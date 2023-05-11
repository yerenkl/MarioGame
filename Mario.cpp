#include "Mario.h"


Mario::Mario(RenderWindow* window) : Object(window)
{
	vx = VELOCITY_X;
	heading = LEFT;
}

void Mario::move(int direction)
{	
	Vector2f position;
	if (direction == RIGHT)
	{
		position = getPosition();
		position.x = position.x + vx;
		setPosition(position);
		if (state <= 3 && state>0) {
			state++;
		}
		else
		{
			state = 1;
		}
		heading = 1;
	}
	if (direction == LEFT)
	{
		position = getPosition();
		position.x = position.x - vx;
		setPosition(position);
		if (state <= 6 && state > 3) {
			state++;
		}
		else
		{
			state = 4;
		}
		heading=1
	}
	if (direction == STOP)
	{
		state = 0;
	}
}