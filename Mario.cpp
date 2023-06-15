#pragma once
#include "Mario.h"

enum STATES { IDLE = 0, LEFT, RIGHT, JUMP ,FALL, SLIDE};

Mario::Mario(sf::RenderWindow* window) : Object(window)
{
    isRunning = false;
    state = IDLE;
    vx = 0;
    vy = 0;
    isJumping = false;
    acc = ACCELERATION;
    g = GRAVITY;
    pos = Vector2f(510, 700);
    sprite.setTexture(textures[0]);
    sprite.setPosition(pos);
}

void Mario::animationReset()
{
    //Resets animation when buttons released
    vx = 0;
    if (isRunning && !isJumping && !dead) {
        isRunning = false;
        animationTimer.restart();
        frame = 4;
        state = SLIDE;
        sprite.setTexture(textures[frame]);
    }
}

void Mario::move(const float dir_x, const float dir_y)
{
    //Makes Mario move horizontally, dir_x=direction on x
    vx += dir_x*acc;
    
    if(dir_y)
    {
        vy = -VELOCITY_Y;
    }
    if (abs(vx) > VELOCITY_X) 
    {
        vx = dir_x*VELOCITY_X;
    }
}

void Mario::jump(const float dir_x, const float dir_y)
{
    //Makes Mario jump
    vx += dir_x * 3;

    vy = -VELOCITY_Y;
    
    if (abs(vx) > VELOCITY_X/3)
    {
        vx = dir_x * VELOCITY_X/3;
    }
}

void Mario::fall(void)
{
    //Mario falls of the screen
    if (state!= FALL)
    {
        vy = VELOCITY_Y;
        state = FALL;
        frame = 6;
        sprite.setTexture(textures[frame]);
        animationTimer.restart();
        dead = true;
    }
}

void Mario::updateMove()
{
    //Calls the necessary movement functions (move or jump) based on buttons.
    if(!isJumping)
        state = IDLE;

    if (state == SLIDE)
    {
        frame = 4;
        if (animationTimer.getElapsedTime().asSeconds() >= 1.f)
        {
            frame = 0;
            state = IDLE;
        }
        sprite.setTexture(textures[frame]);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isJumping == false)
    {
        state = JUMP;
        isJumping = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            jump(1, 1);
            heading = 1;
            
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            jump(-1, 1);
            heading = -1;

        }
        else
        {
            jump(0, 1);
        }
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && isJumping==false)
    {
        move(1, 0);
        heading = 1;
        state = RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && isJumping == false)
    {
        move(-1, 0);
        heading = -1;
        state = LEFT;
    }

}

void Mario::updatePhysics()
{
    //Applies gravitational forces to the Mario.
    vy += g;
    if (vy > VELOCITY_Y && dead)
    {
        vy = VELOCITY_Y;
    }
    if (vy < -VELOCITY_Y)
    {
        vy = -VELOCITY_Y;
    }
    sprite.move(Vector2f(vx, vy));
}

void Mario::update()
{   
    //Updates Mario’s movement, physics and animations.
    if (state != FALL)
    {
        updateMove();
    }
    updatePhysics();
    animationUpdate();
    draw();
} 

void Mario::animationUpdate()
{
    //Updates Mario's animations
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
    
    if (state == IDLE)
    {
        if (animationTimer.getElapsedTime().asSeconds() >= 0.1f)
        {
            frame = 0;
            sprite.setTexture(textures[frame]);
        }
            
    }
    else if (state == RIGHT)
    {
        if (animationTimer.getElapsedTime().asSeconds() >= 0.1f)
        {
            frame++;
            if (frame > 3)
            {
                frame = 1;
                isRunning = true;
            }
                
            animationTimer.restart();
            sprite.setScale(-1.f, 1.f);

            sprite.setTexture(textures[frame]);
        }
    }
    else if (state == LEFT)
    {
        if (animationTimer.getElapsedTime().asSeconds() >= 0.2f)
        {
            frame++;
            if (frame > 3)
            {
                frame = 1;
                isRunning = true;
            }
            sprite.setScale(1.f, 1.f);
            animationTimer.restart();
            sprite.setTexture(textures[frame]);
        }
    }
 
    else if (state == JUMP)
    {
        if (animationTimer.getElapsedTime().asSeconds() >= 0.2f)
        {
            frame = 5;
            sprite.setScale(-1.f, 1.f);
            animationTimer.restart();
            sprite.setTexture(textures[frame]);
        }
    }
    else if (state == FALL)
    {
        if (animationTimer.getElapsedTime().asSeconds() > 3.f)
        {
            dead = false;
            state = IDLE;
            frame = 0;
            sprite.setTexture(textures[frame]);
            setPosition(Vector2f(512,700));
        }
    }
    if (heading == 1) {
        sprite.setScale(-1.f, 1.f);
    }
    else {
        sprite.setScale(1.f, 1.f);
    }
}