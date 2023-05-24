#pragma once
#include "Object.h"
class Turtle :
	public Object
{
public:
	Clock surpriseTime;
	Clock vulnerableTime;
	bool isVulnerable;
	bool stop;
	bool collusion;
	Turtle(RenderWindow* window, int heading, float t_v);
	void jump(const float dir_x, const float dir_y) {}; //Abstract method that will be overridden
	void fall(void);
	void update(void);
	void surprised(void);
	void updatePhysics();
	void updateMove();
	void animationReset() {};
	void vulnerable(void);
	
};

