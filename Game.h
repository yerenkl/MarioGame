#pragma once
#include "Common.h"
#include "Object.h"

class Game
{
	Sprite Assets[82];
	Texture Textures[6];
public:
	void drawBackground(RenderWindow& window);
	int onFloor(Object* obj);
	bool hitFloor(Object* obj);
	bool checkCollusion(Object* t, Object* m, int& side);
};