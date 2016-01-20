#ifndef ROCK_H
#define ROCK_H

#include <SFML/Graphics.hpp>
#include <vector>
class Rock
{
private:
	int rockSpeed;
	sf::Vector2f direction;
	sf::Sprite sprite;
	//sf::Image* fireSheet;
	int rotationAngle;
	int power;
	int value;
	//int explosionCounter;
	//int spriteSize;
	//sf::Texture fireTexture;

public:
	Rock(sf::Texture* conTexture);
	sf::Sprite* getSprite();
	sf::Vector2f getDirection();
	void setDirection(float x, float y);
	void setPosition(sf::Vector2f passedPosition);
	bool isOffScreen(int screenHeight, int screenWidth);
	void move();
	sf::FloatRect getBoundBox();
	int getPower();
	int getValue();
	//void destroy();
	//int getExplosionCounter();
};
#endif
