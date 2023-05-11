#include "Object.h"

Object::Object(RenderWindow* window) 
{
	this->window = window;
	for (int x = 1; x < 8; x++) {
		textures[x - 1].loadFromFile("./assets/mario" + std::to_string(x) + ".png");
	}
	for (int x = 1; x < 6; x++) {
		textures[x+6].loadFromFile("./assets/turtle" + std::to_string(x) + ".png");
	}
	
	pos = Vector2f(250, 500);
	sprite.setPosition(pos);
	state = 0;
	heading = 1;
}
void Object::setPosition(sf::Vector2f pos) 
{
	this->pos = pos;
	sprite.setPosition(pos);
}

Vector2f Object::getPosition()
{
	return pos;
}

void Object::draw(RenderWindow& window)
{	
	window.draw(sprite);
}