#pragma once
#include "../stdafx.h"
#include "../resource/resourcemanager.h"
#include "../entity/player/player.h"
#include "../entity/potato/potato.h"
#include "../entity/enemy/enemy.h"
#include "../entity/bullet/bullet.h"
#include "../entity/enemy/obama/obama.h"

enum bWorldType
{
	COLLISION,
	ENEMIES,
	DOOR,
	OBAMA
};

enum bCollisionType
{
	PLAYER,
	POTATO,
	BULLET,
};

class bRoom
{
public:
	bRoom(sf::RenderWindow* window);
	~bRoom();

	void stop();

	std::string message;
protected:
	sf::RenderWindow* m_window;
	sf::Event m_event;
	float m_deltaTime;

	bResourceManager* RM;
protected:
	virtual void pollEvents();
	virtual void drawSprites();
	virtual void drawText();
	
	void createWorld(std::string path, bWorldType worldType);
	void createSpeech(std::string id, std::string text);
	void createSpotlight();
	void moveSpotlight(int x, int y);
	bool checkCollision(float x, float y, bCollisionType col);

	ePlayer* player = NULL;
	void createPlayer(int x, int y);
	void playerStep();

	sf::Font m_f_arial;

	std::map<std::string, sf::Sprite> m_sprites;
	std::map<std::string, sf::Sound> m_sounds;
	std::map<std::string, sf::Music> m_music;
	std::map<std::string, sf::Text> m_text;

	std::vector<std::string> m_collisions;

	std::vector<eEnemy*> m_enemies;
	void updateEnemies();
	int nenemies = 0;

	eObama* m_obama = NULL;

	std::vector<eBullet*> m_bullets;
	void updateBullets();
	int bulletCollisionType; // 0 = wall; 1 = player

	int npotatoes;
	int potatoCollisionType; // 0 = wall; 1 = enemy
	int potatoCollisionEnemyIndex;
	double potatoCooldown;
	int potatoCooldownTicks;
	std::vector<ePotato*> m_potatoes;
	void updatePotatoes();
};