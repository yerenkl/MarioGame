#pragma once
#include "Common.h"
#include "Object.h"

class Game
{
	Sprite Assets[6];
	Texture Textures[6];
public:
	void drawBackground(RenderWindow& window);
	bool onFloor(Object* obj);
	bool hitFloor(Object* obj);
	/*bool checkCollusion(Turtle* t, Mario* m, int& side);*/
};