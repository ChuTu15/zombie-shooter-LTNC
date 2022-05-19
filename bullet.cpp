#include "header/bullet.h"

using namespace sf;

//the constructor
Bullet::Bullet()
{
    b_BulletShape.setSize(sf::Vector2f(7, 7));
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY)
{
    b_InFlight = true;
    b_Position.x = startX;
    b_Position.y = startY;

    //Calculate the gradient of the flight path
    float gradient = (startX - targetX) / (startY - targetY);
    if (gradient < 0)
    {
        gradient *= -1;
    }
    float ratioXY = b_BulletSpeed / (1 + gradient);
    b_BulletDistanceY = ratioXY;
    b_BulletDistanceX = ratioXY * gradient;

    if (targetX < startX)
    {
        b_BulletDistanceX *= -1;
    }
    if (targetY < startY)
    {
        b_BulletDistanceY *= -1;
    }

    //set a max range of 1000 pixels in any direction
    float range = 1000;
    b_MinX = startX - range;
    b_MaxX = startX + range;
    b_MinY = startY - range;
    b_MaxY = startY + range;

    //position the bullet ready to be drawn
    b_BulletShape.setPosition(b_Position);
}

void Bullet::stop()
{
    b_InFlight = false;
}

bool Bullet::isInFlight()
{
    return b_InFlight;
}

FloatRect Bullet::getPosition()
{
    return b_BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape()
{
    return b_BulletShape;
}

void Bullet::update(float elapsedTime)
{
    //update the bullet position
    b_Position.x += b_BulletDistanceX * elapsedTime;
    b_Position.y += b_BulletDistanceY * elapsedTime;

    //move the bullet
    b_BulletShape.setPosition(b_Position);

    //bullet gone out or range
    if (b_Position.x < b_MinX || b_Position.x > b_MaxX ||
        b_Position.y < b_MinY || b_Position.y > b_MaxY)
    {
        b_InFlight = false;
    }
}
