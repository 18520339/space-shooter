#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{ 
private:
	Sprite sprite;
	Vector2f direction;
	float moveSpeed;

public:
	Bullet(Texture* texture, float posX, float posY, float x, float y, float moveSpeed);
	const FloatRect getBounds();
	void update();
	void render(RenderTarget& target);
};

