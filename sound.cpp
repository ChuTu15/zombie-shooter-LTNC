#include "header/sound.h"


SoundBuffer hitBuffer;
Sound hit;

SoundBuffer splatBuffer;
Sound splat;

SoundBuffer shootBuffer;
Sound shoot;

SoundBuffer reloadBuffer;
Sound reload;

SoundBuffer reloadFailedBuffer;
Sound reloadFailed;

SoundBuffer powerupBuffer;
Sound powerup;

SoundBuffer pickupBuffer;
Sound pickup;

SoundBuffer gameOverBuffer;
Sound gameOver;
void sound()
{
    //hit sound
    hitBuffer.loadFromFile("sound/hit.wav");
    hit.setBuffer(hitBuffer);

    //splat sound
    splatBuffer.loadFromFile("sound/splat.wav");
    splat.setBuffer(splatBuffer);

    //shoot sound
    shootBuffer.loadFromFile("sound/shoot.wav");
    shoot.setBuffer(shootBuffer);

    //reload sound
    reloadBuffer.loadFromFile("sound/reload.wav");
    reload.setBuffer(reloadBuffer);

    //reload failed sound
    reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
    reloadFailed.setBuffer(reloadFailedBuffer);

    //power up sound
    powerupBuffer.loadFromFile("sound/powerup.wav");
    powerup.setBuffer(powerupBuffer);

    //pickup sound
    pickupBuffer.loadFromFile("sound/pickup.wav");
    pickup.setBuffer(pickupBuffer);

    //gameover sound
    gameOverBuffer.loadFromFile("sound/gameover.wav");
    gameOver.setBuffer(gameOverBuffer);

}

