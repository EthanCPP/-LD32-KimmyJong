#pragma once
#include "../stdafx.h"
#include "gamestate.h"

#include "../room/scene1/scene1.h"
#include "../room/scene2/scene2.h"
#include "../room/scene3/scene3.h"
#include "../room/scene4/scene4.h"
#include "../room/scene5/scene5.h"
#include "../room/scene6/scene6.h"
#include "../room/scene7/scene7.h"

class bController
{
public:
	bController(sf::RenderWindow* window);
	~bController();

	void start();
private:
	GameState GS;
	sf::RenderWindow* bWindow;
	sf::Clock m_deltaClock;
	float bDeltaTime;

	void step();
private:
	rScene1* r_scene1;
	rScene2* r_scene2;
	rScene3* r_scene3;
	rScene4* r_scene4;
	rScene5* r_scene5;
	rScene6* r_scene6;
	rScene7* r_scene7;
};