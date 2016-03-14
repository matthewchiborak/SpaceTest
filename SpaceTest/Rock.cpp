#include "Rock.h"

Rock::Rock(sf::Texture* conTexture)
{
	rockSpeed = 4;
	rotationAngle = 5;
	sprite.setTexture(*conTexture);
	sprite.setOrigin(32, 32);
	power = 10;
	value = 100;
}

sf::Sprite* Rock::getSprite()
{
	return &sprite;
}

sf::Vector2f Rock::getDirection()
{
	return direction;
}

void Rock::setDirection(float x, float y)
{
	direction.x = rockSpeed*x;
	direction.y = rockSpeed*y;
}

void Rock::setPosition(sf::Vector2f passedPosition)
{
	sprite.setPosition(passedPosition);
}

bool Rock::isOffScreen(int screenHeight, int screenWidth)
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

void Rock::move()
{
	sprite.move(direction);
	sprite.rotate(rotationAngle);
}

sf::FloatRect Rock::getBoundBox()
{
	return sprite.getGlobalBounds();
}

int Rock::getPower()
{
	return power;
}

int Rock::getValue()
{
	return value;
}

