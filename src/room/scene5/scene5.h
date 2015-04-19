#pragma once
#include "../room.h"

class rScene5 : public bRoom
{
public:
	rScene5(sf::RenderWindow* window);
	~rScene5();

	void start();
	void update(float deltaTime);
	void render();
private:
	void pollEvents();
};