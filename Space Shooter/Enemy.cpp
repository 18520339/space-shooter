#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 5 + 3);
	this->shape.setFillColor(Color(
		rand() % 255 + 1,
		rand() % 255 + 1,
		255
	));
}

void Enemy::initVariables()
{
	this->type = 0;
	this->speed = 2.f;
	this->hp = 0;
	this->hpMax = 10;
	this->damage = 1;
	this->points = 5;
}

Enemy::Enemy(float posX, float posY)
{
	this->initShape();
	this->initVariables();
	this->shape.setPosition(posX, posY);
}

const FloatRect Enemy::getBounds()
{
	return this->shape.getGlobalBounds() ;
}

void Enemy::update() 
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(RenderTarget& target)
{
	target.draw(this->shape);
}
