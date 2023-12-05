#pragma once
#include "batch.hpp"
#include <vector>

struct parallaxParts
{
	sf::Sprite sprite;
	sf::Color color;
	float positionX, positionY;
};

class parallaxBackground
{
public:
	parallaxBackground();
	~parallaxBackground();
	// The idea was having to different star with different color however this png I could not change color on and that I only 1 hour before deadline to finish.
	std::vector<parallaxParts> m_fallingStarYellow;
	std::vector<parallaxParts> m_fallingStarRed;
	void SetUp(sf::Texture* texture);
	void Update(float deltatime);
private:
	sf::Texture m_texture;
};