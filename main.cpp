#include "Game.h"
#include "Object.h"

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	Game MarioGame;
	MarioGame.drawBackground(window);
	return 0;
}