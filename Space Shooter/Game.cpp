#include "Game.h"

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

void Game::initText()
{
	if (!font.loadFromFile("Fonts/poxel-font.ttf"))
		cout << "ERROR::Game::Failed to load font\n";

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
}

void Game::initTexture()
{
	if (!bulletTexture.loadFromFile("Textures/bullet.png"))
		cout << "Error::Game::Couldn't load bullet texture file.\n";

	if (!backgroundTexture.loadFromFile("Textures/background.jpg"))
		cout << "Error::Game::Couldn't load background texture.\n";
	backgroundSprite.setTexture(backgroundTexture);

	spaceShipHpBar.setSize(Vector2f(300, 25));
	spaceShipHpBar.setFillColor(Color::Red);
	spaceShipHpBar.setPosition(Vector2f(20, 20));

	spaceShipHpBarBack = spaceShipHpBar;
	spaceShipHpBarBack.setFillColor(Color(25, 25, 25, 200));
}

Game::Game()
{
	initWindow();
	initText();
	initTexture();

	spaceShip = new SpaceShip();
	enemyInitDelay = enemyInitDelayMax = 50;
	points = 0;
}

Game::~Game()
{
	delete this->window;
	delete this->spaceShip;
	for (Bullet* bullet : this->bullets) delete bullet;
	for (Enemy* enemy : this->enemies) delete enemy;
}


