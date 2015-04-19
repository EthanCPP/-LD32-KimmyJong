#pragma once
#include "../room.h"

class rScene6 : public bRoom
{
public:
	rScene6(sf::RenderWindow* window);
	~rScene6();

	void start();
	void update(float deltaTime);
	void render();
private:
	void pollEvents();
};