#pragma once

#include "batch.hpp"

class PlayerCharacter
{
public:
	PlayerCharacter();
	~PlayerCharacter();
	void SetUp(sf::Texture* texture, float min, float max);
	void PlayerUpdate(float deltatime);
	void ProcessingInput(float deltatime);
	void WorldConstrainingOnPositionX();
	void Restart();
	sf::Sprite m_playerSprite;
	bool pressedLeft;
	bool pressedRight;
private:
	const float defualtMovmentSpeed;
	const float positionY;
	float positionX;
	float minPositionX, maxPositionX;
};