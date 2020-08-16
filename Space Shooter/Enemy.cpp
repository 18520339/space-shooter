#include "Enemy.h"

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0;
	this->speed = this->pointCount / 2;
	this->hpMax = this->pointCount;
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(Color(
		rand() % 255 + 1,
		rand() % 255 + 1,
		255
	));
}

Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(posX, posY);
}

const FloatRect Enemy::getBounds()
{
	return this->shape.getGlobalBounds() ;
}

const int Enemy::getPoints()
{
	return this->points;
}

const int Enemy::getDamage()
{
	return this->damage;
}

void Enemy::update() 
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(RenderTarget& target)
{
	target.draw(this->shape);
}
