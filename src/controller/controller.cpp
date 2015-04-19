#include "controller.h"

bController::bController(sf::RenderWindow* window)
{
	bWindow = window;

	GS = GameState::SCENE1;

	r_scene1 = new rScene1(window);
	r_scene1->start();

	r_scene2 = new rScene2(window);
	r_scene3 = new rScene3(window);
	r_scene4 = new rScene4(window);
	r_scene5 = new rScene5(window);
	r_scene6 = new rScene6(window);
	r_scene7 = new rScene7(window);
}

bController::~bController()
{
	delete bWindow;
}

void bController::start()
{
	while (bWindow->isOpen())
	{
		step();
	}
}

void bController::step()
{
	bDeltaTime = (float)m_deltaClock.restart().asMilliseconds();

	switch (GS)
	{
	case GameState::SCENE1:
		r_scene1->update(bDeltaTime);
		r_scene1->render();
		if (r_scene1->message == "go:Scene2")
		{
			GS = GameState::SCENE2;
			r_scene2->start();
		}
		break;
	case GameState::SCENE2:
		r_scene2->update(bDeltaTime);
		r_scene2->render();
		if (r_scene2->message == "dead")
		{
			r_scene2->stop();
			r_scene2->start();
		}
		if (r_scene2->message == "go:Scene3")
		{
			GS = GameState::SCENE3;
			r_scene2->stop();
			r_scene3->start();
		}
		break;
	case GameState::SCENE3:
		r_scene3->update(bDeltaTime);
		r_scene3->render();
		if (r_scene3->message == "dead")
		{
			r_scene3->stop();
			r_scene3->start();
		}
		if (r_scene3->message == "go:Scene4")
		{
			GS = GameState::SCENE4;
			r_scene3->stop();
			r_scene4->start();
		}
		break;
	case GameState::SCENE4:
		r_scene4->update(bDeltaTime);
		r_scene4->render();
		if (r_scene4->message == "dead")
		{
			r_scene4->stop();
			r_scene4->start();
		}
		if (r_scene4->message == "go:Scene5")
		{
			GS = GameState::SCENE5;
			r_scene4->stop();
			r_scene5->start();
		}
		break;
	case GameState::SCENE5:
		r_scene5->update(bDeltaTime);
		r_scene5->render();
		if (r_scene5->message == "dead")
		{
			r_scene5->stop();
			r_scene5->start();
		}
		if (r_scene5->message == "go:Scene6")
		{
			GS = GameState::SCENE6;
			r_scene5->stop();
			r_scene6->start();
		}
		break;
	case GameState::SCENE6:
		r_scene6->update(bDeltaTime);
		r_scene6->render();
		if (r_scene6->message == "dead")
		{
			r_scene6->stop();
			r_scene6->start();
		}
		if (r_scene6->message == "go:Scene7")
		{
			GS = GameState::SCENE7;
			r_scene6->stop();
			r_scene7->start();
		}
		break;
	case GameState::SCENE7:
		r_scene7->update(bDeltaTime);
		r_scene7->render();
		break;
	default:
		bWindow->close();
	}
}