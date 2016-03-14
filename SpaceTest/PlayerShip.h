#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <SFML/Graphics.hpp>
#include <vector>
class PlayerShip
{
	private:
		int shipSpeed;
		sf::Vector2f direction;
		sf::Sprite sprite;
		int currentAngle;
		int rotationAngle;
		int maxHealth;
		int currentHealth;
		int maxShield;
		int currentShield;
		int shieldCost;

	public:
		PlayerShip(sf::Texture* conTexture);
		sf::Sprite* getSprite();
		sf::Vector2f getDirection();
		void setDirection(float x, float y);
		void setPosition(sf::Vector2f passedPosition);
		bool isOffScreen(int screenHeight, int screenWidth);
		void move(const double PI, int width, int height);
		sf::FloatRect getBoundBox();
		void rotateClockwise();
		void rotateCounterClockwise();
		int getCurrentAngle();
		bool dealDamage(int power); //Returns true if out of health
		int getMaxHealth();
		int getCurrentHealth();
		int getCurrentShield();
		int getMaxShield();
		bool attemptShield();
		void increaseShield(int value);
};
#endif