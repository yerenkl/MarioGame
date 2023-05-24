#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	lives = LIVES;
	score = "00000";
}

void ScoreBoard::setScore(int score)
{
	String str;
	str = "00" + std::to_string(score);

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
