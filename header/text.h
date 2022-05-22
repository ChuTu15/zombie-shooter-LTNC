#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#pragma once

#include "SFML/Graphics.hpp"
#include <sstream>
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 6

using namespace sf;

//load font
extern Font font;

//start
extern Text startText;

//pause
extern Text pauseText;

// game over
extern Text gameOverText;

//Leveling up
extern Text levelUpText[MAX_NUMBER_OF_ITEMS];

//pass wave
extern Text passText;

//Ammo
extern Text ammoText;

//Score
extern Text scoreText;

//high score
extern Text highScoreText;

//Zombie remaining
extern Text zombiesRemainingText;

//Wave number
extern Text waveNumberText;

void text();

#endif // TEXT_H_INCLUDED
