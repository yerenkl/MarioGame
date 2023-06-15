#pragma once
#include "Common.h"

class Object
{
public:
	bool dead;
	Object* next;
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
	Clock animationTimer;
public:
	Object(RenderWindow* window);
	void setPosition(Vector2f pos);
	void setVelocityX(float k);//Sets position of the object
	void turtleJump(void);
	Vector2f getPosition(); //Gets position of the object
	sf::FloatRect boundingBox(void); //	Returns the bounding box of the object
	void resetVelocity();
	void resetVelocityFall();
	void draw(void);//Draws current the object texture to screen
	virtual void jump(const float dir_x, const float dir_y) {};
	virtual void fall(void) {};
	virtual void update(void) {};
	virtual void animationReset() {};
};
