#include "Object.h"

class Mario :public Object
{
	float vx;
	float vy;
public:
	Mario(sf::RenderWindow* window);
	void move(int direction);
	void jump(bool down);
	void fall(void);
};