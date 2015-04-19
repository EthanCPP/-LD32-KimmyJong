#pragma once
#include "../entity.h"

class ePlayer : public bEntity
{
public:
	ePlayer();
	~ePlayer();

	void update();
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);
	void moveUp(float deltaTime);
	void moveDown(float deltaTime);
	
	inline int getDirection() const { return m_direction; }

	bool reduceHealth(int amount);
	inline int getHealth() const { return m_health; }
private:
	int animticks;
	int frame;
	int m_direction;
	int m_health;
};