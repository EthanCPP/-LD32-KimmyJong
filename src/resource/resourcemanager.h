#pragma once
#include "../stdafx.h"

class bResourceManager
{
public:
	bResourceManager(){}
	~bResourceManager(){}

	void reset();

	sf::Texture loadTexture(std::string id, std::string path);
	sf::Texture getTexture(std::string id);
	sf::Sprite createSprite(std::string tex_id, sf::IntRect crop);
	sf::Sprite createSprite(std::string tex_id);

	sf::SoundBuffer loadSoundBuffer(std::string id, std::string path);
	sf::Sound getSound(std::string id);
private:
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::SoundBuffer> m_sounds;
};