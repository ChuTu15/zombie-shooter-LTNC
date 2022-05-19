#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private:
    //where is bullet
    Vector2f b_Position;

    //shape of bullet
    RectangleShape b_BulletShape;

    //bullet in air?
    bool b_InFlight = false;

    //speed of bullet
    float b_BulletSpeed = 1000;

    float b_BulletDistanceX;
    float b_BulletDistanceY;

    //bullet does not fly forever
    float b_MaxX;
    float b_MinX;
    float b_MaxY;
    float b_MinY;

public:
    //the constructor
    Bullet();

    void stop();

    bool isInFlight();

    //launch a new bullet
    void shoot(float startX, float startY, float targetX, float targetY);

    FloatRect getPosition();
    RectangleShape getShape();

    //update the bullet each frame
    void update(float elapsedTime);
};
#endif // BULLET_H_INCLUDED
