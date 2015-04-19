#include "scene2.h"

rScene2::rScene2(sf::RenderWindow* window)
	: bRoom(window)
{

}

rScene2::~rScene2()
{

}

void rScene2::start()
{
	message = "";
	nenemies = 0;

	RM->loadTexture("potato", "res/img/potato.png");
	RM->loadTexture("enemy", "res/img/enemy.png");
	RM->loadTexture("bullet", "res/img/bullet.png");
	RM->loadTexture("door", "res/img/door.png");

	createWorld("res/scene/s1w_collisions.png", bWorldType::COLLISION);
	createWorld("res/scene/s1w_enemies.png", bWorldType::ENEMIES);
	createWorld("res/scene/s1w_door.png", bWorldType::DOOR);

	createSpotlight();
	createPlayer(64, 256);
}

void rScene2::update(float deltaTime)
{
	pollEvents();
	m_deltaTime = deltaTime;

	playerStep();
	moveSpotlight(player->getX(), player->getY());

	updatePotatoes();
	updateEnemies();
	updateBullets();

	if (player->getX() > 928)
		message = "go:Scene3";
}

void rScene2::render()
{
	m_window->clear();

	drawSprites();
	drawText();

	m_window->display();
}

void rScene2::pollEvents()
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