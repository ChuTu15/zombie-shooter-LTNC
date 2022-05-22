#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "header/player.h"
#include "header/createBgr.h"
#include "header/TextureHolder.h"
#include "header/bullet.h"
#include "header/pickup.h"
#include "header/sound.h"
#include "header/text.h"

using namespace sf;

int main()
{
    enum class State {
        START,
        PAUSE,
        PASS,
        LEVELING_UP,
        GAME_OVER,
        PLAYING
    };

    TextureHolder holder;

    //Start with the Game_Over state
    State state = State::START;

    //get the screen resolution and create a window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Shooter Arena", Style::Fullscreen);

    // create a an view for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    //create a an view for the menu update
    View menuView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    //clock for timing
    Clock clock;

    // How long has the PLAYING state been active
    Time gameTimeTotal;

    //Where is the mouse in relation to world coordinates
    Vector2f mouseWorld;
    //Where is the mouse in relation to screen coordinates
    Vector2i mouseScreen;

    //create an instance of the Player class
    Player player;

    //the boundaries of the arena
    IntRect arena;

    //create the background
    VertexArray background;

    //load the background texture
    Texture backgroundTexture = TextureHolder::GetTexture("images/background_sheet.png");

    //prepare for a horder of zombie;
    int numberZombie;
    int numberZombieAlive;
    zombie* zombies = nullptr;

    //bullet
    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1;
    // when fire
    Time lastPressed;

    // crosshair
    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::GetTexture("images/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    spriteCrosshair.setOrigin(25, 25);

    //create pickups
    Pickup healthPickup(1);
    Pickup ammoPickup(2);

    //wave
    int wave = 0;

    //score
    int score = 0;
    int high_score = 0;

    //load high score from a text file
    std::ifstream inFile("gamedata/score.txt");
    if (inFile.is_open())
    {
        inFile >> high_score;
        inFile.close();
    }

    //Background(screen of home/game over)
    Sprite spriteScreen;
    Texture textureScreen = TextureHolder::GetTexture("images/background.png");
    spriteScreen.setTexture(textureScreen);
    spriteScreen.setPosition(0, 0);

    //create a view for the HUD
    View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    //create a sprite for the ammo icon
    Sprite spriteAmmoIcon;
    Texture textureAmmoIcon = TextureHolder::GetTexture("images/ammo_icon.png");
    spriteAmmoIcon.setTexture(textureAmmoIcon);
    spriteAmmoIcon.setPosition(20, 980);

    text();

    //Health bar
    RectangleShape healthBar;
    healthBar.setFillColor(Color::Red);
    healthBar.setPosition(450, 980);

    //when did we last update the HUD?
    int framesScineLastHUDUpdate = 0;
    //what time was the last update
    Time timeSinceLastUpdate;
    //how often (in frames) should we update the HUD
    int fpsMeasurementFrameInterval = 10;

    sound();

    //the main game loop
    while (window.isOpen())
    {
        //Handle input

        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                //pause the game while playing
                if (event.key.code == Keyboard::P && state == State::PLAYING)
                {
                    state = State::PAUSE;
                }

                //restart while pause
                else if (event.key.code == Keyboard::P && state == State::PAUSE)
                {
                    state = State::PLAYING;
                    clock.restart();
                }

                //start a new game while in START or GAME_OVER state
                else if (event.key.code == Keyboard::Return && (state == State::GAME_OVER || state == State::START))
                {
                    state = State::LEVELING_UP;
                    wave = 0;
                    score = 0;

                    currentBullet = 0;
                    bulletsSpare =24;
                    bulletsInClip = 6;
                    clipSize = 6;
                    fireRate = 1;

                    player.resetPlayerStats();
                }

                else if (event.key.code == Keyboard::Return && state == State::PASS)
                {
                    state = State::LEVELING_UP;
                    clock.restart();
                }

                if (state == State::PLAYING)
                {
                    //reload bullet
                    if (event.key.code == Keyboard::R)
                    {
                        if (bulletsSpare >= clipSize)
                        {
                            //Plenty of bullets. Reload.
                            int temp = clipSize - bulletsInClip;
                            bulletsInClip += temp;
                            bulletsSpare -= temp;
                            reload.play();
                        }
                        else if (bulletsSpare < clipSize && bulletsInClip + bulletsSpare <= clipSize)
                        {
                            bulletsInClip += bulletsSpare;
                            bulletsSpare = 0;
                            reload.play();
                        }
                        else if (bulletsSpare == 0)
                        {
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                            reloadFailed.play();
                        }
                        else
                        {
                            reloadFailed.play();
                        }
                    }
                }
            }
        }//end event polling

        //handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        //where is the mouse pointer
        mouseScreen = Mouse::getPosition();



        //handle controlling the player
        if (state == State::PLAYING)
        {

            // Handle the pressing and releasing of the WASD keys
            if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }

            if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }

            if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }

            //fire the bullet
            if (Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0)
                {
                    //pass the center of the player
                    //and the center of the crosshair
                    //to the shoot function
                    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorld.x, mouseWorld.y);
                    currentBullet++;
                    if (currentBullet > 99)
                    {
                        currentBullet = 0;
                    }
                    lastPressed = gameTimeTotal;

                    shoot.play();

                    bulletsInClip--;
                }
            } //end fire bullet

        }// end if PLAYING

        // Handle the player leveling up
        if (state == State::LEVELING_UP)
        {
            //switch to the menu update view
            window.setView(menuView);

            //convert mouse position to world coordinates
            mouseWorld = window.mapPixelToCoords(Mouse::getPosition(), menuView);

            if (Mouse::isButtonPressed(sf::Mouse::Left) && mouseWorld.y < 160 && mouseWorld.y > 110)
            {
                //increase fire rate
                fireRate++;
                state = State::PLAYING;
            }

            if (Mouse::isButtonPressed(sf::Mouse::Left) && mouseWorld.y < 310 && mouseWorld.y > 260)
            {
                //increase clip size
                clipSize += clipSize;
                state = State::PLAYING;
            }

            if (Mouse::isButtonPressed(sf::Mouse::Left) && mouseWorld.y < 460 && mouseWorld.y > 410)
            {
                //increase health
                player.upgradeHealth();
                state = State::PLAYING;
            }

            if (Mouse::isButtonPressed(sf::Mouse::Left) && mouseWorld.y < 610 && mouseWorld.y > 560)
            {
                //increase speed
                player.upgradeSpeed();
                state = State::PLAYING;
            }

            if (Mouse::isButtonPressed(sf::Mouse::Left) && mouseWorld.y < 760 && mouseWorld.y > 710)
            {
                //upgrade health pickup
                healthPickup.upgrade();
                state = State::PLAYING;
            }

            if (Mouse::isButtonPressed(sf::Mouse::Left) && mouseWorld.y < 910 && mouseWorld.y > 860)
            {
                //upgrade ammo pickup
                ammoPickup.upgrade();
                state = State::PLAYING;
            }


            if (state == State::PLAYING)
            {

                //increase the wave number
                wave++;

                //prepare the level
                //we will modify the next two lines later
                arena.left = 0;
                arena.top = 0;
                arena.width = 500 * wave;
                arena.height = 500 * wave;

                //we will modify this line of code later
                int tileSize = createBackground(background, arena);

                //Spawn the player in the middle of the arena
                player.spawn(arena, resolution, tileSize);

                //configure the pickups
                healthPickup.setArena(arena);
                ammoPickup.setArena(arena);

                //create a horde of zombie
                numberZombie = 5 * wave;

                //Delete the previously allocated memory
                delete[] zombies;
                zombies = createHorde(numberZombie, arena);
                numberZombieAlive = numberZombie;

                powerup.play();

                //reset the game clock
                clock.restart();
            }

        }// end if LEVELING_UP


		//UPDATE THE FRAME

        if (state == State::PLAYING)
        {
            //update the delta time
            Time dt = clock.restart();
            //update the total time
            gameTimeTotal += dt;
            //make a decimal fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();

            //convert mouse position to world coordinates
            mouseWorld = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            //set position crosshair
            spriteCrosshair.setPosition(mouseWorld);

            //update the player
            player.update(dtAsSeconds, Mouse::getPosition());

            //make a note of the player's new position
            Vector2f playerPosition(player.getCenter());

            //make the view center around the player
            mainView.setCenter(player.getCenter());

            //loop through each zombie and update them
            for (int i = 0; i < numberZombie; i++)
            {
                if (zombies[i].isAlive())
                {
                    zombies[i].update(dt.asSeconds(), playerPosition);
                }
            }

            //update any bullets that are in-flight
            for (int i = 0; i < 100; i++)
            {
                if (bullets[i].isInFlight())
                {
                    bullets[i].update(dtAsSeconds);
                }
            }

            //update the pickups
            healthPickup.update(dtAsSeconds);
            ammoPickup.update(dtAsSeconds);

            //collision detection
            //have any zombie been shot?
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < numberZombie; j++)
                {
                    if (bullets[i].isInFlight() && zombies[j].isAlive())
                    {
                        if (bullets[i].getPosition().intersects(zombies[j].getPosition()))
                        {
                            //stop the bullet
                            bullets[i].stop();

                            //register the hit and see if it was a kill
                            if (zombies[j].hit())
                            {
                                //not just a hit but a kill too
                                score += 10;
                                if (score >= high_score)
                                {
                                    high_score = score;
                                }

                                numberZombieAlive--;

                                //when all zombies are dead
                                if (numberZombieAlive == 0)
                                {
                                    state = State::PASS;
                                }
                            }

                            splat.play();
                        }
                    }
                }
            }// end zombie being shot

            //have any zombies touched the player
            for (int i = 0; i < numberZombie; i++)
            {
                if (player.getPosition().intersects(zombies[i].getPosition()) && zombies[i].isAlive())
                {
                    if (player.hit(gameTimeTotal))
                    {
                        hit.play();
                    }

                    if (player.getHealth() <= 0)
                    {
                        state = State::GAME_OVER;
                        gameOver.play();
                    }

                    std::ofstream outFile("gamedata/score.txt");
                    outFile << high_score;
                    outFile.close();
                }
            } //end player touched

            //has the player touched health pickup
            if (player.getPosition().intersects(healthPickup.getPosition()) && healthPickup.isSpawned())
            {
                player.increaseHealth(healthPickup.gotIt());
                pickup.play();
            }

            //has the player touched ammo pickup
            if (player.getPosition().intersects(ammoPickup.getPosition()) && ammoPickup.isSpawned())
            {
                bulletsSpare += ammoPickup.gotIt();
                reload.play();
            }
            //end player touch pickups

            //size up the health bar
            healthBar.setSize(Vector2f(player.getHealth() * 3, 70));

            // Increment the amount of time since the last HUD update
            timeSinceLastUpdate += dt;
            // Increment the number of frames since the previous update
            framesScineLastHUDUpdate++;

            //re-calculate every fpsMeasurementFrameInterval frames
            if (framesScineLastHUDUpdate >= fpsMeasurementFrameInterval)
            {
                //update game HUD text
                std::stringstream ssAmmo;
                std::stringstream ssScore;
                std::stringstream ssHighScore;
                std::stringstream ssWave;
                std::stringstream ssZombiesAlive;

                //Update the ammo text
                ssAmmo << bulletsInClip << "/" << bulletsSpare;
                ammoText.setString(ssAmmo.str());

                //Update the score text
                ssScore << "Score: " << score;
                scoreText.setString(ssScore.str());

                //Update the high score text
                ssHighScore << "High Score: " << high_score;
                highScoreText.setString(ssHighScore.str());

                //Update the wave
                ssWave << "Wave: " << wave;
                waveNumberText.setString(ssWave.str());

                //Update the zombies is alive
                ssZombiesAlive << "Zombies: " << numberZombieAlive;
                zombiesRemainingText.setString(ssZombiesAlive.str());

                framesScineLastHUDUpdate = 0;
                timeSinceLastUpdate = Time::Zero;

            } //end HUD update

        } //end updating the scene

		//Draw the scene

        if (state == State::PLAYING)
        {
            //clear the window
            window.clear();

            // set the mainView to be displayed in the window
			// And draw everything related to it
            window.setView(mainView);

            //draw the background
            window.draw(background, &backgroundTexture);

            //draw the zombies
            for (int i = 0; i < numberZombie; i++)
            {
                window.draw(zombies[i].getSprite());
            }

            //draw bullets
            for (int i = 0; i < 100; i++)
            {
                if (bullets[i].isInFlight())
                {
                    window.draw(bullets[i].getShape());
                }
            }

            //draw the player
            window.draw(player.getSprite());

            //draw crosshair
            window.setMouseCursorVisible(false);
            window.draw(spriteCrosshair);

            //draw the pickups
            if (healthPickup.isSpawned())
            {
                window.draw(healthPickup.getSprite());
            }

            if (ammoPickup.isSpawned())
            {
                window.draw(ammoPickup.getSprite());
            }

            // Switch to the HUD view
            window.setView(hudView);

            //draw all the HUD elements
            window.draw(spriteAmmoIcon);
            window.draw(ammoText);
            window.draw(scoreText);
            window.draw(highScoreText);
            window.draw(healthBar);
            window.draw(waveNumberText);
            window.draw(zombiesRemainingText);

        }

        if (state == State::START)
        {
            window.draw(spriteScreen);
            window.draw(startText);
        }

        if (state == State::LEVELING_UP)
		{
		    window.setMouseCursorVisible(true);
		    window.draw(spriteScreen);
		    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
            {
		    window.draw(levelUpText[i]);
		    }
		}

		if (state == State::PAUSE)
		{
		    window.draw(pauseText);
		}

		if (state == State::PASS)
        {
            window.draw(spriteScreen);
            window.draw(passText);
            window.draw(scoreText);
            window.draw(highScoreText);
        }

		if (state == State::GAME_OVER)
		{
            window.draw(spriteCrosshair);
		    window.draw(spriteScreen);
		    window.draw(gameOverText);
		    window.draw(scoreText);
		    window.draw(highScoreText);
		}

        window.display();

    }// end game loop

    // Delete the previously allocated memory
    delete[] zombies;

    return 0;
}
