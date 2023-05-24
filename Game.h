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
	int turtleCount;
	Clock deadTime;
	Clock restartTime;
	Clock TurtleTime;
	LinkedList* spawner;
	int score;
	int side;
	Font fontScore;
	Font fontHead;
	Text text[6];
	ScoreBoard *board;
public:
	Game();
	void drawBackground(RenderWindow& window);
	void GameUpdate(RenderWindow& window);
	void onFloor(Object* obj);
	void turtleCollusion(Object* obj);
	void spawnTurtle(void);
	//bool hitFloor(Object* obj);
	bool checkCollusion(Object* m, Object* t);
};