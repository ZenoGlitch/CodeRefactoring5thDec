#include "Ball.h"

Ball::Ball() 		  
{

};

void Ball::SetUp(const sf::Texture &texture)
{
	m_ballSprite.setTexture(texture);
	m_ballSprite.setPosition(positionX, positionY);
	m_ballSprite.setScale(1.0f, 1.0f);
};

void Ball::Update(float deltatime)
{
	WorldConstraining(positionX, positionY);
	m_direction = Normalized(m_direction);
	positionX += m_direction.x * m_speed * deltatime;
	positionY += m_direction.y * m_speed * deltatime;
	m_ballSprite.setPosition(positionX, positionY);
};

const float Ball::Length(const sf::Vector2f& rhs) noexcept
{
	return std::sqrtf(rhs.x * rhs.x + rhs.y * rhs.y);
};

sf::Vector2f Ball::Normalized(const sf::Vector2f& rhs) {
	const float length = 1.0f / Length(rhs);
	const float x = rhs.x * length;
	const float y = rhs.y * length;
	return sf::Vector2f{ x, y };
}

void Ball::WorldConstraining(float posX, float posY) noexcept
{
	if (posX < static_cast<float>(worldBounds.left))
	{
		m_direction.x = -m_direction.x;
	}
	if (posX >= static_cast<float>(worldBounds.width - 50))
	{
		m_direction.x = -m_direction.x;
	}
	if (posY < static_cast<float>(worldBounds.top))
	{
		m_direction.y = -m_direction.y;
	}
	/*if (posY >= (float)worldBounds.height -50)
	{
		m_direction.y = -m_direction.y;
	}*/

}

void Ball::Restart() noexcept
{
	m_speed = 200.0f;
	positionX = 500.0f;
	positionY = 400.0f;
	m_direction.x = positionX;
	m_direction.y = positionY;
}