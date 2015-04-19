#pragma once
#include "../room.h"

class rScene7 : public bRoom
{
public:
	rScene7(sf::RenderWindow* window);
	~rScene7();

	void start();
	void update(float deltaTime);
	void render();
private:
	void pollEvents();
};