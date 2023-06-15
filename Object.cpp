#pragma once
#include "Object.h"

Object::Object(RenderWindow* window)
{
	this->window = window;
	this->next = nullptr;
	
	dead = false;
	for (int x = 1; x < 8; x++) 
	{
		textures[x - 1].loadFromFile("./assets/mario" + std::to_string(x) + ".png");
	}
	for (int x = 1; x < 6; x++) 
	{
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

void Object::setVelocityX(float k)
{
	/*If k is bigger than 0 sets velocity to that value
	Otherwise, changes the direction.*/
	if (k < 0)
	{
		vx = k * vx;
		heading = -heading;
	}

	else
	{
		if (vx < 0)
		{
			vx = -k;
		}
		else
		{
			vx = k;
		}
	}
}

Vector2f Object::getPosition()
{
	return sprite.getPosition();
}

void Object::draw()
{
	window->draw(sprite);
}

FloatRect Object::boundingBox(void)
{
	sf::Rect<float> rec = this->sprite.getGlobalBounds();
	return (rec);
}

void Object::resetVelocity()
{
	/*Resets vertical velocity to the zero. Called when object collided to
	the floor*/
	if (!dead)
	{
		if(vy>0)
			vy = 0;
		isJumping = false;
	}
}

void Object::resetVelocityFall()
{
	/*Resets velocity when Mario hits the floor with his head.*/
	if(!dead)
		vy = 0;
}

void Object::turtleJump()
{
	//When Mario hits on a turtle, he jumps a bit back.
	vy = -5;
}