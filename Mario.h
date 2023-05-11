#include "Object.h"

class Mario :public Object
{
	float vx;
	float vy;
	bool isJumping;
	bool isWalking;

public:
	Mario(sf::RenderWindow* window);
	void move(int direction);
	void jump(bool ground);
	void fall(void);
};