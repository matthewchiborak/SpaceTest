#include "Explosion.h"

Explosion::Explosion(sf::Image* passedImage, sf::Vector2f myPosition)
{
	//rockSpeed = 4;
	//rotationAngle = 5;
	//sprite.setTexture(*conTexture);
	sprite.setOrigin(32, 32);
	//power = 10;
	//value = 100;
	position = myPosition;
	explosionCounter = 0;
	fireSheet = passedImage;
	spriteSize = 64;
	numberOfSprites = 16;
}

sf::Sprite* Explosion::getSprite()
{
	return &sprite;
}
/*
sf::Vector2f Explosion::getDirection()
{
	return direction;
}

void Explosion::setDirection(float x, float y)
{
	direction.x = rockSpeed*x;
	direction.y = rockSpeed*y;
}

void Explosion::setPosition(sf::Vector2f passedPosition)
{
	sprite.setPosition(passedPosition);
}*/

/*
bool Explosion::isOffScreen(int screenHeight, int screenWidth)
{
	if (sprite.getPosition().x<0 || sprite.getPosition().x>screenWidth || sprite.getPosition().y<0 || sprite.getPosition().y>screenHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Explosion::move()
{
	sprite.move(direction);
	sprite.rotate(rotationAngle);
}

sf::FloatRect Explosion::getBoundBox()
{
	return sprite.getGlobalBounds();
}

int Explosion::getPower()
{
	return power;
}

int Explosion::getValue()
{
	return value;
}*/

void Explosion::advanceAnimation()
{
sf::IntRect spriteBox(((explosionCounter % 4))*spriteSize, ((explosionCounter % 4))*spriteSize, spriteSize, spriteSize);
fireTexture.loadFromImage(*fireSheet, spriteBox);
sprite.setTexture(fireTexture);
explosionCounter++;
}

bool Explosion::checkIfDone()
{
	return false;

	if (explosionCounter >= numberOfSprites)
	{
		return true;
	}
	else
	{
		return false;
	}
}