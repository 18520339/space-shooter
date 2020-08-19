#include "Enemy.h"
#include <iostream>
using namespace std;

int random(int from, int to) 
{ 
	int num = rand() % (to - from + 1) + from;
	return num;
}

Enemy::Enemy(float posX, float posY)
{
	points = random(3, 10);
	speed = points / 2;
	hp = hpMax = points;

	circleShape.setRadius(points * 5);
	circleShape.setPointCount(points);
	circleShape.setFillColor(Color(random(1, 255), random(1, 255), 255));
	circleShape.setPosition(posX, posY);
}

FloatRect Enemy::getGlobalBounds() { return circleShape.getGlobalBounds(); }
int Enemy::getPoints() { return points; }
void Enemy::update() { circleShape.move(0, speed); }
void Enemy::render(RenderTarget& target) { target.draw(circleShape); }
