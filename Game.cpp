#pragma once
#include "Game.h"
#include "Mario.h"
#include "Turtle.h"
#include "Object.h"
#include "ScoreBoard.h"

Game::Game()
{   
    gamewin = false; 
    gameover = false;
    gamestart = false; //start screen or game screen

    score = 0; //initial score

    //fonts, textures and strings loaded
    fonts[0].loadFromFile("./assets/font.ttf");
    fonts[1].loadFromFile("./assets/04B_30__.TTF");
    
    text[0].setFont(fonts[0]);
    text[0].setPosition(50, 50);
    text[1].setFont(fonts[0]);
    text[1].setScale(2.f, 2.f);
    text[2].setFont(fonts[1]);

    text[2].setString("Press Enter!");
    text[2].setScale(1.5f, 1.5f);
    text[2].setPosition(512- text[2].getGlobalBounds().width / 2, 350);

    text[3].setFont(fonts[1]);
    text[3].setString("SUPER MARIO");
    text[3].setScale(2.5f, 2.5f);
    text[3].setPosition(512-text[3].getGlobalBounds().width/2, 250);
    text[3].setFillColor(sf::Color::Red);

    Textures[0].loadFromFile("./assets/brick.png");
    Assets[0].setTexture(Textures[0]);


    Textures[1].loadFromFile("./assets/pipe.png");
    Assets[1].setTexture(Textures[1]);
    Assets[1].setPosition(Vector2f(894, 850));

    Assets[2].setTexture(Textures[1]);
    Assets[2].setScale(-1.f, 1.f);
    Assets[2].setPosition(Vector2f(130, 850));


    Textures[4].loadFromFile("./assets/pipeS.png");
    Assets[4].setPosition(Vector2f(0, 178));
    Assets[4].setTexture(Textures[4]);

    Assets[3].setScale(-1.f, 1.f);
    Assets[3].setTexture(Textures[4]);
    Assets[3].setPosition(Vector2f(1024, 178));

    Textures[5].loadFromFile("./assets/floor.png");
    Assets[5].setTexture(Textures[5]);
    Assets[5].setPosition(Vector2f(0, 924));

    Textures[7].loadFromFile("./assets/start_screen.png");
    Assets[85].setScale(Vector2f(1.5f, 1.5f));
    Assets[85].setTexture(Textures[7]);
    Assets[85].setOrigin(Assets[85].getLocalBounds().width / 2.f, 0.f);
    Assets[85].setPosition(Vector2f(512, 100));

    Textures[8].loadFromFile("./assets/background.png");
    Assets[86].setTexture(Textures[8]);
    Assets[86].setPosition(Vector2f(0, 300));

    for (int x = 6; x < 81; x++)
    {
        Assets[x].setTexture(Textures[0]);
    }

    for (int x = 0; x < 16; x++)
    {
        Assets[x + 6].setPosition(Vector2f(272 + x * 30, 530));
    }
    for (int x = 0; x < 12; x++)
    {
        Assets[x + 22].setPosition(Vector2f(x * 30, 730));
        Assets[x + 34].setPosition(Vector2f(994 - (x * 30), 730));
    }
    for (int x = 0; x < 4; x++)
    {
        Assets[x + 46].setPosition(Vector2f(1024 - 30 - (x * 30), 570));
        Assets[x + 50].setPosition(Vector2f((x * 30), 570));
    }
    for (int x = 0; x < 14; x++)
    {
        Assets[x + 54].setPosition(Vector2f(994 - (x * 30), 330));
        Assets[x + 68].setPosition(Vector2f((x * 30), 330));
    }

    Assets[3].setPosition(Vector2f(1024, 178));

    Textures[6].loadFromFile("./assets/mariohead.png");
    Assets[82].setTexture(Textures[6]);
    Assets[82].setPosition(Vector2f(50, 100));

    Assets[83].setTexture(Textures[6]);
    Assets[83].setPosition(Vector2f(90, 100));

    Assets[84].setTexture(Textures[6]);
    Assets[84].setPosition(Vector2f(130, 100));
}

void Game::drawBackground(RenderWindow& window)
{       
    //this method draws the background objects to the window
    text[0].setString(board->getScore());
    window.draw(text[0]);
    for (int x = 1; x < 85; x++)
    {
        window.draw(Assets[x]);
    }
}

void Game::GameUpdate(RenderWindow& window)
{
    float elapsedTime = 5; //initial game time
    LinkedList* spawner=new LinkedList(&window);
    
    Object* Peach = new Mario(&window);

    float a=TURTLE_SPEED; 
    int b=1; //Turtle eading
    TurtleTime.restart();

    board = new ScoreBoard();

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        window.clear();


        //Game End Conditions
        if (board->getLives() == 0 )
        {
            if (gameover = false)
            {
                delete Peach;
            }
            gameover = true;
            text[1].setString("GAMEOVER");
            text[1].setPosition(512 - text[1].getGlobalBounds().width / 2, 400);
            window.draw(text[1]);
        }
        else if (board->getScore() == "00500")
        {
            if (gameover = false)
            {
                delete Peach;
            }
            gamewin = true;
            text[1].setString("YOU WIN!");
            text[1].setPosition(512 - text[1].getGlobalBounds().width / 2, 400);
            window.draw(text[1]);
        }

        //Game Continues
        if (gamestart)
        {
            
            if (TurtleTime.getElapsedTime().asSeconds() > 3 && !gameover && !gamewin)
            {
                //spawns turtle until desired number of turtles are created.
                if(spawner->elementNumber()<5)
                    spawner->insertTurtle(b, 1);
                b = -b;
                TurtleTime.restart();
            }
            spawner->velocitySet(a);
            a += 0.001; //increases the speed of turtle as the time goes on
            if(!gamewin && !gameover)
                restartTime.restart();
            spawner->drawAll();
            drawBackground(window);
            Peach->update();

            int x=onFloor(Peach); //Number of the tile mario hitted
            Object* temp = spawner->head;

            while (temp != nullptr)
            {
                Object* temp2 = temp->next;
                while (temp2 != nullptr)
                {

                    Turtle* turtle1 = dynamic_cast<Turtle*>(temp);
                    Turtle* turtle2 = dynamic_cast<Turtle*>(temp2);
                    // Check for collision between temp and temp2 turtles
                    if (turtleCollusion(turtle1, turtle2))
                    {
                        turtle1->surprised();
                        turtle2->surprised();
                    }
                    isturtleOn(turtle1, x);
                    temp2 = temp2->next;
                }

                checkCollusion(Peach, temp);
                turtleFloor(temp);
                temp = temp->next;
            }
        }

        if(gamewin || gameover)
        {
            //Wait for 3 seconds until going back to main screen
            if (restartTime.getElapsedTime().asSeconds() >= 3)
            {
                gamestart = false;
                elapsedTime = 5;
            }
        }

        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Right || event.key.code == Keyboard::Left)
                {
                    //Slide when key released.
                    Peach->animationReset();
                }
            }
        }
        if (!gamestart && restartTime.getElapsedTime().asSeconds()+elapsedTime >= 5)
        {
            //Main menu
            window.clear();
            window.draw(text[2]);
            window.draw(text[3]);
            window.draw(Assets[86]);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                //create new game
                spawner->destroyAll();
                gameover = false;
                gamewin = false;
                score = 0;
                gamestart = true;
                elapsedTime = 0;
                a = 1;
                delete board;
                Assets[82].setPosition(Vector2f(50, 100));
                Assets[83].setPosition(Vector2f(90, 100));
                Assets[84].setPosition(Vector2f(130, 100));
                Peach = new Mario(&window);
                board = new ScoreBoard();
            }
        }

        window.display();

    }
}

int Game::onFloor(Object* obj)
{
   /* Checks the collusion of the Mario and the floor.
    Returns the number of the collided tile. */

    for (int x = 5; x < 81; x++) {
        FloatRect a = Assets[x].getGlobalBounds();
        FloatRect b = obj->boundingBox();

        //Mario is seperated to two parts
        sf::FloatRect b_up(b.left, b.top, b.width, 10);
        sf::FloatRect b_down(b.left, b.top + b.height, b.width, 10);
        if (a.intersects(b_down))
        {
            obj->resetVelocity();
            obj->setPosition(Vector2f(obj->getPosition().x,a.top-b.height));
        }
        else if (a.intersects(b_up) && !obj->dead)
        {
            obj->setPosition(Vector2f(obj->getPosition().x, a.top + a.height));
            obj->resetVelocityFall();
            return x;
            
        }
    }
    return 0;
}

void Game::turtleFloor(Object* obj)
{
    /* Checks the collusion of the Turtle and the floor.*/
    
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
            obj->setVelocityX(-1);
            obj->resetVelocity();
            obj->setPosition(Vector2f(940, WINDOW_HEIGHT - 846));
        }
        else if (b.intersects(pipe4))
        {
            obj->setVelocityX(-1);
            obj->setPosition(Vector2f(80, WINDOW_HEIGHT - 846));
        }

        else if (a.intersects(b_down)) //ground
        {
            
            if (b.intersects(border_right))
            {
                /* When turtle comes to window edge it turns otherside.*/
                obj->setVelocityX(-1);
                obj->setPosition(Vector2f(border_right.left - b.width-10, obj->getPosition().y));
            }
            else if (b.intersects(border_left))
            {
                /* When turtle comes to window edge it turns otherside.*/
                obj->setVelocityX(-1);
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

bool Game::turtleCollusion(Turtle* obj1, Turtle* obj2)
{
    /* Checks the collusion of two turtles. Returns True if they collide.*/
    FloatRect a = obj1->boundingBox();
    FloatRect b = obj2->boundingBox();

    sf::FloatRect turtle1Left(a.left, a.top, 10, a.height);
    sf::FloatRect turtle1Right(a.left+a.width-10, a.top, 10, a.height);

    sf::FloatRect turtle2Left(b.left, b.top, 10, b.height);
    sf::FloatRect turtle2Right(b.left + b.width - 10, b.top, 10, b.height);
    if (turtlehitTime.getElapsedTime().asSeconds() > 2.f && obj1->collusion)
    {
        /* Wait for 2 seconds until next collision check.*/
        obj1->collusion = false;
    }

    if ((turtle1Left.intersects(turtle2Right) || turtle2Left.intersects(turtle1Right)) && !obj1->collusion && !obj1->dead && !obj2->dead)
    {
        obj1->collusion = true;

        /* Change the directions of the turtles .*/
        obj1->setVelocityX(-1);
        obj2->setVelocityX(-1);
        turtlehitTime.restart();
        return true;
    }
    return false;
}

void Game::checkCollusion(Object* m, Object* t)
{
    /* Checks the collusion of Mario and Turtles .*/
    FloatRect a = t->boundingBox();
    FloatRect b = m->boundingBox();

    sf::FloatRect mario_down(b.left, b.top + b.height-20, b.width, 20);
    sf::FloatRect turtle_up(a.left, a.top, a.width, 20);


    if (mario_down.intersects(turtle_up) && !m->dead && !t->dead)
    {
        /* If Mario beats the turtle */
        t->fall();
        m->turtleJump();
        score += 100;
        board->setScore(score);
    }
    else if (a.intersects(b) && !m->dead && !t->dead)
    {
        /* If Mario get hit by Turtle */
        m->fall();
        Assets[81 + board->getLives()].setPosition(-500, -500);
        board->setLives(board->getLives()-1);
    }
}

void Game::isturtleOn(Turtle* obj1,int x)
{
    /* Checks if a turtle is on specific tile. Turtle is vulnerable if yes */
    FloatRect a = Assets[x].getGlobalBounds();
    FloatRect b = obj1->boundingBox();
    if (a.intersects(b))
    {
        obj1->vulnerable();
    }
}