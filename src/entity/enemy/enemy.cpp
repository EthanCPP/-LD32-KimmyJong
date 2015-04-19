#include "enemy.h"

eEnemy::eEnemy()
	: bEntity()
{
	m_health = 100;
	isShooting = false;
	m_canShoot = false;
	m_shootSpeed = 85;
}

eEnemy::~eEnemy()
{

}

void eEnemy::update(float deltaTime, int playerX, int playerY)
{
	m_deltaTime = deltaTime;
	m_playerX = playerX;
	m_playerY = playerY;

	if (m_canShoot)
	{
		m_shootTicks++;
		if (m_shootTicks >= m_shootSpeed)
		{
			m_shootTicks = 0;
			isShooting = true;
		}
	}
	else
		m_shootTicks = 0;

	// check distance
	int d = m_obama ? 400 : 200;
	if (sqrt(pow(m_playerX - m_sprite.getPosition().x, 2) + pow(m_playerY - m_sprite.getPosition().y, 2)) < d)
	{
		if (m_obama)
			moveToPlayer();

		m_canShoot = true;

		// calculate direction
		if (m_sprite.getPosition().x - m_playerX > -32 && m_sprite.getPosition().x - m_playerX < 32)
		{
			// inline x
			if (m_sprite.getPosition().y - m_playerY > 0)
			{
				// player is above
				m_direction = 0;
			}
			else
			{
				// player is below
				m_direction = 1;
			}
		}
		else if (m_sprite.getPosition().x - m_playerX < 0)
		{
			// player is to the right
			m_direction = 3;
		}
		else
		{
			// player is to the left
			m_direction = 2;
		}
	}
	else
		m_canShoot = false;
}

void eEnemy::moveToPlayer()
{
	if (m_direction == 0)
		m_sprite.move(0, -0.02f * m_deltaTime);
	if (m_direction == 1)
		m_sprite.move(0, 0.02f * m_deltaTime);
	if (m_direction == 2)
		m_sprite.move(-0.02f * m_deltaTime, 0);
	if (m_direction == 3)
		m_sprite.move(0.02f * m_deltaTime, 0);
}

bool eEnemy::reduceHealth(int amount)
{
	m_health -= amount;
	if (m_health < 0)
		return true;

	return false;
}
