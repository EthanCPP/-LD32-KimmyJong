#pragma once
#include "../room.h"

class rScene2 : public bRoom
{
public:
	rScene2(sf::RenderWindow* window);
	~rScene2();

	void start();
	void update(float deltaTime);
	void render();
private:
	void pollEvents();
};