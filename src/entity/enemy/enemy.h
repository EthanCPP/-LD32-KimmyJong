#pragma once
#include "../entity.h"
#include <math.h>

class eEnemy : public bEntity
{
public:
	eEnemy();
	~eEnemy();

	void update(float deltaTime, int playerX, int playerY);

	bool reduceHealth(int amount);
	inline int getHealth() const { return m_health; }

	inline int getDirection() const { return m_direction; }
	bool isShooting;
protected:
	int m_health;
	float m_deltaTime;
	int m_direction;
	int m_playerX, m_playerY;

	int m_shootTicks;
	bool m_canShoot;
	int m_shootSpeed;
	bool m_obama = false;

	void moveToPlayer();
};