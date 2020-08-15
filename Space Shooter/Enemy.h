#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy
{
private:
	CircleShape shape;
	int type;
	float speed;

	int hp;
	int hpMax;
	int damage;
	int points;

	void initShape();
	void initVariables();

public:
	Enemy(float posX, float posY);
	const FloatRect getBounds();
	void update();
	void render(RenderTarget& target);
};

