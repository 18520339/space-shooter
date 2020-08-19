#include "Game.h"
#include <sstream>

void Game::initWindow()
{
	window = new RenderWindow(
		VideoMode(600, 800),
		"Space Shooter - SFML Game Development",
		Style::Close | Style::Titlebar
	);
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(false);
}

void Game::initSystem()
{
	points = 0;
	enemyInitDelay = enemyInitDelayMax = 50;
	spaceShip = new SpaceShip();

	bulletTexture = new Texture();
	if (!(*bulletTexture).loadFromFile("Textures/bullet.png"))
		cout << "Error::Game::Couldn't load bullet texture file.\n";
}

void Game::initGUI()
{
	if (!backgroundTexture.loadFromFile("Textures/background.jpg"))
		cout << "Error::Game::Couldn't load background texture.\n";
	backgroundSprite.setTexture(backgroundTexture);

	if (!font.loadFromFile("Fonts/poxel-font.ttf"))
		cout << "Error::Game::Failed to load font\n";

	pointText.setFont(font);
	pointText.setCharacterSize(20);
	pointText.setFillColor(Color::White);
	pointText.setString("test");
	pointText.setPosition(500, 25);

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(60);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition(
		(window->getSize().x - gameOverText.getGlobalBounds().width) / 2,
		(window->getSize().y - gameOverText.getGlobalBounds().height) / 2
	);

	spaceShipHpBar.setSize(Vector2f(300, 25));
	spaceShipHpBar.setFillColor(Color::Red);
	spaceShipHpBar.setPosition(Vector2f(20, 20));

	spaceShipHpBarBack = spaceShipHpBar;
	spaceShipHpBarBack.setFillColor(Color(25, 25, 25, 200));
}


Game::Game()
{
	initWindow();
	initSystem();
	initGUI();
}

Game::~Game()
{
	delete window;
	delete spaceShip;
	delete bulletTexture;

	for (Bullet* bullet : bullets) delete bullet;
	for (Enemy* enemy : enemies) delete enemy;
}

void Game::updatePollEvent()
{
	Event e;
	while (window->pollEvent(e))
	{
		if ((e.Event::type == Event::Closed) ||
			(e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape))
			window->close();
	}
}

void Game::updateInput()
{
	float spaceShipWidth = spaceShip->getGlobalBounds().width;
	float spaceShipHeight = spaceShip->getGlobalBounds().height;

	spaceShip->setPosition(
		Mouse::getPosition().x - window->getPosition().x - spaceShipWidth / 1.8,
		Mouse::getPosition().y - window->getPosition().y - spaceShipHeight / 1.2
	);

	if (Mouse::isButtonPressed(Mouse::Left) && spaceShip->canAttack())
		bullets.push_back(new Bullet(
			bulletTexture,
			spaceShip->getPosition().x + spaceShipWidth / 3,
			spaceShip->getPosition().y + spaceShipWidth / 7,
			0, -1, 5
		));
}

void Game::updateCollision()
{
	float spaceShipWidth = spaceShip->getGlobalBounds().width;
	float spaceShipHeight = spaceShip->getGlobalBounds().height;

	float spaceShipTop = spaceShip->getGlobalBounds().top;
	float spaceShipLeft = spaceShip->getGlobalBounds().left;

	unsigned windowWidth = window->getSize().x;
	unsigned windowHeight = window->getSize().y;

	if (spaceShipLeft < 0) spaceShipLeft = 0;
	else if (spaceShipLeft + spaceShipWidth >= windowWidth)
		spaceShipLeft = windowWidth - spaceShipWidth;

	if (spaceShipTop < 0) spaceShipTop = 0;
	else if (spaceShipTop + spaceShipHeight >= windowHeight) 
		spaceShipTop = windowHeight - spaceShipHeight;

	spaceShip->setPosition(spaceShipLeft, spaceShipTop);
}

void Game::updateBullets()
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		bullets[i]->update();
		if (bullets[i]->getGlobalBounds().top + bullets[i]->getGlobalBounds().height < 0.f)
		{
			delete bullets.at(i);
			bullets.erase(bullets.begin() + i);
			// cout << "Number of Bullets" << bullets.size() << endl;
		}
	}
}

void Game::updateEnemies()
{
	enemyInitDelay += 0.5;
	if (enemyInitDelay >= enemyInitDelayMax)
	{
		enemies.push_back(new Enemy(rand() % window->getSize().x - 20, -100));
		enemyInitDelay = 0;
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->update();
		if (enemies[i]->getGlobalBounds().top > window->getSize().y)
		{
			delete enemies.at(i);
			enemies.erase(enemies.begin() + i);
		}
		else if (enemies[i]->getGlobalBounds().intersects(spaceShip->getGlobalBounds()))
		{
			spaceShip->loseHp(enemies.at(i)->getPoints());
			delete enemies.at(i);
			enemies.erase(enemies.begin() + i);
		}
		// cout << "Number of Enemies" << enemies.size() << endl;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (int j = 0; j < bullets.size() && !enemy_deleted; ++j)
		{
			if (enemies[i]->getGlobalBounds().intersects(bullets[j]->getGlobalBounds()))
			{
				enemy_deleted = true;
				points += enemies[i]->getPoints();

				delete enemies[i];
				enemies.erase(enemies.begin() + i);

				delete bullets[j];
				bullets.erase(bullets.begin() + j);
			}
		}
	}
}

void Game::updateGUI()
{
	stringstream ss;
	ss << "Points: " << points;
	pointText.setString(ss.str());

	float hpPercent = (float)spaceShip->getHp() / spaceShip->getHpMax();
	spaceShipHpBar.setSize(Vector2f(300 * hpPercent, spaceShipHpBar.getSize().y));
}

void Game::update()
{
	updateInput();
	updateCollision();
	updateBullets();
	updateEnemies();
	updateCombat();
	updateGUI();
	spaceShip->update();
}

void Game::render()
{
	window->clear();
	window->draw(backgroundSprite);

	spaceShip->render(*window);
	for (Bullet* bullet : bullets) bullet->render(*window);
	for (Enemy* enemy : enemies) enemy->render(*window);

	window->draw(pointText);
	window->draw(spaceShipHpBarBack);
	window->draw(spaceShipHpBar);

	if (spaceShip->getHp() <= 0) window->draw(gameOverText);
	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		updatePollEvent();
		if (spaceShip->getHp() > 0) update();
		render();
	}
}