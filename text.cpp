#include "header/text.h"

Font font;
Text startText;
Text pauseText;
Text gameOverText;
Text levelUpText;
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
    pauseText.setString("Press Enter to continue");

    // game over
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(125);
    gameOverText.setFillColor(Color::White);
    gameOverText.setPosition(250, 800);
    gameOverText.setString("Game Over! \nPress Enter to retry");

    //Leveling up
    levelUpText.setFont(font);
    levelUpText.setCharacterSize(80);
    levelUpText.setFillColor(Color::White);
    levelUpText.setPosition(150, 250);
    std::stringstream levelUpstream;
    levelUpstream <<
        "Select update:"
        "\n1 - Increased rate of fire" <<
        "\n2 - Increased clip size(next reload)" <<
        "\n3 - Increased max health" <<
        "\n4 - Increased run speed" <<
        "\n5 - More and better health pickups" <<
        "\n6 - More and better ammo pickups";
    levelUpText.setString(levelUpstream.str());


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
    //std::stringstream s;
    //s << "High Score:" << high_score;
    //highScoreText.setString(s.str());

    //Zombie remaining
    zombiesRemainingText.setFont(font);
    zombiesRemainingText.setCharacterSize(55);
    zombiesRemainingText.setFillColor(Color::White);
    zombiesRemainingText.setPosition(1500, 980);
    //zombiesRemainingText.setString("Zombies: 100");

    //Wave number
    waveNumberText.setFont(font);
    waveNumberText.setCharacterSize(55);
    waveNumberText.setFillColor(Color::White);
    waveNumberText.setPosition(1250, 980);
}
