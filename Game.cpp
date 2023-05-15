#pragma once
#include "Game.h"
#include "Mario.h"
#include "Turtle.h"
#include "Object.h"
#include "ScoreBoard.h"
Game::Game()
{   
    font.loadFromFile("./assets/font.ttf");
    hitFlag = false;
    deadTime.restart();
    Textures[0].loadFromFile("./assets/brick.png");
    Assets[0].setTexture(Textures[0]);


    Textures[1].loadFromFile("./assets/pipe.png");
    Assets[1].setTexture(Textures[1]);
    Assets[1].setPosition(Vector2f(WINDOW_WIDTH - 130, WINDOW_HEIGHT - 174));

    Assets[2].setTexture(Textures[1]);
    Assets[2].setScale(-1.f, 1.f);
    Assets[2].setPosition(Vector2f(130, WINDOW_HEIGHT - 174));


    Textures[4].loadFromFile("./assets/pipeS.png");
    Assets[4].setPosition(Vector2f(0, WINDOW_HEIGHT - 846));
    Assets[4].setTexture(Textures[4]);

    Assets[3].setScale(-1.f, 1.f);
    Assets[3].setTexture(Textures[4]);
    Assets[3].setPosition(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT - 846));

    Textures[5].loadFromFile("./assets/floor.png");
    Assets[5].setTexture(Textures[5]);
    Assets[5].setPosition(Vector2f(0, WINDOW_HEIGHT - 100));
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

    Assets[3].setPosition(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT - 846));
}

void Game::drawBackground(RenderWindow& window)
{
        for (int x = 1; x < 81; x++)
        {
            window.draw(Assets[x]);
        }

}

void Game::GameUpdate(RenderWindow& window)
{
    Object* Peach = new Mario(&window);
    Object* Koppa = new Turtle(&window);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        window.clear();
        Koppa->update();
        drawBackground(window);
        Peach->update();
        
        if (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Right || event.key.code == Keyboard::Left)
                {
                    Peach->animationReset();
                }
            }
        }
        
        
        checkCollusion(Peach, Koppa, side);
        cout << side;

        if (side==2 && !hitFlag) {
            
            hitFlag = true;
            deadTime.restart();
        }
        
        if (hitFlag) //hits mario
        {
            if (deadTime.getElapsedTime().asSeconds() > 3.0f)
            {
                hitFlag = false;
                onFloor(Peach);
            }
        }
        else
        {
            onFloor(Peach);
        }

        turtleCollusion(Koppa);
        window.display();

    }
}

void Game::onFloor(Object* obj)
{
    for (int x = 5; x < 81; x++) {
        FloatRect a = Assets[x].getGlobalBounds();
        FloatRect b = obj->boundingBox();
        sf::FloatRect b_up(b.left, b.top, b.width, 10);
        sf::FloatRect b_down(b.left, b.top + b.height, b.width, 10);
        if (a.intersects(b_down))
        {
            obj->resetVelocity();
            obj->setPosition(Vector2f(obj->getPosition().x,a.top-b.height));

        }
        else if (a.intersects(b_up))
        {
            obj->setPosition(Vector2f(obj->getPosition().x, a.top + a.height));
            obj->resetVelocityFall();
            
        }
    }
}

void Game::turtleCollusion(Object* obj)
{
    sf::FloatRect border_right(1014, 0, 10, 800);
    sf::FloatRect border_left(0, 0, 10, 800);
    sf::FloatRect pipe1(80, 250, 110, 2);
    sf::FloatRect pipe2(870, 250, 35, 2);
    
    for (int x = 5; x < 81; x++) {
        FloatRect a = Assets[x].getGlobalBounds();
        FloatRect b = obj->boundingBox();

        sf::FloatRect pipe3 = Assets[1].getGlobalBounds();
        pipe3.left += b.width*2;
        sf::FloatRect pipe4 = Assets[2].getGlobalBounds();
        pipe4.left -= b.width*2;

        sf::FloatRect b_up(b.left, b.top, b.width, b.height - 10);
        sf::FloatRect b_down(b.left, b.top + b.height, b.width, 10);
        sf::FloatRect b_left(b.left, b.top, 10, b.height);
        sf::FloatRect b_right(b.left+b.width-10, b.top, 10, b.height);

        if (b.intersects(pipe3))
        {
            cout << "ouch";
            obj->setVelocityX();
            obj->resetVelocity();
            obj->setPosition(Vector2f(940, WINDOW_HEIGHT - 846));
        }
        else if (b.intersects(pipe4))
        {
            cout << "ouch";
            obj->setVelocityX();
            obj->setPosition(Vector2f(80, WINDOW_HEIGHT - 846));
        }

        else if (a.intersects(b_down)) //ground
        {
            
            if (b.intersects(border_right))
            {
                obj->setVelocityX();
                obj->setPosition(Vector2f(border_right.left - b.width-10, obj->getPosition().y));
            }
            else if (b.intersects(border_left))
            {
                obj->setVelocityX();
                obj->setPosition(Vector2f(border_left.left + b.width + 10, obj->getPosition().y));
            }

            obj->resetVelocity();
            obj->setPosition(Vector2f(obj->getPosition().x, a.top - b.height));
        }
        else if (b.intersects(pipe1))
        {
            obj->resetVelocity();
            obj->setPosition(Vector2f(obj->getPosition().x, pipe1.top - b.height));
        }
        else if (b.intersects(pipe2))
        {
            obj->resetVelocity();
            obj->setPosition(Vector2f(obj->getPosition().x, pipe2.top - b.height));
        }
    }

}

bool Game::checkCollusion(Object* m, Object* t, int& side)
{
    FloatRect a = t->boundingBox();
    FloatRect b = m->boundingBox();

    sf::FloatRect mario_down(b.left, b.top + b.height-20, b.width, 20);
    sf::FloatRect turtle_up(a.left, a.top, a.width, 20);
    if (mario_down.intersects(turtle_up))
    {
        t->fall();
        side = 1; //turtle dead
        return true;
    }
    else if (a.intersects(b))
    {
        m->fall();
        side = 2; //mario dead
        return true;
    }
    side = 0;
    return false;
}
