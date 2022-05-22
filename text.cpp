#include "header/text.h"

using namespace sf;

Font font;
Text startText;
Text pauseText;
Text gameOverText;
Text levelUpText[MAX_NUMBER_OF_ITEMS];
Text passText;
Text ammoText;
Text scoreText;
Text highScoreText;
Text zombiesRemainingText;
Text waveNumberText;

void text()
{
    //load font
    font.loadFromFile("fonts/zombiecontrol.ttf");

    //start
    startText.setFont(font);
    startText.setCharacterSize(125);
    startText.setFillColor(Color::White);
    startText.setPosition(250,850);
    startText.setString("Press Enter to play");

    //pause
    pauseText.setFont(font);
    pauseText.setCharacterSize(100);
    pauseText.setFillColor(Color::White);
    pauseText.setPosition(400, 400);
    pauseText.setString("Press P to continue");

    // game over
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(Color::White);
    gameOverText.setPosition(250, 800);
    gameOverText.setString("Game Over! \nPress Enter to retry");

    //Leveling up
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        levelUpText[i].setFont(font);
        levelUpText[i].setCharacterSize(50);
        levelUpText[i].setFillColor(Color::White);
        levelUpText[i].setStyle(Text::Underlined);
        levelUpText[i].setOutlineThickness(2.f);
        levelUpText[i].setPosition(150, 50 * (i + 1) + 100 * i);
    }
    levelUpText[0].setString("\n1 - Increased rate of fire");
    levelUpText[1].setString("\n2 - Increased clip size(next reload)");
    levelUpText[2].setString("\n3 - Increased max health");
    levelUpText[3].setString("\n4 - Increased run speed");
    levelUpText[4].setString("\n5 - More and better health pickups");
    levelUpText[5].setString("\n6 - More and better ammo pickups");

    //pass wave
    passText.setFont(font);
    passText.setCharacterSize(100);
    passText.setFillColor(Color::White);
    passText.setPosition(250, 800);
    passText.setString("Congratulation! \nPress Enter to continue");


    //Ammo
    ammoText.setFont(font);
    ammoText.setCharacterSize(55);
    ammoText.setFillColor(Color::White);
    ammoText.setPosition(200, 980);

    //Score
    scoreText.setFont(font);
    scoreText.setCharacterSize(55);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 0);

    //high score
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(55);
    highScoreText.setFillColor(Color::White);
    highScoreText.setPosition(1400, 0);

    //Zombie remaining
    zombiesRemainingText.setFont(font);
    zombiesRemainingText.setCharacterSize(55);
    zombiesRemainingText.setFillColor(Color::White);
    zombiesRemainingText.setPosition(1500, 980);

    //Wave number
    waveNumberText.setFont(font);
    waveNumberText.setCharacterSize(55);
    waveNumberText.setFillColor(Color::White);
    waveNumberText.setPosition(1250, 980);
}

