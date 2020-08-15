#pragma once
#include "Ship.h"
#include "Bullet.h"
#include <map>

class Game
{
private:
	RenderWindow* window;
	vector<Bullet*> bullets;
	Texture* texture;
	Ship* ship;
	void initWindow();
	void initTexture();
	void initShip();

public:
	Game();
	~Game();
	void run();
	void updatePollEvent();
	void updateMovement();
	void updateBullets();
	void update();
	void render();
};

