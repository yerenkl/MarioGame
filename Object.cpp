#pragma once
#include "Object.h"

Object::Object(RenderWindow* window)
{
	this->window = window;
	dead = false;
	for (int x = 1; x < 8; x++) {
		textures[x - 1].loadFromFile("./assets/mario" + std::to_string(x) + ".png");
	}
	for (int x = 1; x < 6; x++) {
		textures[x + 6].loadFromFile("./assets/turtle" + std::to_string(x) + ".png");
	}
}

void Object::setPosition(sf::Vector2f pos)
{
	if(!dead)
	{
		this->pos = pos;
		sprite.setPosition(pos);
	}
}

void Object::setVelocityX()
{
	vx = -vx;
	heading = -heading;
}

Vector2f Object::getPosition()
{
	return sprite.getPosition();
}

void Object::draw(RenderWindow& window)
{
	window.draw(sprite);
}

FloatRect Object::boundingBox(void)
{
	sf::Rect<float> rec = this->sprite.getGlobalBounds();
	return (rec);
}

void Object::resetVelocity()
{
	if (!dead)
	{
		vy = 0;
		isJumping = false;
	}
}

void Object::resetVelocityFall()
{
	vy = 0;
}