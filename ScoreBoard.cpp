#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	lives = 3;
	score = "00000";
}

void ScoreBoard::setScore(int score)
{
	String str = "00"+std::to_string(score);
	this->score = str;
}

void ScoreBoard::setLives(int lives)
{
	this->lives = lives;
}

int ScoreBoard::getLives(void)
{
	return lives;
}

String ScoreBoard::getScore(void)
{
	return score;
}
