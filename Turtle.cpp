#pragma once
#include "Turtle.h"

enum STATES { MOVE = 0, VULNERABLE, SURPRISE, FALL};

Turtle::Turtle(RenderWindow* window,int heading=1,float vx=TURTLE_SPEED) : Object(window)
{
    vy = 0;
    collusion = false;
    frame = 7;
    state = MOVE;
    sprite.setTexture(textures[frame]);
    if(heading==1) //which pipe to spawn
        pos = Vector2f(80,250);
    else
        pos= Vector2f(870, 250);
    sprite.setPosition(pos);
    this->heading = heading;
    this->vx = heading*vx;
    animationTimer.restart();
}

void Turtle::fall(void)
{
    frame = 11;
    state = FALL;
    sprite.setTexture(textures[frame]);
    dead = true;
    vx = 0;
    vy = 10;
}

void Turtle::vulnerable(void)
{
    if (state!=VULNERABLE)
    {
        state = VULNERABLE;
        frame = 11;
        sprite.setTexture(textures[frame]);
        vy = -10.8;
        vulnerableTime.restart();
    }
    
}

void Turtle::update()
{
    if (state==SURPRISE)
    {
        sprite.setTexture(textures[frame]);
        if(surpriseTime.getElapsedTime().asSeconds()>0.5)
        {
            state=MOVE;
            frame = 7;
        }
    }
    else
    {
        updatePhysics();
    }

    if(state==VULNERABLE && vulnerableTime.getElapsedTime().asSeconds()>8)
    {
        state = MOVE;
    }

    if (state==MOVE)
    {
        Vector2f position;
        float elapsed1 = animationTimer.getElapsedTime().asSeconds();
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
            animationTimer.restart();
        }
    }
    
    draw();
}

void Turtle::surprised(void)
{
    if (state != VULNERABLE)
    {
        state = SURPRISE;
        frame = 10;
        surpriseTime.restart();
    }
}

void Turtle::updatePhysics()
{
    vy += 0.5;
    
    if (vy > VELOCITY_Y && state!=FALL)
    {
        vy = VELOCITY_Y;
    }
    if (state==VULNERABLE)
        sprite.move(Vector2f(0, vy));
    
    else
        sprite.move(Vector2f(vx, vy));
}
