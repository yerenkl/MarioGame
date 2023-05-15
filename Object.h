#pragma once
#include "Common.h"

class Object
{
public:
	bool dead;
protected:
	RenderWindow* window;
	Texture textures[14];
	Sprite sprite;
	Vector2f pos;
	float vx;
	float vy;
	int state;
	int frame;
	int heading;
	bool isJumping;
	sf::Clock clock;
	Clock animationTimer;
public:
	Object(RenderWindow* window); //Constructor
	void setPosition(Vector2f pos);
	void setVelocityX(void);//Sets position of the object
	Vector2f getPosition(); //Gets position of the object-
	sf::FloatRect boundingBox(void);
	void resetVelocity();
	void resetVelocityFall();
	void draw(RenderWindow& window);//Draws current the object texture to screen
	void move(int direction) {}; //Abstract method that will be overridden
	virtual void jump(const float dir_x, const float dir_y) {}; //Abstract method that will be overridden
	virtual void fall(void) {};
	virtual void update(void) {};
	virtual void animationReset() {};
};
