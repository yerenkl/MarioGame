#include "Game.h"
#include "Object.h"

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	window.setFramerateLimit(60);
	Game MarioGame;
	MarioGame.drawBackground(window);
	return 0;
}