#pragma once
#include "Common.h"
#include "Object.h"
#include "ScoreBoard.h"

class Game
{
	Sprite Assets[86];
	Texture Textures[7];
	bool hitFlag;
	Clock deadTime;
	int score;
	int side;
	Font font;
	Text scoreText;
	Text gameOver;
	ScoreBoard *board;
public:
	Game();
	void drawBackground(RenderWindow& window);
	void GameUpdate(RenderWindow& window);
	void onFloor(Object* obj);
	void turtleCollusion(Object* obj);
	//bool hitFloor(Object* obj);
	bool checkCollusion(Object* m, Object* t, int& side);
};