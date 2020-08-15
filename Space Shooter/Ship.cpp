#include "Ship.h"

void Ship::initVariables()
{
	this->moveSpeed = 2.f;
	this->attackCoolDownMax = 10.f;
	this->attackCoolDown = this->attackCoolDownMax;
}

void Ship::initTexture()
{
	if(!this->texture.loadFromFile("Textures/ship.png"))
		cout << "Error::Ship::initTexture::Couldn't load texture file.\n";
}

void Ship::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.1f, 0.1f);
}

Ship::Ship()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

const Vector2f& Ship::getPosition()
{
	return this->sprite.getPosition();
}

const Vector2f& Ship::getSize()
{
	return Vector2f(
		this->sprite.getScale().x * this->sprite.getTexture()->getSize().x,
		this->sprite.getScale().y * this->sprite.getTexture()->getSize().y
	);
}

const bool Ship::canAttack()
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0.f;
		return true;
	}
	return false;
}

void Ship::move(const float x, const float y)
{
	this->sprite.move(this->moveSpeed * x, this->moveSpeed * y);
}

void Ship::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Ship::updateAttack()
{
	if (this->attackCoolDown < this->attackCoolDownMax)
		this->attackCoolDown += 0.5f; 
}

void Ship::update()
{
	this->updateAttack();
}

void Ship::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
