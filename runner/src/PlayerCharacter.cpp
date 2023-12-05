#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
	: defualtMovmentSpeed(700.0f), positionY(650.0f)
{
	positionX = 0.0f;
	minPositionX = 0;
	maxPositionX = 0;
	pressedLeft = false;
	pressedRight = false;
};

PlayerCharacter::~PlayerCharacter()
{

};

void PlayerCharacter::SetUp(sf::Texture* texture, float min, float max)
{
	//Thinking is easier to read if I set variables in a SetUp class
	minPositionX = min;
	maxPositionX = max;
	positionX = 500.0f;
	m_playerSprite.setTexture(*texture);
	m_playerSprite.setPosition(positionX, positionY);
	m_playerSprite.setScale(1.0f, 0.5f);
};

void PlayerCharacter::PlayerUpdate(float deltatime)
{
	ProcessingInput(deltatime);
	m_playerSprite.setPosition(positionX, positionY);
	WorldConstrainingOnPositionX();
};

void PlayerCharacter::ProcessingInput(float deltatime)
{
	if(pressedLeft)
	{
		positionX += -defualtMovmentSpeed * deltatime;
	}
	if(pressedRight)
	{
		positionX += defualtMovmentSpeed * deltatime;
	}
};

void PlayerCharacter::WorldConstrainingOnPositionX() 
{
	if(positionX < minPositionX)
	{
		positionX = 0.0f;
	}
	if(positionX >= maxPositionX - 150.0f)
	{
		positionX = maxPositionX - 150.0f;
	}
};

void PlayerCharacter::Restart()
{
	positionX = 500.0f;
}