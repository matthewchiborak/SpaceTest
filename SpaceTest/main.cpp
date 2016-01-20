#include <SFML/Graphics.hpp>
#include "math.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <ctime>
#include "PlayerShip.h"
#include "Rock.h"
#include "Bullet.h"
#include "FileManager.h"
#include "Explosion.h"



int main()
{
	//Load high scores
	std::string fileName = "highscores.txt";
	FileManager scoreManager;
	scoreManager.readScoreFile(fileName);

	const double PI = 3.14159265;
	std::srand(std::time(0));

	float shotInterval = 200;
	int spawnInterval = 300;
	bool shieldActive = false;
	int windowHeight = 683;
	int windowWidth = 1024;

	int score = 0;

	const int maxBulletsOnScreen = 10;

	Bullet* bulletHolder[maxBulletsOnScreen];
	for (int i = 0; i < maxBulletsOnScreen; i++)
	{
		bulletHolder[i] = nullptr;
	}

	sf::RenderWindow window(sf::VideoMode(1024, 683), "SpaceLand");
	window.setVerticalSyncEnabled(true);

	int healthBarHeight = 30;
	sf::RectangleShape healthBarBack(sf::Vector2f(200, healthBarHeight));
	healthBarBack.setFillColor(sf::Color::Red);
	sf::RectangleShape healthBarFront(sf::Vector2f(200, healthBarHeight));
	healthBarFront.setFillColor(sf::Color::Green);

	sf::RectangleShape shieldBarBack(sf::Vector2f(200, healthBarHeight));
	shieldBarBack.setFillColor(sf::Color::Red);
	shieldBarBack.setPosition(windowWidth-200, 0);
	sf::RectangleShape shieldBarFront(sf::Vector2f(200, healthBarHeight));
	shieldBarFront.setFillColor(sf::Color::Blue);
	shieldBarFront.setPosition(windowWidth-200, 0);

	sf::CircleShape shieldShape(32);
	shieldShape.setFillColor(sf::Color(150, 50, 250, 0));
	shieldShape.setOrigin(32, 32);
	shieldShape.setOutlineThickness(4);
	shieldShape.setOutlineColor(sf::Color::Blue);

	sf::Font font;
	if (!font.loadFromFile("Mr Sunshine.ttf"))
	{
		std::cout << "Font loading error\n";
	}

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Test");
	scoreText.setCharacterSize(24);
	scoreText.setColor(sf::Color::White);
	//scoreText.setPosition(windowWidth / 2, 0);

	/*sf::Image fireImageSheet;
	if (!fireImageSheet.loadFromFile("Fire.png"))
	{
		std::cout << "Failed to load fire\n";
	}

	const int maxNumberOfFire = 20;
	Explosion* fireHolder[maxNumberOfFire];

	for (int i = 0; i < maxNumberOfFire; i++)
	{
		fireHolder[i] = nullptr;
	}*/

	sf::Texture rockTexture;
	rockTexture.loadFromFile("Rock.png");

	const int maxRocksOnScreen = 15;
	
	Rock* rockHolder[maxRocksOnScreen];

	for (int i = 0; i < maxRocksOnScreen; i++)
	{
		rockHolder[i] = nullptr;
	}
	
	
	auto lastRockSpawned = std::chrono::high_resolution_clock::now();
	

	sf::Texture playerShipTexture;
	playerShipTexture.loadFromFile("PlayerShip.png");
	PlayerShip player(&playerShipTexture);

	bool shotCooldown = false;
	auto start = std::chrono::high_resolution_clock::now();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.rotateClockwise();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.rotateCounterClockwise();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player.move(PI, windowWidth, windowHeight);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			if (player.attemptShield())
			{
				shieldShape.setPosition(player.getSprite()->getPosition());
				//window.draw(shieldShape);
				shieldActive = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			rockTexture.loadFromFile("Rock.png");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			rockTexture.loadFromFile("Cage.png");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!shotCooldown)
			{
				for (int i = 0; i < maxBulletsOnScreen; i++)
				{
					if (bulletHolder[i]==nullptr)
					{
						bulletHolder[i] = new Bullet();
						bulletHolder[i]->setPosition(player.getSprite()->getPosition());
						bulletHolder[i]->setDirection(sin(player.getCurrentAngle()*PI / 180), -1 * cos(player.getCurrentAngle()*PI / 180));
						shotCooldown = true;
						start = std::chrono::high_resolution_clock::now();
						break;
					}
				}
			}
		}

		//Spawn rock if need 
		auto rockTimeNow = std::chrono::high_resolution_clock::now();
		if (((std::chrono::duration_cast<std::chrono::milliseconds>(rockTimeNow - lastRockSpawned).count())>shotInterval))
		{
			for (int i = 0; i < maxRocksOnScreen; i++)
			{
				if (rockHolder[i]==nullptr)
				{
					rockHolder[i] = new Rock(&rockTexture);
					int cornerNumber = rand() % 4;
					int rockAngle = rand() % 90;
				
					if (cornerNumber == 0)
					{
						rockHolder[i]->getSprite()->setPosition(0, 0);
						rockAngle += 90;
					}
					else if (cornerNumber == 1)
					{
						rockHolder[i]->getSprite()->setPosition(windowWidth - 64, 0);
						rockAngle += 180;
					}
					else if (cornerNumber == 2)
					{
						rockHolder[i]->getSprite()->setPosition(windowWidth - 64, windowHeight - 64);
						rockAngle += 270;
					}
					else
					{
						rockHolder[i]->getSprite()->setPosition(0, windowHeight - 64);
					}
					
					rockHolder[i]->setDirection(sin(rockAngle*PI / 180), -1 * cos(rockAngle*PI / 180));
					
					lastRockSpawned = std::chrono::high_resolution_clock::now();
					break;
				}
			}
		}

		


		window.clear();



		for (int i = 0; i < maxBulletsOnScreen; i++)
		{
			if (bulletHolder[i]!=nullptr)
			{
				if (bulletHolder[i]->isOffScreen(windowHeight, windowWidth))
				{
					delete bulletHolder[i];
					bulletHolder[i] = nullptr;
				}
				else
				{
					bulletHolder[i]->move();
					window.draw(*bulletHolder[i]->getSprite());
				}
			}
		}

		sf::FloatRect shipBox = player.getBoundBox();

		for (int i = 0; i < maxRocksOnScreen; i++)
		{
			if (rockHolder[i]!=nullptr)
			{
				if (rockHolder[i]->isOffScreen(windowHeight, windowWidth))
				{
					delete rockHolder[i];
					rockHolder[i] = nullptr;
					//rockHolder[i]->destroy();
				}
				else
				{
					rockHolder[i]->move();
					window.draw(*(rockHolder[i]->getSprite()));
				}

				//Check if rock is hitting the ship
				
				if (rockHolder[i] != nullptr)
				{
					sf::FloatRect rockBox = rockHolder[i]->getBoundBox();

					if (rockBox.intersects(shipBox))
					{
						if (!shieldActive)
						{
							player.dealDamage(rockHolder[i]->getPower());
						}

						/*for (int k = 0; k < maxNumberOfFire; k++)
						{
							if (fireHolder[k] == nullptr)
							{
								fireHolder[k] = new Explosion(&fireImageSheet, rockHolder[i]->getDirection());
								break;
							}
						}*/

						delete rockHolder[i];
						rockHolder[i] = nullptr;
						//rockHolder[i]->destroy();
						
					}
				}


				//Check if bullet is hitting a rock
				for (int j = 0; j < maxBulletsOnScreen; j++)
				{
					if (bulletHolder[j]!=nullptr)
					{
						if (rockHolder[i]!=nullptr)
						{
							sf::FloatRect rockBox = rockHolder[i]->getBoundBox();
							sf::FloatRect bulletBox = bulletHolder[j]->getBoundBox();
							if (rockBox.intersects(bulletBox))
							{
								score += rockHolder[i]->getValue();
								player.increaseShield(2);

								/*for (int k = 0; k < maxNumberOfFire; k++)
								{
									if (fireHolder[k] == nullptr)
									{
										fireHolder[k] = new Explosion(&fireImageSheet, rockHolder[i]->getDirection());
										break;
									}
								}*/
								
								delete rockHolder[i];
								rockHolder[i] = nullptr;
								//rockHolder[i]->destroy();
								delete bulletHolder[j];
								bulletHolder[j] = nullptr;
							}
						}
					}
				}
			}
		}

		

		auto end = std::chrono::high_resolution_clock::now();
		
		if (shotCooldown&&((std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count())>shotInterval))
		{
			shotCooldown = false;
		}

		window.draw(*player.getSprite());

		
		if (shieldActive)
		{
			//shieldShape.setPosition(player.getSprite()->getPosition());
			shieldActive = false;
			window.draw(shieldShape);
		}

		//Draw the explosions
		/*for (int i = 0; i < maxNumberOfFire; i++)
		{
			if (fireHolder[i] != nullptr)
			{
				fireHolder[i]->advanceAnimation();

				if (fireHolder[i]->checkIfDone())
				{
					delete fireHolder[i];
					fireHolder[i] = nullptr;
				}
				else
				{
					window.draw(*fireHolder[i]->getSprite());
				}
			}
		}*/
		

		//Draw the health bar
		healthBarFront.setSize(sf::Vector2f(2*player.getCurrentHealth(), healthBarHeight));
		window.draw(healthBarBack);
		window.draw(healthBarFront);
		shieldBarFront.setSize(sf::Vector2f(2 * player.getCurrentShield(), healthBarHeight));
		window.draw(shieldBarBack);
		window.draw(shieldBarFront);
		scoreText.setString("Score: " + std::to_string(score));
		window.draw(scoreText);



		window.display();

		if (player.getCurrentHealth() <= 0)
		{
			window.close();

			sf::RenderWindow scoreBoard(sf::VideoMode(500, 700), "High Scores");
			scoreBoard.setVerticalSyncEnabled(true);

			sf::Text scoreBoardText;
			scoreBoardText.setFont(font);
			scoreBoardText.setString("Testing");
			scoreBoardText.setCharacterSize(50);
			scoreBoardText.setColor(sf::Color::White);

			std::string name = "";

			std::string* playerNames = scoreManager.getPlayers();
			std::string* scoreValues = scoreManager.getScores();
			//int* numOfEntries = scoreManager.getNumberOfEntries();
			int newPlacing = 10;
			std::string prior = "";
			std::string after = "";
			bool placeFound = false;

			/*if (*numOfEntries < 9)
			{
				(*numOfEntries)++;
			}*/

			std::string tempPlayer = "";
			std::string tempScore = "";

			for (int i = 0; i < 10; i++)
			{
				if (!placeFound)
				{
					if (score > atoi(scoreValues[i].c_str()))
					{
						newPlacing = i;
						placeFound = true;
						//tempPlayer = playerNames[i+1];
						//tempScore = scoreValues[i+1];
						//i--;
						for (int j = 9; j > newPlacing; j--)
						{
							playerNames[j] = playerNames[j-1];
							scoreValues[j] = scoreValues[j-1];
						}
					}
					else
					{
						prior = prior + playerNames[i] + "   " + scoreValues[i]+"\n";
					}
				}
				else
				{
					
						//playerNames[i + 1] = playerNames[i];
						//scoreValues[i + 1] = scoreValues[i];
						after = after + playerNames[i] + "   " + scoreValues[i]+"\n";
					
				}
			}

			int lettersEntered = 0;
			std::string previousName[4];
			for (int k = 0; k < 4; k++)
			{
				previousName[k] = "";
			}

			while (scoreBoard.isOpen())
			{
				sf::Event scoreEvent;
				while (scoreBoard.pollEvent(scoreEvent))
				{
					if (scoreEvent.type == sf::Event::Closed)
					{
						if (lettersEntered==3||!placeFound)
						{
							if (placeFound)
							{
								playerNames[newPlacing] = name;
								scoreValues[newPlacing] = std::to_string(score);
							}
							scoreManager.save(fileName);
							scoreBoard.close();
						}
					}
					if (scoreEvent.type == sf::Event::TextEntered)
					{
						if (placeFound)
						{
							if (lettersEntered<3||(scoreEvent.text.unicode==8))
							{
								if ((scoreEvent.text.unicode == 8))
								{
									if (lettersEntered != 0)
									{
										lettersEntered--;
										name = previousName[lettersEntered];
									}
									
								}
								else if (scoreEvent.text.unicode < 128)
								{
									//std::cout << scoreEvent.text.unicode << "\n";
									name += static_cast<char>(scoreEvent.text.unicode);
									lettersEntered++;
									previousName[lettersEntered] = name;
								}
							}
						}
					}
				}

				scoreBoard.clear();
				std::string result = prior + name + "   " + std::to_string(score) + "\n" + after;
				if (!placeFound)
				{
					result = prior;
				}
				scoreBoardText.setString(result);
				scoreBoard.draw(scoreBoardText);
				scoreBoard.display();
			}
		}
	}

	for (int i = 0; i < maxRocksOnScreen; i++)
	{
		if (rockHolder[i] != nullptr)
		{
			delete rockHolder[i];
		}
	}
	/*for (int i = 0; i < maxNumberOfFire; i++)
	{
		if (fireHolder[i] != nullptr)
		{
			delete fireHolder[i];
		}
	}*/
	for (int i = 0; i < maxBulletsOnScreen; i++)
	{
		if (bulletHolder[i] != nullptr)
		{
			delete bulletHolder[i];
		}
	}

	return 0;
}