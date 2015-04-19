#pragma once
#include "../room.h"

enum rScene1State
{
	NEWSPAPER,
	DIALOG1,
	DIALOG2,
	DIALOG3,
	DIALOG4,
	DIALOG5
};

class rScene1 : public bRoom
{
public:
	rScene1(sf::RenderWindow* window);
	~rScene1();

	void start();
	void update(float deltaTime);
	void render();
private:
	void createNewspaper();
	void pollEvents();

	rScene1State STATE;
};