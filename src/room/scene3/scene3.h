#pragma once
#include "../room.h"

class rScene3 : public bRoom
{
public:
	rScene3(sf::RenderWindow* window);
	~rScene3();

	void start();
	void update(float deltaTime);
	void render();
private:
	void pollEvents();
};