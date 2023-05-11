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
	if (state == 0)
	{
		sprite.setTexture(textures[0]);
		heading = -1;
	}
	if (state == 1) 
	{
		sprite.setScale(heading, 1.f);
		sprite.setTexture(textures[1]);
	}
	if (state == 2) 
	{
		sprite.setTexture(textures[2]);
	}
	if (state == 3) 
	{
		sprite.setTexture(textures[3]);
	}
	if (state == 4) 
	{
		sprite.setScale(heading, 1.f);
		sprite.setTexture(textures[1]);
	}
	if (state == 5)
	{
		sprite.setTexture(textures[2]);
	}
	if (state == 6)
	{
		sprite.setTexture(textures[3]);
	}
	window.draw(sprite);
}