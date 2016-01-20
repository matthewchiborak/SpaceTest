#include "PlayerShip.h"

PlayerShip::PlayerShip(sf::Texture* conTexture)
{
	shipSpeed = 5;
	currentAngle = 0;
	sprite.setTexture(*conTexture);
	sprite.setOrigin(32, 32);
	sprite.setPosition(512, 500);
	rotationAngle = 10;
	currentHealth = 100;
	maxHealth = 100;
	maxShield = 100;
	currentShield = 100;
	shieldCost = 1;
}

sf::Sprite* PlayerShip::getSprite()
{
	return &sprite;
}

sf::Vector2f PlayerShip::getDirection()
{
	return direction;
}

void PlayerShip::setDirection(float x, float y)
{
	direction.x = shipSpeed*x;
	direction.y = shipSpeed*y;
}

void PlayerShip::setPosition(sf::Vector2f passedPosition)
{
	sprite.setPosition(passedPosition);
}

bool PlayerShip::isOffScreen(int screenHeight, int screenWidth)
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

void PlayerShip::move(const double PI, int width, int height)
{
	//sprite.move(direction);
	//sprite.rotate(rotationAngle);
	//int x = shipSpeed * sin(currentAngle*PI / 180);
	//int y = shipSpeed * cos(currentAngle*PI / 180);
	sprite.move(shipSpeed * sin(currentAngle*PI / 180), -1* shipSpeed * cos(currentAngle*PI / 180));

	int x = sprite.getPosition().x;
	int y = sprite.getPosition().y;

	if (sprite.getPosition().x < 0)
	{
		x = width;
	}
	if (sprite.getPosition().x > width)
	{
		x = 0;
	}
	if (sprite.getPosition().y < 0)
	{
		y = height;
	}
	if (sprite.getPosition().y > height)
	{
		y = 0;
	}

	sprite.setPosition(x, y);
}

sf::FloatRect PlayerShip::getBoundBox()
{
	return sprite.getGlobalBounds();
}

/*void PlayerShip::setCurrentAngle(int angle)
{
	currentAngle = angle;
}*/

int PlayerShip::getCurrentAngle()
{
	return currentAngle;
}

void PlayerShip::rotateClockwise()
{
	sprite.rotate(rotationAngle);
	currentAngle += rotationAngle;
	currentAngle = currentAngle % 360;
}
void PlayerShip::rotateCounterClockwise()
{
	sprite.rotate(-1*rotationAngle);
	currentAngle -= rotationAngle;
	if (currentAngle < 0)
	{
		currentAngle += 360;
	}
}

bool PlayerShip::dealDamage(int power)
{
	currentHealth -= power;

	if (currentHealth <= 0)
	{
		currentHealth = 0;
		return true;
	}
	else
	{
		return false;
	}
}

int PlayerShip::getMaxHealth()
{
	return maxHealth;
}

int PlayerShip::getCurrentHealth()
{
	return currentHealth;
}

int PlayerShip::getCurrentShield()
{
	return currentShield;
}
int PlayerShip::getMaxShield()
{
	return maxShield;
}

bool PlayerShip::attemptShield()
{
	//CHeck shield health
	currentShield -= shieldCost;
	if (currentShield <= 0)
	{
		currentShield = 0;
		return false;
	}

	return true;
}

void PlayerShip::increaseShield(int value)
{
	currentShield += value;
	if (currentShield > maxShield)
	{
		currentShield = maxShield;
	}
}