#include "SpaceShip.h"
#include <iostream>
using namespace std;

SpaceShip::SpaceShip()
{
	hp = hpMax = 100;
	attackSpeed = attackSpeedMax = 10;

	if (!texture.loadFromFile("Textures/ship.png"))
		cout << "Error::SpaceShip::Couldn't load texture file.\n";

	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.1, 0.1);
}

bool SpaceShip::canAttack()
{
	if (attackSpeed >= attackSpeedMax)
	{
		attackSpeed = 0;
		return true;
	}
	return false;
}

FloatRect SpaceShip::getGlobalBounds() { return sprite.getGlobalBounds(); }
Vector2f SpaceShip::getPosition() { return sprite.getPosition(); }
void SpaceShip::setPosition(float x, float y) { sprite.setPosition(x, y); }

int SpaceShip::getHpMax() { return hpMax; }
int SpaceShip::getHp() { return hp; }
void SpaceShip::setHp(int hp) { this->hp = hp; }
void SpaceShip::loseHp(int value) { hp = hp < value ? hp - value : 0; }

void SpaceShip::update() { if (attackSpeed < attackSpeedMax) this->attackSpeed += 0.5; }
void SpaceShip::render(RenderTarget& target) { target.draw(sprite); }