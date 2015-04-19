#pragma once
#include "../entity.h"

class eBullet : public bEntity
{
public:
	eBullet(int direction);
	~eBullet();

	void update(float deltaTime);
private:
	float m_deltaTime;
	int m_direction;
};