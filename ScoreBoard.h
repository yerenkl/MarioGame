#pragma once
#include "Common.h"
class ScoreBoard
{
	string score; //Current score
	int lives; //Remaining life count for Mario
public:
	void setScore(int score); //Sets the score
	void setLives(int lives); //Sets the remaining lives
	int getLives(void); //Gets the remain
};

