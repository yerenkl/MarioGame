#pragma once
#include "Turtle.h"

Turtle::Turtle(RenderWindow* window,int heading=1,float vx=TURTLE_SPEED) : Object(window)
{
    isVulnerable = false;
    vy = 0;
    stop = false;
    collusion = false;
    frame = 7;
    sprite.setTexture(textures[frame]);
    if(heading==1) //which pipe to spawn
        pos = Vector2f(80,250);
    else
        pos= Vector2f(870, 250);
    sprite.setPosition(pos);
    animationTimer.restart();
    this->heading = heading;
    this->vx = heading*vx;
    clock.restart();
}

void Turtle::fall(void)
{
    frame = 11;
    sprite.setTexture(textures[frame]);
    dead = true;
    vx = 0;
    vy = 10;
}

void Turtle::vulnerable(void)
{
    vy = -10.8;
    frame = 11;
    sprite.setTexture(textures[frame]);
    if (!isVulnerable)
    {
        isVulnerable = true;
        vulnerableTime.restart();
    }
    else 
    {
        isVulnerable = false;
        vulnerableTime.restart();
    }
    
}

void Turtle::update()
{
    
    if (stop && !isVulnerable)
    {
        sprite.setTexture(textures[frame]);
        if(surpriseTime.getElapsedTime().asSeconds()>0.5)
        {
            stop = false;
            frame = 7;
        }
    }
    else
    {
        updatePhysics();
    }

    if(isVulnerable && vulnerableTime.getElapsedTime().asSeconds()>8)
    {
        isVulnerable = false;
    }

    if (!dead && !isVulnerable)
    {
        Vector2f position;
        float elapsed1 = clock.getElapsedTime().asSeconds();
        position = sprite.getPosition();
        if (heading == 1) {
            sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
            sprite.setScale(1.f, 1.f);
        }
        else {
            sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
            sprite.setScale(-1.f, 1.f);
        }

        sprite.setTexture(textures[frame]);
        if (elapsed1 > 0.5)
        {
            if (frame < 9) {
                frame++;
            }
            else
            {
                frame = 7;
            }
            clock.restart();
        }
    }
    
    draw();
}

void Turtle::surprised(void)
{
    stop = true;
    frame = 10;
    surpriseTime.restart();
}

void Turtle::updatePhysics()
{
    vy += 0.5;
    
    if (vy > VELOCITY_Y && !dead)
    {
        vy = VELOCITY_Y;
    }
    if (isVulnerable)
        sprite.move(Vector2f(0, vy));
    
    else
        sprite.move(Vector2f(vx, vy));
}
