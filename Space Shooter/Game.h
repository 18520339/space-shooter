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
	unsigned points;
	float enemyInitDelay, enemyInitDelayMax;

	SpaceShip* spaceShip;
	Texture* bulletTexture;

	vector<Bullet*> bullets;
	vector<Enemy*> enemies;

	Texture backgroundTexture;
	Sprite backgroundSprite;

	Font font;
	Text pointText;
	Text gameOverText;

	RectangleShape spaceShipHpBar;
	RectangleShape spaceShipHpBarBack;

	void initWindow();
	void initSystem();
	void initGUI();

public:
	Game();
	~Game();

	void updatePollEvent();
	void updateInput();
	void updateCollision();

	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateGUI();

	void update();
	void render();
	void run();
};

