#include "Bullet.h"

Bullet::Bullet(Texture* texture, float posX, float posY, float x, float y, float moveSpeed)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(posX, posY);
	this->sprite.scale(0.27f, 0.1f);

	this->direction.x = x;
	this->direction.y = y;
	this->moveSpeed = moveSpeed;
}

const FloatRect Bullet::getBounds()
{
	return this->sprite.getGlobalBounds();
}

void Bullet::update()
{
	this->sprite.move(
		this->moveSpeed * this->direction.x,
		this->moveSpeed * this->direction.y
	);
}

void Bullet::render(RenderTarget& target)
{
	target.draw(this->sprite);
}