#pragma once
#include "Common.h"
#include "Object.h"

class Game
{
	Sprite Assets[82];
	Texture Textures[6];
	bool hitFlag;
	Clock deadTime;
	int side;
	Font font;
public:
	Game();
	void drawBackground(RenderWindow& window);
	void GameUpdate(RenderWindow& window);
	void onFloor(Object* obj);
	void turtleCollusion(Object* obj);
	//bool hitFloor(Object* obj);
	bool checkCollusion(Object* m, Object* t, int& side);
};