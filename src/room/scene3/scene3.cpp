#include "scene3.h"

rScene3::rScene3(sf::RenderWindow* window)
	: bRoom(window)
{

}

rScene3::~rScene3()
{

}

void rScene3::start()
{
	message = "";
	nenemies = 0;

	RM->loadTexture("potato", "res/img/potato.png");
	RM->loadTexture("enemy", "res/img/enemy.png");
	RM->loadTexture("bullet", "res/img/bullet.png");
	RM->loadTexture("door", "res/img/door.png");

	createWorld("res/scene/s2w_collisions.png", bWorldType::COLLISION);
	createWorld("res/scene/s2w_enemies.png", bWorldType::ENEMIES);
	createWorld("res/scene/s2w_door.png", bWorldType::DOOR);

	createSpotlight();
	createPlayer(32, 192);
}

void rScene3::update(float deltaTime)
{
	pollEvents();
	m_deltaTime = deltaTime;

	playerStep();
	moveSpotlight(player->getX(), player->getY());

	updatePotatoes();
	updateEnemies();
	updateBullets();

	if (player->getX() > 928)
		message = "go:Scene4";
}

void rScene3::render()
{
	m_window->clear();

	drawSprites();
	drawText();

	m_window->display();
}

void rScene3::pollEvents()
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