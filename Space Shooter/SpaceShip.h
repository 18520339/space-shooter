#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class SpaceShip
{
private:
	Texture texture;
	Sprite sprite;

	float hp, hpMax;
	float attackSpeed, attackSpeedMax;

public:
	SpaceShip();
	bool canAttack();

	FloatRect getGlobalBounds();
	Vector2f getPosition();
	void setPosition(float x, float y);

	int getHpMax();
	int getHp();
	void setHp(int hp);
	void loseHp(int value);

	void update();
	void render(RenderTarget& target);
};

