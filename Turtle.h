#pragma once
#include "Object.h"
class Turtle :
    public Object
{
public:
	Turtle(RenderWindow* window, int heading, float t_v);
	void jump(const float dir_x, const float dir_y) {}; //Abstract method that will be overridden
	void fall(void);
	void update(void);
	void updatePhysics();
	void updateMove();
	void animationReset() {};
};

