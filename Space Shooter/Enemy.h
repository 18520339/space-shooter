#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy
{
private:
	CircleShape circleShape;
	int points;
	float speed;
	float hp, hpMax;

public:
	Enemy(float posX, float posY);
	FloatRect getGlobalBounds();
	int getPoints();

	void update();
	void render(RenderTarget& target);
};

