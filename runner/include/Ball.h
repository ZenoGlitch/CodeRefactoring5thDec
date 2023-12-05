#pragma once
#include "batch.hpp"

//enum class BallMovementDirection
//{
//	//I made this to keep check the ball changing direction.
//	UP, Down, Left, Right
//};

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEGHT = 720;

class Ball 
{
public:
	Ball();

	void SetUp(const sf::Texture &texture);
	void Update(float deltatime);
	const float Length(const sf::Vector2f& rhs) noexcept;
	void WorldConstraining(float posX, float posY) noexcept;
	void Restart() noexcept;
	sf::Vector2f Normalized(const sf::Vector2f& rhs);
	sf::Sprite m_ballSprite;
	
	
	const sf::IntRect worldBounds = { 0, 0, SCREEN_WIDTH , SCREEN_HEGHT};
	
	bool hasCollided = false;
	float m_speed{ 200.0f };
	float positionX{ 500.0f };
	float positionY{ 400.0f };
	sf::Vector2f m_direction{positionX, positionY};

private:
};