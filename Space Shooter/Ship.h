#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Ship
{
private:
	Texture texture;
	Sprite sprite;

	float moveSpeed;
	float attackCoolDown;
	float attackCoolDownMax;

	int hpMax;
	int hp;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Ship();
	const Vector2f getPosition();
	const FloatRect getBounds();

	const int getHpMax();
	const int getHp();
	const bool canAttack();

	void move(const float x, const float y);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	void updateAttack();
	void update();
	void render(RenderTarget& target);
};

