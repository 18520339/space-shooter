#pragma once
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	RenderWindow* window;
	vector<Bullet*> bullets;
	Texture* texture;

	Ship* ship;
	RectangleShape shipHpBar;
	RectangleShape shipHpBarBack;

	vector<Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;

	Font font;
	Text pointText;
	Text gameOverText;
	unsigned points;

	Texture worldBackgroundTex;
	Sprite worldBackground;

	void initWindow();
	void initTexture();
	void initGUI();
	void initWorld();
	void initSystems();
	void initShip();
	void initEnemies();

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

