#include "player.h"

ePlayer::ePlayer()
	: bEntity()
{
	animticks = 0;
	frame = 0;
	m_direction = 2;
	m_health = 100;
}

ePlayer::~ePlayer()
{

}

bool ePlayer::reduceHealth(int amount)
{
	m_health -= amount;
	if (m_health < 0)
		return true;

	return false;
}

void ePlayer::update()
{
	animticks++;
	if (animticks >= 5)
	{
		animticks = 0;
		frame++;

		if (frame >= 7)
			frame = 0;

		m_sprite.setTextureRect(sf::IntRect(32 * frame, 0, 32, 32));
	}
}

void ePlayer::moveLeft(float deltaTime)
{
	m_direction = 2;
	m_sprite.move(-0.1f * deltaTime, 0);
}

void ePlayer::moveRight(float deltaTime)
{
	m_direction = 3;
	m_sprite.move(0.1f * deltaTime, 0);
}

void ePlayer::moveUp(float deltaTime)
{
	m_direction = 0;
	m_sprite.move(0, -0.1f * deltaTime);
}

void ePlayer::moveDown(float deltaTime)
{
	m_direction = 1;
	m_sprite.move(0, 0.1f * deltaTime);
}