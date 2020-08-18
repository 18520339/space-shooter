#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
private:
	Sprite sprite;
	Vector2f direction;
	float speed;

public:
	Bullet(Texture texture, float posX, float posY, float x, float y, float speed);
	FloatRect getGlobalBounds();
	void update();
	void render(RenderTarget& target);
};

