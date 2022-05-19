#pragma once
#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

#include <SFML/Graphics.hpp>

using namespace sf;

class zombie
{
private:
    //speed of each zombie
    const float BLOATER_SPEED = 40;
    const float CHASER_SPEED = 80;
    const float CRAWLER_SPEED = 30;

    //health of each zombie
    const float BLOATER_HEALTH = 5;
    const float CHASER_HEALTH = 1;
    const float CRAWLER_HEALTH = 3;

    //Make each zombie vary its speed slightly
    const int MAX_VARRIANCE = 30;
    const int OFFSET = 101 - MAX_VARRIANCE;

    //position of zombie
    Vector2f z_Position;

    //A sprite for the zombie;
    Sprite z_Sprite;

    //How fast can this one run/crawl?
    float z_Speed;

    //How much health has it got?
    float z_Health;

    //Is it still alive;
    bool z_Alive = true;

public:
    //Handle when a bullet hits a zombie
    bool hit();

    //Find out if the zombie is alive
    bool isAlive();

    //spawn a new zombie
    void spawn(float startX, float startY, int type, int seed);

    //return a rectangle that is the position in the world
    FloatRect getPosition();

    //get a copy of the sprite to draw
    Sprite getSprite();

    //update frame
    void update(float elapsedTime, Vector2f playerLocation);


};

#endif // ZOMBIE_H_INCLUDED
