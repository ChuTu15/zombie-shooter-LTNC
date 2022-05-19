#include "header/player.h"
#include "header/TextureHolder.h"

Player::Player()
{
    p_Speed = START_SPEED;
    p_Health = START_HEALTH;
    p_MaxHealth = START_HEALTH;

    //Associate the player with the texture
    p_Sprite = Sprite(TextureHolder::GetTexture("images/player.png"));

    //set the origin to the center of the player
    p_Sprite.setOrigin(25, 25);
}

void Player::resetPlayerStats()
{
    p_Speed = START_SPEED;
    p_Health = START_HEALTH;
    p_MaxHealth = START_HEALTH;
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
    //place the player in the middle of the arena
    p_position.x = arena.width / 2.0f;
    p_position.y = arena.height / 2.0f;

    //set the arena
    p_Arena.left = arena.left;
    p_Arena.width = arena.width;
    p_Arena.top = arena.top;
    p_Arena.height = arena.height;

    //remember how big the tiles are in this arena
    p_TileSize = tileSize;

    //set the screen resolution
    p_Resolution.x = resolution.x;
    p_Resolution.y = resolution.y;
}

Time Player::getLastHitTime()
{
    return p_LastHit;
}

bool Player::hit(Time timeHit)
{
    if (timeHit.asMilliseconds() - p_LastHit.asMilliseconds() <= 200)
    {
        return false;
    }
    else
    {
        p_LastHit = timeHit;
        p_Health -= 10;
        return true;
    }
}

FloatRect Player::getPosition()
{
    return p_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
    return p_position;
}

float Player::getRotation()
{
    return p_Sprite.getRotation();
}

Sprite Player::getSprite()
{
    return p_Sprite;
}

int Player::getHealth()
{
    return p_Health;
}

void Player::moveLeft()
{
    p_FacingLeft = true;
}

void Player::moveRight()
{
    p_FacingRight = true;
}

void Player::moveUp()
{
    p_FacingUp = true;
}

void Player::moveDown()
{
    p_FacingDown = true;
}

void Player::stopDown()
{
    p_FacingDown = false;
}

void Player::stopUp()
{
    p_FacingUp = false;
}

void Player::stopLeft()
{
    p_FacingLeft = false;
}

void Player::stopRight()
{
    p_FacingRight = false;
}

void Player::update(float elapsedTime, Vector2i mousePos)
{
    if (p_FacingLeft)
    {
        p_position.x -= p_Speed * elapsedTime;
    }

    if (p_FacingRight)
    {
        p_position.x += p_Speed * elapsedTime;
    }

    if (p_FacingUp)
    {
        p_position.y -= p_Speed * elapsedTime;
    }

    if (p_FacingDown)
    {
        p_position.y += p_Speed * elapsedTime;
    }

    p_Sprite.setPosition(p_position);

    //keep the player on the arena
    if (p_position.x < p_Arena.left + p_TileSize)
    {
        p_position.x = p_Arena.left + p_TileSize;
    }

    if (p_position.x > p_Arena.width - p_TileSize)
    {
        p_position.x = p_Arena.width - p_TileSize;
    }

    if (p_position.y < p_Arena.top + p_TileSize)
    {
        p_position.y = p_Arena.top + p_TileSize;
    }

    if (p_position.y > p_Arena.height - p_TileSize)
    {
        p_position.y = p_Arena.height - p_TileSize;
    }

    // calculate the angle to the mouse
    float angle = (atan2(mousePos.y - p_Resolution.y / 2, mousePos.x - p_Resolution.x / 2) * 180) / 3.14159265;

    p_Sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
    //20% increase in speed
    p_Speed += (p_Speed * 0.2);
}

void Player::upgradeHealth()
{
    //20% increase in health
    p_MaxHealth += (p_MaxHealth * 0.2);
}

void Player::increaseHealth(int amount)
{
    p_Health += amount;

    //but not more than the max health
    if (p_Health > p_MaxHealth)
    {
        p_Health = p_MaxHealth;
    }
}
