#pragma once
#include "../stdafx.h"

class bEntity
{
public:
	bEntity();
	~bEntity();

	void setSprite(sf::Sprite sprite);
	inline sf::Sprite getSprite() { return m_sprite; }
	inline int getX() const { return (int)m_sprite.getPosition().x; }
	inline int getY() const { return (int)m_sprite.getPosition().y; }
protected:
	sf::Sprite m_sprite;
};