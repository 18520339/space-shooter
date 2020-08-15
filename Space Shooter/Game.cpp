#include "Game.h"

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

	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(12);
	this->pointText.setFillColor(Color::White);
	this->pointText.setString("test");
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background.jpg"))
		cout << "Error::GAME::INITWORLD::Couldn't load background texture.\n";
	this->worldBackground.setTexture(this->worldBackgroundTex);
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

	if (Mouse::getPosition().x >= window->getPosition().x &&
		Mouse::getPosition().y >= window->getPosition().y &&
		Mouse::getPosition().x <= window->getPosition().x + window->getSize().x &&
		Mouse::getPosition().y <= window->getPosition().y + window->getSize().y)
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
}

void Game::updateBullets()
{
	for (int i = 0; i < this->bullets.size(); ++i)
	{
		bullets[i]->update();
		if (bullets[i]->getBounds().top + bullets[i]->getBounds().height < 0.f)
		{
			delete this->bullets.at(i);
			this->bullets.erase(this->bullets.begin() + i--);
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
		if (enemies[i]->getBounds().top + 
			enemies[i]->getBounds().height >
			this->window->getSize().y)
		{
			delete this->enemies.at(i);
			this->enemies.erase(this->enemies.begin() + i--);
			cout << this->enemies.size() << "\n";
		}
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
	this->updatePollEvent();
	this->updateInput();
	this->updateGUI();
	this->ship->update();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
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
	this->window->display();
}
