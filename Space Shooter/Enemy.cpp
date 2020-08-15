#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 5 + 3);

}

void Enemy::initVariables()
{
	this->type = 0;
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

void Enemy::update()
{
 
}

void Enemy::render(RenderTarget& target)
{
	target.draw(this->shape);
}
