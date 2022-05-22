#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "SFML/Audio.hpp"
#include <iostream>

using namespace sf;

extern SoundBuffer hitBuffer;
extern Sound hit;


extern SoundBuffer splatBuffer;
extern Sound splat;

extern SoundBuffer shootBuffer;
extern Sound shoot;

extern SoundBuffer reloadBuffer;
extern Sound reload;

extern SoundBuffer reloadFailedBuffer;
extern Sound reloadFailed;

extern SoundBuffer powerupBuffer;
extern Sound powerup;

extern SoundBuffer pickupBuffer;
extern Sound pickup;

extern SoundBuffer gameOverBuffer;
extern Sound gameOver;

void sound();

#endif // SOUND_H_INCLUDED
