#pragma once
#include "Object.h"

Object::Object(RenderWindow* window) 
{
	this->window = window;
	for (int x = 1; x < 8; x++) {
		textures[x - 1].loadFromFile("./assets/mario" + std::to_string(x) + ".png");
	}
	for (int x = 1; x < 6; x++) {
		textures[x+6].loadFromFile("./assets/turtle" + std::to_string(x) + ".png");
	}
	state = 0;
	heading = 1;
}
void Object::setPosition(sf::Vector2f pos) 
{
	this->pos = pos;
	sprite.setPosition(pos);
}

Vector2f Object::getPosition()
{
	return pos;
}

void Object::draw(RenderWindow& window)
{	
	window.draw(sprite);
}

IntRect Object::boundingBox(void)
{
    sf::Rect<float> rec= this->sprite.getGlobalBounds();
    return static_cast<IntRect>(rec);
}

Mario::Mario(RenderWindow* window) : Object(window)
{
    vx = 0;
    isJumping = true;
    sprite.setTexture(textures[0]);
    vy = 0;
    pos = Vector2f(540, 1080 - 300);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
    sprite.setPosition(pos);
    lives = 3;
    Clock clock;
}

void Mario::move(int direction)
{
    
    if (state != 6)
    {
        sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
        Vector2f position;
        float elapsed1 = clock.getElapsedTime().asSeconds();
        if (direction == LEFT)
        {
            position = getPosition();
            vx += 1;
            if (vx >= VELOCITY_X)
            {
                vx = VELOCITY_X;
            }
            position.x = position.x - vx;
            setPosition(position);
            if (elapsed1 > 0.1 && isJumping == false)
            {
                if (state <= 3 && state > 0)
                {
                    state++;
                }
                else
                {
                    state = 1;
                }
                clock.restart();
            }
            if (heading == LEFT) {
                heading = RIGHT;
            }
        }

        if (direction == RIGHT)
        {
            position = getPosition();
            vx -= 2;
            if (vx <= -VELOCITY_X)
            {
                vx = -VELOCITY_X;
            }
            position.x = position.x - vx;
            setPosition(position);
            if (elapsed1 > 0.1 && isJumping == false)
            {
                if (state <= 3 && state > 0)
                {
                    state++;
                }
                else
                {
                    state = 1;
                }
                clock.restart();
            }
            if (heading == RIGHT) {
                heading = LEFT;
            }
        }
        if (direction == STOP)
        {
            if (!isJumping)
            {
                state = 0;
            }
            vx = 0;
        }


        sprite.setTexture(textures[state]);


        if (heading == LEFT) {
            sprite.setScale(-1.f, 1.f);
        }
        else {
            sprite.setScale(1.f, 1.f);
        }
    }
    
}



void Mario::jump(bool ground) //on ground and not jumping
{
    Vector2f position;
    
    if(ground && !isJumping && state!=6)
    {       
        isJumping = true;
        vy = VELOCITY_Y;
        state = 5;
        sprite.setTexture(textures[state]);
        jumped.restart();
    }
    

}

void Mario::fall(void) {
    vy = -VELOCITY_Y;
    state = 6;
    sprite.setTexture(textures[state]);
    Vector2f position = getPosition();
    position.y -= vy;
    setPosition(position);
    clock.restart();
    if (lives == 0) 
    {
        cout << "GAMEOVER";
    }
}



void Mario::update(int ground)
{
    Vector2f position;

    if (state != 6) 
    {
        if (ground == 2)
        {
            vy = -2;

            isJumping = true;
            state = 5;
        }
        if (ground == 4)
        {
            vy = -5;
            vx = 0;
            isJumping = true;
            state = 0;
        }
        if (!isJumping && !ground)
        {
            isJumping = true;
            state = 5;
        }
        if (isJumping || ground == 0)
        {
            position = getPosition();
            vy -= 0.2;
            if (vx <= -1)
            {
                vx = -1;
            }
            if (vx >= 1)
            {
                vx = 1;
            }
            if (vy <= -VELOCITY_Y)
            {
                vy = -VELOCITY_Y;
            }

            if (isJumping && ground == 1 && jumped.getElapsedTime().asSeconds() > 0.0001) {
                cout << isJumping;
                sprite.setTexture(textures[0]);
                isJumping = false;
                vy = 0;
            }
            position.y -= vy;
            position.x -= vx;
            setPosition(position);
        }
    }
    else
    {
        position = getPosition();
        position.y -= vy;
        setPosition(position);
        float elapsed1 = clock.getElapsedTime().asSeconds();
        if(elapsed1 > 2 && lives != 0)
        { //revive time
            lives--;
            vx = 0;
            isJumping = true;
            state = 0;
            sprite.setTexture(textures[state]);
            vy = 0;
            pos = Vector2f(540, 1080 - 300);
            sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
            sprite.setPosition(pos);
        }
    }
    
}

Turtle::Turtle(RenderWindow* window) : Object(window)
{
    vx = 5;
    vy = 6;
    state = 7;
    sprite.setTexture(textures[state]);
    pos = Vector2f(80, WINDOW_HEIGHT - 846);
    setPosition(pos);
    sf::Clock clock;
    heading = RIGHT;
}

void Turtle::update(int ground)
{
    Vector2f position;
    float elapsed1 = clock.getElapsedTime().asSeconds();
    position = getPosition();
    if (position.x >= 950 || position.x <= 50) {

        vx = -vx;
        
        if(position.y == 850)
        {
            position.x = 80;
            position.y = WINDOW_HEIGHT - 846;
        }
        if (heading == LEFT) {
            sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
            sprite.setScale(1.f, 1.f);
            heading = RIGHT;
        }
        else {
            sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
            sprite.setScale(-1.f, 1.f);
            heading = LEFT;
        }
    }


    if (ground) {
        position.x += vx;
        sprite.setTexture(textures[state]);
        if(elapsed1 > 0.5)
        {
            if (state < 9) {
                state++;
            }
            else
            {
                state = 7;
            }
            clock.restart();
        }

    }

    else
    {
        position.y = position.y + vy;
    }


    setPosition(position);
}