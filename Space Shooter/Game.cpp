#include "Game.h"
#include <sstream>

void Game::initWindow()
{
	this->window = new RenderWindow(
		VideoMode(600, 800), 
		"Space Shooter - SFML Game Development",
		Style::Close | Style::Titlebar
	);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);

}

void Game::initTexture()
{
	this->texture = new Texture();
	if (!(*this->texture).loadFromFile("Textures/bullet.png"))
		cout << "Error::GAME::INITTEXTURE::Couldn't load texture file.\n";
}

void Game::initGUI()
{
	if (!this->font.loadFromFile("Fonts/poxel-font.ttf"))
		cout << "ERROR::GAME::INITGUI::Failed to load font\n";

	this->pointText.setPosition(500.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(Color::White);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		(this->window->getSize().x - this->gameOverText.getGlobalBounds().width) / 2.f,
		(this->window->getSize().y - this->gameOverText.getGlobalBounds().height) / 2.f
	);

	this->shipHpBar.setSize(Vector2f(300.f, 25.f));
	this->shipHpBar.setFillColor(Color::Red);
	this->shipHpBar.setPosition(Vector2f(20.f, 20.f));

	this->shipHpBarBack = this->shipHpBar;
	this->shipHpBarBack.setFillColor(Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background.jpg"))
		cout << "Error::GAME::INITWORLD::Couldn't load background texture.\n";
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initShip()
{
	this->ship = new Ship();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50;
	this->spawnTimer = this->spawnTimerMax;
}

Game::Game()
{
	this->initWindow();
	this->initTexture();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initShip();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->ship;
	delete this->texture;
	
	for (Bullet* bullet : this->bullets)
		delete bullet;

	for (Enemy* enemy : this->enemies)
		delete enemy;
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvent();
		if (this->ship->getHp() > 0)
			this->update();
		this->render();
	}
}

void Game::updatePollEvent()
{
	Event e;
	while (this->window->pollEvent(e))
	{
		if ((e.Event::type == Event::Closed) ||
			(e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape))
			this->window->close();
	}
}

void Game::updateInput()
{
	/*
	if (Keyboard::isKeyPressed(Keyboard::A))
		this->ship->move(-1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::D))
		this->ship->move(1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::W))
		this->ship->move(0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::S))
		this->ship->move(0.f, 1.f);
	*/

	this->ship->setPosition(
		Mouse::getPosition().x - window->getPosition().x - this->ship->getBounds().width / 1.8,
		Mouse::getPosition().y - window->getPosition().y - this->ship->getBounds().height / 1.2
	);

	if (Mouse::isButtonPressed(Mouse::Left) && this->ship->canAttack())
		this->bullets.push_back(new Bullet(
			this->texture, 
			this->ship->getPosition().x + this->ship->getBounds().width / 3,
			this->ship->getPosition().y + this->ship->getBounds().width / 7,
			0.f, -1.f, 5.f
		));
}

void Game::updateGUI()
{
	stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());

	float hpPercent = (float)this->ship->getHp() / this->ship->getHpMax();
	this->shipHpBar.setSize(Vector2f(300.f * hpPercent, this->shipHpBar.getSize().y));
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	if (this->ship->getBounds().left < 0.f)
		this->ship->setPosition(0.f, this->ship->getBounds().top);
	else if (this->ship->getBounds().left + this->ship->getBounds().width >= this->window->getSize().x)
		this->ship->setPosition(
			this->window->getSize().x - this->ship->getBounds().width, 
			this->ship->getBounds().top
		);

	if (this->ship->getBounds().top < 0.f)
		this->ship->setPosition(this->ship->getBounds().left, 0.f);
	else if (this->ship->getBounds().top + this->ship->getBounds().height >= this->window->getSize().y)
		this->ship->setPosition(
			this->ship->getBounds().left,
			this->window->getSize().y - this->ship->getBounds().height
		);
}

void Game::updateBullets()
{
	for (int i = 0; i < this->bullets.size(); ++i)
	{
		bullets[i]->update();
		if (bullets[i]->getBounds().top + bullets[i]->getBounds().height < 0.f)
		{
			delete this->bullets.at(i);
			this->bullets.erase(this->bullets.begin() + i);
			cout << this->bullets.size() << "\n";
		}
	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x -20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	for (int i = 0; i < this->enemies.size(); ++i)
	{
		enemies[i]->update();
		if (enemies[i]->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies.at(i);
			this->enemies.erase(this->enemies.begin() + i);
		}
		else if (this->enemies[i]->getBounds().intersects(this->ship->getBounds()))
		{ 
			this->ship->loseHp(this->enemies.at(i)->getDamage());
			delete this->enemies.at(i);
			this->enemies.erase(this->enemies.begin() + i);
		}
		cout << this->enemies.size() << "\n";
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (int j = 0; j < this->bullets.size() && !enemy_deleted; ++j)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				
				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);
			
				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();
	this->ship->update();
	this->updateCollision();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->shipHpBarBack);
	this->window->draw(this->shipHpBar);
}

void Game::render()
{
	this->window->clear();
	this->renderWorld();


	this->ship->render(*this->window);

	for (Bullet* bullet : this->bullets)
		bullet->render(*this->window);

	for (Enemy* enemy : this->enemies)
		enemy->render(*this->window);

	this->renderGUI();
	if (this->ship->getHp() <= 0)
		this->window->draw(this->gameOverText);
	this->window->display();
}
