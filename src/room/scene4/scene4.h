#pragma once
#include "../room.h"

class rScene4 : public bRoom
{
public:
	rScene4(sf::RenderWindow* window);
	~rScene4();

	void start();
	void update(float deltaTime);
	void render();
private:
	void pollEvents();
};