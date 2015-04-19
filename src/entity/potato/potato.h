#pragma once
#include "../entity.h"

enum ePotatoDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class ePotato : public bEntity
{
public:
	ePotato(int direction);
	~ePotato();

	void update(float deltaTime);

private:
	float m_deltaTime;
	ePotatoDirection m_direction;
};