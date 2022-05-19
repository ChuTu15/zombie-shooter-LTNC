#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>

using namespace sf;

class Player
{
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;

    //where the player is
    Vector2f p_position;


    Sprite p_Sprite;
    Texture p_Texture;

    //what size is the current arena
    IntRect p_Arena;

    //what is the screen resolution
    Vector2f p_Resolution;

    //How big is each tile of the arena
    int p_TileSize;

    //which direction is the player facing
    bool p_FacingRight;
    bool p_FacingUp;
    bool p_FacingDown;
    bool p_FacingLeft;

    //player health
    int p_Health;
    int p_MaxHealth;

    //when was the player last hit
    Time p_LastHit;

    //player speed
    float p_Speed;

public:
    Player();

    void spawn(IntRect arena, Vector2f resolution, int tileSize);

    void resetPlayerStats();
    bool hit(Time timeHit);
    Time getLastHitTime();

    FloatRect getPosition(); //where is the player
    Vector2f getCenter(); //where is the center of the player

    float getRotation(); //what is the rotation of the player

    Sprite getSprite();

    //functions to move the player
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    //stop the player from moving
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();

    //update the player
    void update(float elapsedTime, Vector2i mousePos);

    //give the player health
    void upgradeHealth();

    //get the player speed
    void upgradeSpeed();

    //increase the player health
    void increaseHealth(int amount);

    //How much health has the player currently got?
    int getHealth();
};

#endif // PLAYER_H_INCLUDED
