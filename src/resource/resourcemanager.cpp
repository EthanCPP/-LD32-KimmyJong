#include "resourcemanager.h"

void bResourceManager::reset()
{
	m_textures.clear();
	m_sounds.clear();
}

sf::Texture bResourceManager::loadTexture(std::string id, std::string path)
{
	sf::Texture texture;
	texture.loadFromFile(path);

	m_textures[id] = texture;
	return texture;
}

sf::Texture bResourceManager::getTexture(std::string id)
{
	return m_textures[id];
}

sf::Sprite bResourceManager::createSprite(std::string tex_id, sf::IntRect crop)
{
	sf::Sprite sprite;
	sprite.setTexture(m_textures[tex_id]);
	sprite.setTextureRect(crop);

	return sprite;
}

sf::Sprite bResourceManager::createSprite(std::string tex_id)
{
	return createSprite(tex_id, sf::IntRect(0, 0, m_textures[tex_id].getSize().x, m_textures[tex_id].getSize().y));
}

sf::SoundBuffer bResourceManager::loadSoundBuffer(std::string id, std::string path)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile(path);

	m_sounds[id] = buffer;
	return buffer;
}

sf::Sound bResourceManager::getSound(std::string id)
{
	sf::Sound sound;
	sound.setBuffer(m_sounds[id]);

	return sound;
}