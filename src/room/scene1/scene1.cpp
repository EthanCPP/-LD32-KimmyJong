#include "scene1.h"

rScene1::rScene1(sf::RenderWindow* window)
	: bRoom(window)
{

}

rScene1::~rScene1()
{

}

void rScene1::start()
{
	STATE = rScene1State::NEWSPAPER;
	createNewspaper();
}

void rScene1::createNewspaper()
{
	RM->loadTexture("newspaper", "res/img/scene1/newspaper.png");
	m_sprites["newspaper"] = RM->createSprite("newspaper");

	RM->loadTexture("kimspeech", "res/img/kimspeech.png");
	RM->loadTexture("playerspeech", "res/img/playerspeech.png");
}

void rScene1::update(float deltaTime)
{
	pollEvents();
	m_deltaTime = deltaTime;
}

void rScene1::render()
{
	m_window->clear();

	drawSprites();
	drawText();

	m_window->display();
}

void rScene1::pollEvents()
{
	while (m_window->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyReleased:
			if (STATE == rScene1State::NEWSPAPER)
			{
				STATE = rScene1State::DIALOG1;
				m_sprites.clear();

				createSpeech("kimspeech", "Have you gained access to Obama's bunker, Steve?");
			}
			else
			if (m_event.key.code == sf::Keyboard::Return)
			{
				if (STATE == rScene1State::DIALOG1)
				{
					STATE = rScene1State::DIALOG2;
					m_sprites.clear();

					createSpeech("playerspeech", "Yes sir, I'm in. Give me a few minutes and he'll be gone.");
				}
				else if (STATE == rScene1State::DIALOG2)
				{
					STATE = rScene1State::DIALOG3;
					m_sprites.clear();

					createSpeech("kimspeech", "Good. Don't forget to use the potato. They'll never see you coming.");
				}
				else if (STATE == rScene1State::DIALOG3)
				{
					STATE = rScene1State::DIALOG4;
					m_sprites.clear();

					createSpeech("kimspeech", "Press SPACE to throw a potato.");
				}
				else if (STATE == rScene1State::DIALOG4)
				{
					STATE = rScene1State::DIALOG5;
					m_sprites.clear();

					createSpeech("playerspeech", "Got it. I'm on my way.");
				}
				else if (STATE == rScene1State::DIALOG5)
				{
					message = "go:Scene2";
				}
			}
			break;
		default:
			break;
		}
	}
}