#pragma once
#include "SpaceShip.h"
#include "Bullet.h"
#include "Enemy.h"

#include <iostream>
using namespace std;

class Game
{
private:
	RenderWindow* window;

	Font font;
	Text pointText;
	Text gameOverText;

	Texture bulletTexture;
	Texture backgroundTexture;
	Sprite backgroundSprite;
	RectangleShape spaceShipHpBar;
	RectangleShape spaceShipHpBarBack;

	SpaceShip* spaceShip;
	float enemyInitDelay, enemyInitDelayMax;
	unsigned points;

	vector<Bullet*> bullets;
	vector<Enemy*> enemies;

	void initWindow();
	void initText();
	void initTexture();

public:
	Game();
	~Game();

	void run();
	void updatePollEvent();
	void updateInput();

	void updateGUI();
	void updateWorld();
	void updateCollision();

	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();

	void renderWorld();
	void renderGUI();
	void render();
};

