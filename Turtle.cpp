#include "Turtle.h"

Turtle::Turtle(RenderWindow* window) : Object(window)
{
    vy = 0;
    frame = 7;
    sprite.setTexture(textures[frame]);
    pos = Vector2f(500,500);
    setPosition(pos);
    animationTimer.restart();
    heading = -1;
    vx = heading*TURTLE_SPEED;
    clock.restart();
}


void Turtle::fall(void)
{
    dead = true;
    vx = 0;
    vy = 10;
}

void Turtle::update()
{
    updatePhysics();
    if (!dead)
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
    
    draw(*window);
}

void Turtle::updatePhysics()
{
    vy += GRAVITY;
    if (vy > VELOCITY_Y && !dead)
    {
        vy = VELOCITY_Y;
    }
    sprite.move(Vector2f(vx, vy));
}
