#include "header/zombie.h"
#include "header/TextureHolder.h";
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

void zombie::spawn(float startX, float startY, int type, int seed)
{
    switch (type)
    {
    case 0:
        //Bloater
        z_Sprite = Sprite(TextureHolder::GetTexture("images/bloater.png"));
        z_Speed = BLOATER_SPEED;
        z_Health = BLOATER_HEALTH;
        break;

    case 1:
        //Chaser
        z_Sprite = Sprite(TextureHolder::GetTexture("images/chaser.png"));
        z_Speed = CHASER_SPEED;
        z_Health = CHASER_HEALTH;
        break;
    case 2:
        //Crawler
        z_Sprite = Sprite(TextureHolder::GetTexture("images/crawler.png"));
        z_Speed = CRAWLER_SPEED;
        z_Health = CRAWLER_HEALTH;
        break;
    }

    // Modify the speed to make the zombie unique
    // Every zombie is unique. Create a speed modifier
    srand((int)time(0) * seed);

    // Somewhere between 80 and 100
    float modifier = (rand() % MAX_VARRIANCE) + OFFSET;

    // Express this as a fraction of 1
    modifier /= 100; // Now equals between .7 and 1
    z_Speed *= modifier;

    z_Position.x = startX;
    z_Position.y = startY;


    z_Sprite.setOrigin(25,25);
    z_Sprite.setPosition(z_Position);
}

bool zombie::hit()
{
    z_Health--;

    if (z_Health <= 0)
    {
        //dead
        z_Alive = false;
        z_Sprite.setTexture(TextureHolder::GetTexture("images/blood.png"));
        return true;
    }

    return false;
}

bool zombie::isAlive()
{
    return z_Alive;
}

FloatRect zombie::getPosition()
{
    return z_Sprite.getGlobalBounds();
}

Sprite zombie::getSprite()
{
    return z_Sprite;
}

void zombie::update(float elapsedTime, Vector2f playerLocation)
{

    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    //update the zombie position variable
    if (playerX > z_Position.x)
    {
        z_Position.x = z_Position.x + z_Speed * elapsedTime;
    }

    if (playerY > z_Position.y)
	{
		z_Position.y = z_Position.y + z_Speed * elapsedTime;
	}

	if (playerX < z_Position.x)
	{
		z_Position.x = z_Position.x - z_Speed * elapsedTime;
	}

	if (playerY < z_Position.y)
	{
		z_Position.y = z_Position.y - z_Speed * elapsedTime;
	}

	//move the sprite
	z_Sprite.setPosition(z_Position);

	//face the sprite in the correct direction
	float angle = (atan2(playerY - z_Position.y, playerX - z_Position.x) * 180) / 3.14159265;

	z_Sprite.setRotation(angle);
}
