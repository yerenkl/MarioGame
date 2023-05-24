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
	float elapsedTime;
	bool hitFlag;
	bool gamestart;
	bool gamewin;
	bool gameover;
	bool turtlehitFlag;
	int turtleCount;
	Clock deadTime;
	Clock restartTime;
	Clock TurtleTime;
	Clock turtlehitTime;
	LinkedList* spawner;
	int score;
	int side;
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
	void spawnTurtle(void);
	//bool hitFloor(Object* obj);
	bool checkCollusion(Object* m, Object* t);
};