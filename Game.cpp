#include "Game.h"

void Game::drawBackground(RenderWindow& window)
{
    int flag = 0;
    Textures[0].loadFromFile("./assets/brick.png");
    Assets[0].setTexture(Textures[0]);

    Textures[1].loadFromFile("./assets/floor.png");
    Assets[1].setTexture(Textures[1]);
    Assets[1].setPosition(Vector2f(0, WINDOW_HEIGHT - 100));

    Textures[2].loadFromFile("./assets/pipe.png");
    Assets[2].setTexture(Textures[2]);
    Assets[2].setPosition(Vector2f(WINDOW_WIDTH - 130, WINDOW_HEIGHT - 174));

    Assets[3].setTexture(Textures[2]);
    Assets[3].setScale(-1.f, 1.f);
    Assets[3].setPosition(Vector2f(130, WINDOW_HEIGHT - 174));

    Textures[3].loadFromFile("./assets/pipeS.png");
    Assets[4].setPosition(Vector2f(0, WINDOW_HEIGHT - 846));
    Assets[4].setTexture(Textures[3]);


    Assets[5].setScale(-1.f, 1.f);
    Assets[5].setTexture(Textures[3]);
    Assets[5].setPosition(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT - 846));

    for (int x = 6; x < 81; x++)
    {
        Assets[x].setTexture(Textures[0]);
    }

    for (int x = 0; x < 16; x++)
    {
        Assets[x + 6].setPosition(Vector2f(WINDOW_WIDTH / 2 - 240 + x * 30, WINDOW_HEIGHT - 494));
    }
    for (int x = 0; x < 12; x++)
    {
        Assets[x + 22].setPosition(Vector2f(x * 30, WINDOW_HEIGHT - 294));
        Assets[x + 34].setPosition(Vector2f(WINDOW_WIDTH - 30 - (x * 30), WINDOW_HEIGHT - 294));
    }
    for (int x = 0; x < 4; x++)
    {
        Assets[x + 46].setPosition(Vector2f(WINDOW_WIDTH - 30 - (x * 30), WINDOW_HEIGHT - 454));
        Assets[x + 50].setPosition(Vector2f((x * 30), WINDOW_HEIGHT - 454));
    }
    for (int x = 0; x < 14; x++)
    {
        Assets[x + 54].setPosition(Vector2f(WINDOW_WIDTH - 30 - (x * 30), WINDOW_HEIGHT - 694));
        Assets[x + 68].setPosition(Vector2f((x * 30), WINDOW_HEIGHT - 694));
    }

    Assets[5].setPosition(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT - 846));
    
    Object* Peach = new Mario(&window);
    Object* Koppa = new Turtle(&window);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        window.clear();

        window.draw(Assets[1]);
        for (int x = 6; x < 81; x++)
        {
            window.draw(Assets[x]);
        }


        if (window.pollEvent(event))
        {
            
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            
            
             
            if(event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Right || event.key.code == Keyboard::Left)
                {
                    Peach->move(STOP);
                }
            }
            
        }
        if (onFloor(Peach) != 4)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                Peach->move(RIGHT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                Peach->move(LEFT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                Peach->jump(onFloor(Peach));

            }
        }
        if (checkCollusion(Koppa, Peach,flag)){ //check collusion with turtle
            Peach->fall();
        }

        Peach->update(onFloor(Peach));
        

        Koppa->update(onFloor(Koppa));
        Peach->draw(window);
        Koppa->draw(window);

        for (int x = 2; x < 6; x++)
        {
            window.draw(Assets[x]);
        }

        window.display();
        
    }

}
int Game::onFloor(Object* obj)
{
    for (int x = 0; x < 81; x++) {

        IntRect a = static_cast<IntRect>(Assets[x].getGlobalBounds());
        IntRect b = obj->boundingBox();

        sf::IntRect a_up(a.left+10, a.top - 12, a.width-20, 30);
        sf::IntRect a_down(a.left+10, a.top + a.height + 12, a.width-10, 10);

        sf::IntRect a_left(a.left + a.width - 10, a.top - 5, 5, a.height - 10);


        
        if (b.intersects(a_left))
        {
            /*cout << "left";*/
            return 4;
        }
        if (b.intersects(a_down))
        {
            /*cout << "top:" << b.top << "bottom:" << b.left  << "\n";*/
           /* cout << "up";*/
            return 2;
        }
        if (b.intersects(a_up))
        {
            /*cout << "GROUND";*/
            return 1;
        }
        
    }
    return 0;
}

bool Game::hitFloor(Object* obj)
{

    for (int x = 0; x < 81; x++) {
        IntRect a = static_cast<IntRect>(Assets[x].getGlobalBounds());
        IntRect b = obj->boundingBox();
        sf::IntRect b_up(b.left, b.top, b.width, b.height - 10);
        sf::IntRect b_down(b.left, b.top + b.height, b.width, 10);
        if (a.intersects(b_up))
        {
            return false;
        }
    }
    return true;

}

bool Game::checkCollusion(Object* t, Object* m, int& side)
{
        IntRect a = t->boundingBox();
        IntRect b = m->boundingBox();
        if (a.intersects(b))
        {
            return true;
        }
    return false;

}