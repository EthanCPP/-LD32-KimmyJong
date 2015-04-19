#include "scene6.h"

rScene6::rScene6(sf::RenderWindow* window)
	: bRoom(window)
{

}

rScene6::~rScene6()
{

}

void rScene6::start()
{
	message = "";
	nenemies = 0;

	RM->loadTexture("potato", "res/img/potato.png");
	RM->loadTexture("obama", "res/img/obama.png");
	RM->loadTexture("bullet", "res/img/bullet.png");
	RM->loadTexture("door", "res/img/door.png");

	createWorld("res/scene/s5w_collisions.png", bWorldType::COLLISION);
	createWorld("res/scene/s5w_obama.png", bWorldType::OBAMA);
	createWorld("res/scene/s5w_door.png", bWorldType::DOOR);

	createSpotlight();
	createPlayer(64, 192);
}

void rScene6::update(float deltaTime)
{
	pollEvents();
	m_deltaTime = deltaTime;

	playerStep();
	moveSpotlight(player->getX(), player->getY());

	updatePotatoes();
	updateEnemies();
	updateBullets();

	if (player->getX() > 928)
		message = "go:Scene7";
}

void rScene6::render()
{
	m_window->clear();

	drawSprites();
	drawText();

	m_window->display();
}

void rScene6::pollEvents()
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