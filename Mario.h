#pragma once
#include "Object.h"
class Mario :
    public Object
{
	float g;
	float acc;
	int lives;
public:
	void update();
	Mario(sf::RenderWindow* window);
private:
	void move(const float dir_x, const float dir_y);
	void updateMove();
	void updatePhysics();
	void animationUpdate();
	void animationReset();
	void jump(const float dir_x, const float dir_y);
	void fall(void);
};

