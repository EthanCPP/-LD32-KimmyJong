#include "bullet.h"

eBullet::eBullet(int direction)
	: bEntity()
{
	m_direction = direction;
}

eBullet::~eBullet()
{

}

void eBullet::update(float deltaTime)
{
	m_deltaTime = deltaTime;

	if (m_direction == 0)
		m_sprite.move(0, -0.4f * deltaTime);
	else if (m_direction == 1)
		m_sprite.move(0, 0.4f * deltaTime);
	else if (m_direction == 2)
		m_sprite.move(-0.4f * deltaTime, 0);
	else if (m_direction == 3)
		m_sprite.move(0.4f * deltaTime, 0);
}