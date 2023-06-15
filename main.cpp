#include "Game.h"

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	auto image = sf::Image{};
	if (!image.loadFromFile("./assets/mariohead.png"))
	{
		cout << "Image could not loaded.";
	}
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	window.setFramerateLimit(60);
	Game MarioGame;
	MarioGame.GameUpdate(window);
	return 0;
}