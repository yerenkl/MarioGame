#pragma once
#include "Common.h"
#include "Object.h"
#include "Turtle.h"
#include "ScoreBoard.h"
#include "Linkedlist.h"

class Game
{
	Sprite Assets[88];
	Texture Textures[9];
	int score;
	float elapsedTime;
	bool gamestart;
	bool gamewin;
	bool gameover;
	int turtleCount;
	Clock deadTime;
	Clock restartTime;
	Clock TurtleTime;
	Clock turtlehitTime;
	LinkedList* spawner;
	Font fonts[2];
	Text text[6];
	ScoreBoard *board;
public:
	Game();
	void drawBackground(RenderWindow& window);
	void GameUpdate(RenderWindow& window);
	int onFloor(Object* obj);
	void turtleFloor(Object* obj);
	bool turtleCollusion(Turtle* obj1, Turtle* obj2);
	void isturtleOn(Turtle* obj1, int x);
	bool checkCollusion(Object* m, Object* t);
};