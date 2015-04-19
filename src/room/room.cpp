#include "room.h"

bRoom::bRoom(sf::RenderWindow* window)
{
	m_window = window;
	RM = new bResourceManager();

	m_f_arial.loadFromFile("res/font/arial.ttf");
	
}

bRoom::~bRoom()
{
	delete m_window;
}

void bRoom::stop()
{
	player = NULL;
	m_sprites.clear();
	m_sounds.clear();
	m_music.clear();
	m_text.clear();
	m_collisions.clear();
	m_enemies.clear();
	m_bullets.clear();
	m_potatoes.clear();
}

void bRoom::pollEvents()
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

void bRoom::createSpotlight()
{
	RM->loadTexture("zspotlight", "res/img/spotlight.png");
	m_sprites["zspotlight"] = RM->createSprite("zspotlight");
	m_sprites["zspotlight"].setOrigin(960, 540);
}

void bRoom::moveSpotlight(int x, int y)
{
	m_sprites["zspotlight"].setPosition((float)x, (float)y);
}

void bRoom::createPlayer(int x, int y)
{
	RM->loadTexture("player", "res/img/player.png");
	player = new ePlayer();

	RM->loadTexture("health_back", "res/img/health_back.png");
	RM->loadTexture("health_front", "res/img/health_front.png");
	m_sprites["zzhealth_back"] = RM->createSprite("health_back");
	m_sprites["zzhealth_back"].setPosition(10, 479);
	m_sprites["zzhealth_front"] = RM->createSprite("health_front");
	m_sprites["zzhealth_front"].setPosition(10, 479);
	
	sf::Sprite plrspr = RM->createSprite("player");
	plrspr.setPosition((float)x, (float)y);
	plrspr.setTextureRect(sf::IntRect(0, 0, 32, 32));
	player->setSprite(plrspr);

	// load sounds
	RM->loadSoundBuffer("hit", "res/sound/hit.wav");
	m_sounds["hit"] = RM->getSound("hit");

	RM->loadSoundBuffer("die", "res/sound/die.wav");
	m_sounds["die"] = RM->getSound("die");

	RM->loadSoundBuffer("shoot", "res/sound/shoot.wav");
	m_sounds["shoot"] = RM->getSound("shoot");

	// music
	m_music["music"].openFromFile("res/sound/music.ogg");
	m_music["music"].setLoop(true);
	m_music["music"].play();
}

void bRoom::createWorld(std::string path, bWorldType worldType)
{
	RM->loadTexture("world" + std::to_string(worldType), path);
	sf::Image wimage;
	wimage.loadFromFile(path);

	int n = 0;
	for (unsigned int y = 0; y < 17; y++)
	{
		for (unsigned int x = 0; x < 30; x++)
		{
			if (worldType == bWorldType::COLLISION)
			{
				if (wimage.getPixel(x * 32, y * 32) != sf::Color(0, 0, 0, 0))
				{
					n++;
					m_sprites["world_wall" + std::to_string(n)] = RM->createSprite("world" + std::to_string(worldType), sf::IntRect(x * 32, y * 32, 32, 32));
					m_sprites["world_wall" + std::to_string(n)].setPosition(x * 32.0f, y * 32.0f);

					m_collisions.push_back("world_wall" + std::to_string(n));
				}
			}
			else if (worldType == bWorldType::ENEMIES)
			{
				if (wimage.getPixel(x * 32, y * 32) != sf::Color(0, 0, 0, 0))
				{
					n++;
					nenemies++;
					sf::Sprite enemyspr = RM->createSprite("enemy");
					enemyspr.setPosition(x * 32.0f, y * 32.0f);

					eEnemy* enemy = new eEnemy();
					enemy->setSprite(enemyspr);

					m_enemies.push_back(enemy);
				}
			}
			else if (worldType == bWorldType::OBAMA)
			{
				if (wimage.getPixel(x * 32, y * 32) != sf::Color(0, 0, 0, 0))
				{
					n++;
					nenemies++;
					sf::Sprite obamaspr = RM->createSprite("obama");
					obamaspr.setPosition(x * 32.0f, y * 32.0f);

					m_obama = new eObama();
					m_obama->setSprite(obamaspr);
				}
			}
			else if (worldType == bWorldType::DOOR)
			{
				if (wimage.getPixel(x * 32, y * 32) != sf::Color(0, 0, 0, 0))
				{
					n++;
					m_sprites["DOOR" + std::to_string(n)] = RM->createSprite("door");
					m_sprites["DOOR" + std::to_string(n)].setPosition(x * 32.0f, y * 32.0f);

					m_collisions.push_back("DOOR" + std::to_string(n));
				}
			}
		}
	}
}

void bRoom::createSpeech(std::string id, std::string text)
{
	m_sprites["speech"] = RM->createSprite(id);
	m_sprites["speech"].setPosition(0, 380);

	sf::Text speechtxt;
	speechtxt.setFont(m_f_arial);
	speechtxt.setCharacterSize(16);
	speechtxt.setColor(sf::Color::Black);
	speechtxt.setString(text);
	speechtxt.setPosition(190, 415);
	m_text["speech"] = speechtxt;
}

bool bRoom::checkCollision(float x, float y, bCollisionType col)
{
	if (col == bCollisionType::PLAYER)
	{
		for (unsigned int i = 0; i < m_collisions.size(); i++)
		{
			float ex = m_sprites[m_collisions[i]].getPosition().x;
			float ey = m_sprites[m_collisions[i]].getPosition().y;

			if (x + 32 >= ex && x <= ex + 32 && y + 32 >= ey && y <= ey + 32)
				return true;
		}
	}
	else if (col == bCollisionType::POTATO)
	{
		// walls
		for (unsigned int i = 0; i < m_collisions.size(); i++)
		{
			float ex = m_sprites[m_collisions[i]].getPosition().x;
			float ey = m_sprites[m_collisions[i]].getPosition().y;

			if (x + 32 >= ex && x <= ex + 32 && y + 32 >= ey && y <= ey + 32)
			{
				potatoCollisionType = 0;
				return true;
			}
		}

		// enemies
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			float ex = (float)m_enemies[i]->getX();
			float ey = (float)m_enemies[i]->getY();

			if (x + 32 >= ex && x <= ex + 32 && y + 32 >= ey && y <= ey + 32)
			{
				potatoCollisionEnemyIndex = i;
				potatoCollisionType = 1;
				return true;
			}
		}

		// obama
		if (m_obama != NULL)
		{
			float ox = (float)m_obama->getX();
			float oy = (float)m_obama->getY();

			if (x + 32 >= ox && x <= ox + 32 && y + 32 >= oy && y <= oy + 32)
			{
				potatoCollisionType = 2;
				return true;
			}
		}
	}
	else if (col == bCollisionType::BULLET)
	{
		// walls
		for (unsigned int i = 0; i < m_collisions.size(); i++)
		{
			float ex = m_sprites[m_collisions[i]].getPosition().x;
			float ey = m_sprites[m_collisions[i]].getPosition().y;

			if (x + 32 >= ex && x <= ex + 32 && y + 32 >= ey && y <= ey + 32)
			{
				bulletCollisionType = 0;
				return true;
			}
		}

		// player
		float px = (float)player->getX();
		float py = (float)player->getY();

		if (x + 32 >= px && x <= px + 32 && y + 32 >= py && y <= py + 32)
		{
			bulletCollisionType = 1;
			return true;
		}
	}

	return false;
}

void bRoom::playerStep()
{
	player->update();

	if (potatoCooldown > 0)
	{
		potatoCooldownTicks++;
		if (potatoCooldownTicks >= 20)
		{
			potatoCooldownTicks = 0;
			potatoCooldown--;
		}
	}

	m_sprites["zzhealth_front"].setScale(((float)player->getHealth() / 100.0f), 1.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !checkCollision((float)player->getX() - 0.4f * m_deltaTime, (float)player->getY(), bCollisionType::PLAYER))
		player->moveLeft(m_deltaTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !checkCollision((float)player->getX() + 0.4f * m_deltaTime, (float)player->getY(), bCollisionType::PLAYER))
		player->moveRight(m_deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !checkCollision((float)player->getX(), (float)player->getY() - 0.4f * m_deltaTime, bCollisionType::PLAYER))
		player->moveUp(m_deltaTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !checkCollision((float)player->getX(), (float)player->getY() + 0.4f * m_deltaTime, bCollisionType::PLAYER))
		player->moveDown(m_deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (potatoCooldown == 0)
		{
			m_sounds["shoot"].play();
			potatoCooldown = 1;
			npotatoes++;
			sf::Sprite potatospr = RM->createSprite("potato");
			potatospr.setPosition((float)player->getX(), (float)player->getY());

			ePotato* potato = new ePotato(player->getDirection());
			potato->setSprite(potatospr);

			m_potatoes.push_back(potato);
		}
	}
}

void bRoom::updateEnemies()
{
	if (nenemies <= 0)
	{
		// remove doors
		for (unsigned int i = 0; i < m_collisions.size(); i++)
		{
			if (m_collisions[i].substr(0, 4) == "DOOR")
			{
				m_sprites[m_collisions[i]].setPosition(-500, -500);
				m_collisions.erase(m_collisions.begin() + i);
			}
		}
	}

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->update(m_deltaTime, player->getX(), player->getY());
		if (m_enemies[i]->isShooting)
		{
			m_sounds["shoot"].play();
			m_enemies[i]->isShooting = false;

			sf::Sprite bulletspr = RM->createSprite("bullet");
			bulletspr.setPosition((float)m_enemies[i]->getX(), (float)m_enemies[i]->getY());

			eBullet* bullet = new eBullet(m_enemies[i]->getDirection());
			bullet->setSprite(bulletspr);

			m_bullets.push_back(bullet);
		}
	}

	if (m_obama != NULL)
	{
		m_obama->update(m_deltaTime, player->getX(), player->getY());
		if (m_obama->isShooting)
		{
			m_sounds["shoot"].play();
			m_obama->isShooting = false;

			sf::Sprite bulletspr = RM->createSprite("bullet");
			bulletspr.setPosition((float)m_obama->getX(), (float)m_obama->getY());

			eBullet* bullet = new eBullet(m_obama->getDirection());
			bullet->setSprite(bulletspr);

			m_bullets.push_back(bullet);
		}
	}
}

void bRoom::updateBullets()
{
	if (m_bullets.size() > 0)
	{
		for (unsigned int i = 0; i < m_bullets.size(); i++)
		{
			if (m_bullets[i]->getX() < 0 || m_bullets[i]->getX() > 960 || m_bullets[i]->getY() < 0 || m_bullets[i]->getY() > 540)
			{
				delete m_bullets[i];
				m_bullets.erase(m_bullets.begin() + i);
			}
			else
			{
				m_bullets[i]->update(m_deltaTime);
				if (checkCollision((float)m_bullets[i]->getX(), (float)m_bullets[i]->getY(), bCollisionType::BULLET))
				{
					if (bulletCollisionType == 1) // player
					{
						if (player->reduceHealth(15))
						{
							m_sounds["die"].play();
							message = "dead";
						}
					}

					// play hit sound
					m_sounds["hit"].play();

					delete m_bullets[i];
					m_bullets.erase(m_bullets.begin() + i);
				}
			}
		}
	}
}

void bRoom::updatePotatoes()
{
	for (unsigned int i = 0; i < m_potatoes.size(); i++)
	{
		if (m_potatoes[i]->getX() < 0 || m_potatoes[i]->getX() > 960 || m_potatoes[i]->getY() < 0 || m_potatoes[i]->getY() > 540)
		{
			delete m_potatoes[i];
			m_potatoes.erase(m_potatoes.begin() + i);
		}
		else
		{
			m_potatoes[i]->update(m_deltaTime);
			if (checkCollision((float)m_potatoes[i]->getX(), (float)m_potatoes[i]->getY(), bCollisionType::POTATO))
			{
				if (potatoCollisionType == 1) // enemies
				{
					if (m_enemies[potatoCollisionEnemyIndex]->reduceHealth(50))
					{
						m_sounds["die"].play();
						nenemies -= 1;
						delete m_enemies[potatoCollisionEnemyIndex];
						m_enemies.erase(m_enemies.begin() + potatoCollisionEnemyIndex);
					}
				}

				if (potatoCollisionType == 2) // obama
				{
					if (m_obama->reduceHealth(50))
					{
						m_sounds["die"].play();
						nenemies -= 1;
						delete m_obama; 
						m_obama = NULL;
					}
				}

				// play hit sound
				m_sounds["hit"].play();

				delete m_potatoes[i];
				m_potatoes.erase(m_potatoes.begin() + i);
			}
		}
	}
}

void bRoom::drawSprites()
{
	if (player != NULL)
		m_window->draw(player->getSprite());

	for (unsigned int i = 0; i < m_potatoes.size(); i++)
		m_window->draw(m_potatoes[i]->getSprite());

	for (unsigned int i = 0; i < m_enemies.size(); i++)
		m_window->draw(m_enemies[i]->getSprite());

	for (unsigned int i = 0; i < m_bullets.size(); i++)
		m_window->draw(m_bullets[i]->getSprite());

	for (auto spr : m_sprites)
		m_window->draw(m_sprites[spr.first]);

	if (m_obama != NULL)
		m_window->draw(m_obama->getSprite());
}

void bRoom::drawText()
{
	for (auto txt : m_text)
		m_window->draw(m_text[txt.first]);
}