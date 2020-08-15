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
		cout << "Error::Ship::initTexture::Couldn't load texture file.\n";
}


void Game::initShip()
{
	this->ship = new Ship();
	this->enemy = new Enemy(20.f, 20.f);
}

Game::Game()
{
	this->initWindow();
	this->initTexture();
	this->initShip();
}

Game::~Game()
{
	delete this->window;
	delete this->ship;
	delete this->texture;
	
	for (Bullet* bullet : this->bullets)
		delete bullet;
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
			Mouse::getPosition().x - window->getPosition().x - this->ship->getSize().x / 1.8,
			Mouse::getPosition().y - window->getPosition().y - this->ship->getSize().y / 1.2
		);

	if (Mouse::isButtonPressed(Mouse::Left) && this->ship->canAttack())
		this->bullets.push_back(new Bullet(
			this->texture, 
			this->ship->getPosition().x + this->ship->getSize().x / 3,
			this->ship->getPosition().y + this->ship->getSize().y / 9,
			0.f, -1.f, 5.f
		));
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

void Game::update()
{
	this->updatePollEvent();
	this->updateInput();
	this->ship->update();
	this->updateBullets();
}

void Game::render()
{
	this->window->clear();
	this->ship->render(*this->window);

	for (Bullet* bullet : this->bullets)
		bullet->render(*this->window);

	this->enemy->render(*this->window);
	this->window->display();
}
