#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "SFML/Graphics.hpp"
#include <sstream>
#include <iostream>

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
extern Text levelUpText;

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
