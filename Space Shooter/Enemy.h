#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy
{
private:
	CircleShape shape;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initShape();
	void initVariables();

public:
	Enemy(float posX, float posY);
	void update();
	void render(RenderTarget& target);
};

