#include "header/pickup.h"
#include "header/TextureHolder.h"
#include <iostream>

Pickup::Pickup(int type)
{
    pi_Type = type;

    if (pi_Type == 1)
    {
        pi_Sprite = Sprite(TextureHolder::GetTexture("images/health_pickup.png"));

        //how much is pickup worth
        pi_Value = HEALT_VALUE;
    }
    else
    {
        pi_Sprite = Sprite(TextureHolder::GetTexture("images/ammo_pickup.png"));

        //how much is pickup worth
        pi_Value = AMMO_VALUE;
    }

    pi_Sprite.setOrigin(25, 25);

    pi_SecondsToLive = START_SECONDS_TO_LIVE;
    pi_SecondsToWait = START_WAIT_TIME;
}

void Pickup::setArena(IntRect arena)
{
    pi_Arena.left = arena.left + 100;
    pi_Arena.width = arena.width - 100;
    pi_Arena.top = arena.top + 100;
    pi_Arena.height = arena.height - 100;

    spawn();
}

void Pickup::spawn()
{
    //spawn at a random location
    srand((int)time(0) / pi_Type);
    //srand((int)time(0));
    int x = (rand() % pi_Arena.width + 50);
    srand((int)time(0) * pi_Type);
    int y = (rand() % pi_Arena.height + 50);

    pi_SecondsSinceSpawn = 0;
    pi_Spawned = true;

    //std::cout << x << " " << y << endl;

    pi_Sprite.setPosition(x, y);
}

FloatRect Pickup::getPosition()
{
    return pi_Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite()
{
    return pi_Sprite;
}

bool Pickup::isSpawned()
{
    return pi_Spawned;
}

int Pickup::gotIt()
{
    pi_Spawned = false;
    pi_SecondsSinceDeSpawn = 0;
    return pi_Value;
}

void Pickup::update(float elapsedTime)
{
    if (pi_Spawned)
    {
        pi_SecondsSinceSpawn += elapsedTime;
    }
    else
    {
        pi_SecondsSinceDeSpawn += elapsedTime;
    }

    //Do we need to hide a pickup?
    if (pi_SecondsSinceSpawn > pi_SecondsToLive && pi_Spawned)
    {
        //remove the pickup and put it somewhere else
        pi_Spawned = false;
        pi_SecondsSinceDeSpawn = 0;
    }

    //Do we need to spawn a pickup
    if (pi_SecondsSinceDeSpawn > pi_SecondsToWait && !pi_Spawned)
    {
        //spawn the pickup and reset the timer;
        spawn();
    }
}

void Pickup::upgrade()
{
    if (pi_Type == 1)
    {
        pi_Value += (HEALT_VALUE * 0.5);
    }
    else
    {
        pi_Value += (AMMO_VALUE * 0.5);
    }

    //make them more frequent and last longer
    pi_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
    pi_SecondsToWait -= (START_WAIT_TIME / 10);
}
