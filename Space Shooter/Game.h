#pragma once
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"
#include <map>

class Game
{
private:
	RenderWindow* window;
	vector<Bullet*> bullets;
	Texture* texture;
	Ship* ship;
	Enemy* enemy;

	void initWindow();
	void initTexture();
	void initShip();

public:
	Game();
	~Game();

	void run();
	void updatePollEvent();
	void updateInput();
	void updateBullets();
	void update();
	void render();
};

