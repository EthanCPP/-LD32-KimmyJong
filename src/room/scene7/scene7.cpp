#include "scene7.h"

rScene7::rScene7(sf::RenderWindow* window)
	: bRoom(window)
{

}

rScene7::~rScene7()
{

}

void rScene7::start()
{
	message = "";
	nenemies = 0;

	RM->loadTexture("potato", "res/img/potato.png");
	RM->loadTexture("bullet", "res/img/bullet.png");
	RM->loadTexture("door", "res/img/door.png");

	createWorld("res/scene/s6w_collisions.png", bWorldType::COLLISION);

	createSpotlight();
	createPlayer(64, 192);
}

void rScene7::update(float deltaTime)
{
	pollEvents();
	m_deltaTime = deltaTime;

	playerStep();
	moveSpotlight(player->getX(), player->getY());

	updatePotatoes();
	updateEnemies();
	updateBullets();
}

void rScene7::render()
{
	m_window->clear();

	drawSprites();
	drawText();

	m_window->display();
}

void rScene7::pollEvents()
{
	while (m_window->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		default:
			break;
		}
	}
}