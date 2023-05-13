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
    isJumping = false;
    sprite.setTexture(textures[0]);
    vy = 0;
    pos = Vector2f(540, 1080 - 300);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
    sprite.setPosition(pos);

}

void Mario::move(int direction)
{
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
    Vector2f position;
    if (direction == LEFT)
    {
        position = getPosition();
        vx +=1;
        if (vx >= VELOCITY_X)
        {
            vx = VELOCITY_X;
        }
        position.x = position.x - vx;
        setPosition(position);
        if (isJumping == false)
        {
            if (state <= 3 && state > 0)
            {
                state++;
            }
            else
            {
                state = 1;
            }
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
        if (isJumping == false)
        {
            if (state <= 3 && state > 0)
            {
                state++;
            }
            else
            {
                state = 1;
            }
        }
        if (heading == RIGHT) {
            heading = LEFT;
        }
    }
    if (direction == STOP)
    {
        state = 0;
        vx = 0;
    }

    if (!isJumping)
    {
        sprite.setTexture(textures[state]);
    }

    if (heading == LEFT) {
        sprite.setScale(-1.f, 1.f);
    }
    else {
        sprite.setScale(1.f, 1.f);
    }
}

void Mario::jump(bool ground)
{
    Vector2f position;
    
    if(ground && !isJumping)
    {       
        isJumping = true;
        vy = 10;
        sprite.setTexture(textures[5]);
        state = 5;
    }
    

}

void Mario::fall(void) {
    vy = -10;
    sprite.setTexture(textures[6]);
    Vector2f position = getPosition();
    position.y -= vy;
    setPosition(position);
}

void Mario::update(bool ground, bool u_g)
{
    Vector2f position;

    if (!u_g)
    {
        printf("jesus");
        vy = -1.7;
        isJumping = false;
    }

    if (!isJumping && ground)
    {
        sprite.setTexture(textures[state]);
        vy = 0;
    }
    
    else if (isJumping || !ground || !u_g)
    {
        position = getPosition();
        vy -= 0.2;
        if (vx <= -2.5)
        {
            vx = -2.5;
        }
        if (vx >= 2.5)
        {
            vx = 2.5;
        }
        if (vy >= 12)
        {
            vy= 12;
        }
        if (vy <= -12)
        {
            vy = -12;
        }
        position.y -= vy;
        position.x -= vx;
        setPosition(position);
        if (ground) {
            state = 0;
            isJumping = false;
            
        }
    }
}

Turtle::Turtle(RenderWindow* window) : Object(window)
{
    vx = 1;
    vy = 6;
    state = 7;
    sprite.setTexture(textures[state]);
    pos = Vector2f(50, WINDOW_HEIGHT - 846);
    sprite.setPosition(pos);
    sf::Clock clock;
}

void Turtle::update(bool ground, bool u_g)
{
    Vector2f position;
    float elapsed1 = clock.getElapsedTime().asSeconds();
    position = getPosition();
    if (ground) {
        position.x = position.x + vx;
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