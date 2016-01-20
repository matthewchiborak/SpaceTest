#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>

class Explosion
{
private:
	//int rockSpeed;
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Image* fireSheet;
	//int rotationAngle;
	//int power;
	//int value;
	int explosionCounter;
	int spriteSize;
	sf::Texture fireTexture;
	int numberOfSprites;

public:
	Explosion(sf::Image* passedImage, sf::Vector2f myPosition);
	sf::Sprite* getSprite();
	//sf::Vector2f getDirection();
	//void setDirection(float x, float y);
	//void setPosition(sf::Vector2f passedPosition);
	//bool isOffScreen(int screenHeight, int screenWidth);
	//void move();
	//sf::FloatRect getBoundBox();
	//int getPower();
	//int getValue();
	void advanceAnimation();
	bool checkIfDone();
};
#endif