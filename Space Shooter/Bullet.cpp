#include "Bullet.h"

Bullet::Bullet(Texture* texture, float posX, float posY, float x, float y, float speed)
{
	sprite.setTexture(*texture);
	sprite.setPosition(posX, posY);
	sprite.scale(0.27f, 0.1f);

	direction.x = x;
	direction.y = y;
	this->speed = speed;
}

FloatRect Bullet::getGlobalBounds() { return sprite.getGlobalBounds(); }
void Bullet::update() { sprite.move(speed * direction.x, speed * direction.y); }
void Bullet::render(RenderTarget& target) { target.draw(sprite); }