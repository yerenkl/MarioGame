#pragma once
#include "Common.h"

class Object
{
protected:
	Texture textures[14];
	RenderWindow* window;
	int state;
	int heading;
	Sprite sprite;
	Vector2f pos;
public:
	Object(RenderWindow* window); //Constructor
	void setPosition(Vector2f pos); //Sets position of the object
	Vector2f getPosition(); //Gets position of the object-
	sf::IntRect boundingBox(void);
	void draw(RenderWindow& window);//Draws current the object texture to screen
	virtual void move(int direction) {}; //Abstract method that will be overridden
	virtual void jump(bool down) {}; //Abstract method that will be overridden
	virtual void update(bool ground, bool u_g){};
	virtual void fall(void) {};
};

class Mario :public Object
{
	float vx;
	float vy;
	bool isJumping;
	bool isWalking;
	

public:
	Mario(sf::RenderWindow* window);
	void move(int direction);
	void jump(bool down);
	void update(bool ground, bool u_g);
	void fall(void);
};

class Turtle :public Object
{
	float vx;
	float vy;
	sf::Clock clock;
public:
	Turtle(sf::RenderWindow* window);
	void move(int direction) {};
	void jump(bool down) {};
	void update(bool ground, bool u_g);
	void fall(void) {};
};