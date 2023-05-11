#include "Game.h"
#include "Mario.h"

void Game::drawBackground(RenderWindow& window)
{
    int flag = 0;
    Textures[0].loadFromFile("./assets/brick.png");
    Assets[0].setTexture(Textures[0]);
    
    Textures[1].loadFromFile("./assets/floor.png");
    Assets[1].setTexture(Textures[1]);
    Assets[1].setPosition(Vector2f(0, WINDOW_HEIGHT-100));

    Textures[2].loadFromFile("./assets/pipe.png");
    Assets[2].setTexture(Textures[2]);
    Assets[2].setPosition(Vector2f(WINDOW_WIDTH-130, WINDOW_HEIGHT-174));

    Assets[3].setTexture(Textures[2]);
    Assets[3].setScale(-1.f, 1.f);
    Assets[3].setPosition(Vector2f(130, WINDOW_HEIGHT-174));

    Textures[3].loadFromFile("./assets/pipeS.png");
    Assets[4].setPosition(Vector2f(0, WINDOW_HEIGHT - 846));
    Assets[4].setTexture(Textures[3]);

    
    Assets[5].setScale(-1.f, 1.f);
    Assets[5].setTexture(Textures[3]);
    Assets[5].setPosition(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT - 846));
    
    Mario Peach(&window);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        window.clear();

        for (int x = 1; x < 6; x++)
        {
            window.draw(Assets[x]);
        }

        for (int x = 0; x < 16; x++)
        {
            Assets[0].setPosition(Vector2f(WINDOW_WIDTH / 2 - 240 + x * 30, WINDOW_HEIGHT - 494));
            window.draw(Assets[0]);
            if (x < 12)
            {
                Assets[0].setPosition(Vector2f(x * 30, WINDOW_HEIGHT - 294));
                window.draw(Assets[0]);
                Assets[0].setPosition(Vector2f(WINDOW_WIDTH - 30 - (x * 30), WINDOW_HEIGHT - 294));
                window.draw(Assets[0]);
            }
            if (x < 4) {
                Assets[0].setPosition(Vector2f(WINDOW_WIDTH - 30 - (x * 30), WINDOW_HEIGHT - 454));
                window.draw(Assets[0]);
                Assets[0].setPosition(Vector2f((x * 30), WINDOW_HEIGHT - 454));
                window.draw(Assets[0]);
            }
            if (x < 14) {
                Assets[0].setPosition(Vector2f(WINDOW_WIDTH - 30 - (x * 30), WINDOW_HEIGHT - 694));
                window.draw(Assets[0]);
                Assets[0].setPosition(Vector2f((x * 30), WINDOW_HEIGHT - 694));
                window.draw(Assets[0]);
            }

        }

        while (window.pollEvent(event))
        {
            
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Right)
                {
                    Peach.move(RIGHT);
                }
                if (event.key.code == Keyboard::Left)
                {
                    Peach.move(LEFT);
                }
                if (event.key.code == Keyboard::Up)
                {
                    
                    Peach.jump(true);
                    printf("jumped");
                    
                }
            }
            if(event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Right || event.key.code == Keyboard::Left)
                {
                    Peach.move(STOP);
                }
            }
        }
        Peach.jump(false);

        Peach.draw(window);

        window.display();
        
    }

}