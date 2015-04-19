#include "potato.h"

ePotato::ePotato(int direction)
	: bEntity()
{
	m_direction = (ePotatoDirection)direction;
}

ePotato::~ePotato()
{

}

void ePotato::update(float deltaTime)
{
	m_deltaTime = deltaTime;

	if (m_direction == ePotatoDirection::UP)
		m_sprite.move(0, -0.4f * deltaTime);
	else if (m_direction == ePotatoDirection::DOWN)
		m_sprite.move(0, 0.4f * deltaTime);
	else if (m_direction == ePotatoDirection::LEFT)
		m_sprite.move(-0.4f * deltaTime, 0);
	else if (m_direction == ePotatoDirection::RIGHT)
		m_sprite.move(0.4f * deltaTime, 0);
}