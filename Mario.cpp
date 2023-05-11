#include "Mario.h"


Mario::Mario(RenderWindow* window) : Object(window)
{
	vx = 0;
    isJumping = false;
    sprite.setTexture(textures[0]);

    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
    sprite.setPosition(pos);
    
}

void Mario::move(int direction)
{   
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
    Vector2f position;
    if (direction == LEFT)
    {
        printf("moving");
        position = getPosition();
        vx +=2 ;
        if(vx>=VELOCITY_X)
        {
            vx = VELOCITY_X;
        }
        position.x = position.x - vx;
        setPosition(position);
        if(isJumping==false)
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

        if (heading == LEFT ) {
            heading = RIGHT;
        }
    }
    if (direction == RIGHT)
    {
        printf("moving");
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
    if (!isJumping && ground)
    {
        isJumping = true;
        vy = 35;
        sprite.setTexture(textures[5]);
    }

    if (isJumping)
    {
        state = 5;
        position = getPosition();
        vy -= 2;
        if (vx <= -5)
        {
            vx = -5;
        }
        if (vx >= 5)
        {
            vx = 5;
        }
        position.y -= vy;
        position.x -= vx;
        printf("jumping");
        setPosition(position);

        if (getPosition().y > 500) {
            position.y = 500;
            setPosition(position);
            vy = 0;
            sprite.setTexture(textures[0]);
            isJumping = false;

        }
    }

}