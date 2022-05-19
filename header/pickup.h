#ifndef PICKUP_H_INCLUDED
#define PICKUP_H_INCLUDED

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
private:
    //start value for pickups
    const int HEALT_VALUE = 50;
    const int AMMO_VALUE = 12;
    const int START_WAIT_TIME = 10;
    const int START_SECONDS_TO_LIVE = 5;

    Sprite pi_Sprite;
    IntRect pi_Arena;

    //How much is this pickup worth?
    int pi_Value;

    //what type of pickup is this?
    //1 = health; 2 = ammo
    int pi_Type;

    // Handle spawning and disappearing
    bool pi_Spawned;
    float pi_SecondsSinceSpawn;
    float pi_SecondsSinceDeSpawn;
    float pi_SecondsToLive;
    float pi_SecondsToWait;

public:
    Pickup(int type);

    //prepare a new pickup
    void setArena(IntRect arena);
    void spawn();

    //check the position of a pickup
    FloatRect getPosition();

    //get the sprite for drawing
    Sprite getSprite();

    //update each frame
    void update(float elapsedTime);

    //Is this pickup currently spawned?
    bool isSpawned();

    //get the goodness from the pickup
    int gotIt();

    //upgrade the value of each pickup
    void upgrade();
};

#endif // PICKUP_H_INCLUDED
