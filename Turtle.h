#pragma once
#include "Object.h"
class Turtle :
	public Object
{
	Clock surpriseTime;
	Clock vulnerableTime;
	void update(void);
	void updatePhysics();
	void animationReset() {};
	void jump(const float dir_x, const float dir_y) {};
public:
	bool collusion;
	Turtle(RenderWindow* window, int heading, float t_v);
	void fall(void);
	void surprised(void);
	void vulnerable(void);
};

