#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy
{
private:
	unsigned pointCount;
	CircleShape shape;
	int type;
	float speed;

	int hpMax;
	int hp;

	int damage;
	int points;

	void initVariables();
	void initShape();

public:
	Enemy(float posX, float posY);
	const FloatRect getBounds();

	const int getPoints();
	const int getDamage();
	void update();
	void render(RenderTarget& target);
};

