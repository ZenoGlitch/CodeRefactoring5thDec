#include "Brick.h"

Brick::Brick()
{

};

Brick::~Brick()
{

};

void Brick::SetUp(sf::Texture* texture)
{
	m_texture = *texture;
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	float x = 0;
	float y = 100;
	for (int i = 0; i < m_brickObject.size(); i++)
	{
		
		m_brickObject[i].sprite.setTexture(m_texture);
		m_brickObject[i].color = sf::Color::Red;
		m_brickObject[i].positionX = x;
		m_brickObject[i].positionY = y;
		x += 100;
		m_brickObject[i].sprite.setPosition(m_brickObject[i].positionX, m_brickObject[i].positionY);
		m_brickObject[i].sprite.setColor(m_brickObject[i].color);
	};
}
	

void Brick::Update()
{
	
};

void Brick::Restart()
{
	m_brickObject.clear();

	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	m_brickObject.push_back({});
	float x = 0;
	float y = 100;
	for (int i = 0; i < m_brickObject.size(); i++)
	{

		m_brickObject[i].sprite.setTexture(m_texture);
		m_brickObject[i].color = sf::Color::Red;
		m_brickObject[i].positionX = x;
		m_brickObject[i].positionY = y;
		x += 100;
		m_brickObject[i].sprite.setPosition(m_brickObject[i].positionX, m_brickObject[i].positionY);
		m_brickObject[i].sprite.setColor(m_brickObject[i].color);
	};
}