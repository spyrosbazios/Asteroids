#include "Game.h"
#include "graphics.h"
#include "Config.h"
#include "Plane.h"
#include "Lives.h"
#include "windows.h"
Game::Game()
{
	planeA = new Plane();
	lives = new Lives();
}

void Game::init()
{
	graphics::playMusic("Assets\\sounds\\music.mp3", 0.5f, true, 4000);
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawGameScreen();
	}
	else if (status == STATUS_GAMEOVER)
	{
		drawGameoverScreen();
	}
}

void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateGameScreen();
	}
	else if (status == STATUS_GAMEOVER)
	{
		updateGameoverScreen();
	}
}

void Game::spawnMeteorite()
{
	if (state)
	{
		timeSaved = graphics::getGlobalTime();
		state = !state;
	}
	if ((graphics::getGlobalTime() - timeSaved) > 500.0f) {
		meteoriteList.push_back(new Meteorite);
		state = !state;
	}
}

void Game::checkMeteorite()
{
	if (!meteoriteList.empty())
	{
		for (auto const& i : meteoriteList)
		{
			if (!i->getState()) {
				meteoriteList.remove(i);
				break;
			}
		}
	}
}

void Game::checkBullet()
{
	if (!bulletList.empty())
	{
		for (auto const& i : bulletList)
		{
			if (!i->getState()) {
				bulletList.remove(i);
				break;
			}
		}
	}
}

void Game::checkCollisionBullet()
{
	if (!bulletList.empty())
	{
		for (auto const& i : bulletList)
		{
			Disk bulletDisk = i->getCollisionHull();
			for (auto const& j : meteoriteList)
			{
				Disk meteoriteDisk = j->getCollisionHull();

				float dx = bulletDisk.cx - meteoriteDisk.cx;
				float dy = bulletDisk.cy - meteoriteDisk.cy;

				if (sqrt(dx * dx + dy * dy) < bulletDisk.radius + meteoriteDisk.radius) {
					j->setState(false);
					graphics::playSound("Assets\\sounds\\explosion.wav", 1.0f, false);
					break;
				}
			}
		}
	}
}

void Game::checkCollisionPlane()
{
	if (!meteoriteList.empty())
	{
		Disk planeDisk = planeA->getCollisionHull();
		for (auto const& i : meteoriteList)
		{
			Disk meteoriteDisk = i->getCollisionHull();
			float dx = planeDisk.cx - meteoriteDisk.cx;
			float dy = planeDisk.cy - meteoriteDisk.cy;

			if (sqrt(dx * dx + dy * dy) < meteoriteDisk.radius + planeDisk.radius) {
				graphics::playSound("Assets\\sounds\\planeCrash.mp3", 1.0f, false);
				i->setState(false);
				lives->dieOnce();
				planeA->explode();
				break;
			}
		}
	}
}

void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_PLAYING;
	}
}

void Game::updateGameScreen()
{
	planeA->update();

	spawnMeteorite();

	if (!meteoriteList.empty()) {
		for (auto const& i : meteoriteList)
		{
			i->update();
		}
	}

	if (!bulletList.empty()) {
		for (auto const& i : bulletList)
		{
			i->update();
		}
	}

	checkBullet();											//checks if obj is out of canvas
	checkMeteorite();
	checkCollisionPlane();
	checkCollisionBullet();
	checkGameover();
}

void Game::checkGameover() {
	if (lives->gameoverCheck()) {
		status = STATUS_GAMEOVER;
	}
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	br.texture = "Assets\\main\\background.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::Brush transitionBrush;
	transitionBrush.fill_opacity = sinf(graphics::getGlobalTime() / 2000.0f);
	transitionBrush.texture = "Assets\\main\\background_transition.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, transitionBrush);

	graphics::setFont("Assets\\main\\font.ttf");
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 150);

	br.fill_color[0] = 0.3f + glow * 0.7f;
	br.fill_color[1] = 0.3f + glow * 0.7f;
	br.fill_color[2] = 0.3f + glow * 0.7f;
	char info[30];
	sprintf_s(info, "Press    enter    to    start");
	graphics::drawText((CANVAS_WIDTH / 2) - 700, CANVAS_HEIGHT / 2, 60, info, br);

	char info2[60];
	sprintf_s(info2, "USE    ARROWS    TO    NAVIGATE,    M    TO    SHOOT");
	graphics::drawText((CANVAS_WIDTH / 2) - 550, (CANVAS_HEIGHT / 2) + 120, 30, info2, br);
}

void Game::drawGameScreen()
{
	graphics::Brush br;
	br.texture = "Assets\\main\\background.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::Brush transitionBrush;
	transitionBrush.fill_opacity = sinf(graphics::getGlobalTime() / 2000.0f);
	transitionBrush.texture = "Assets\\main\\background_transition.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, transitionBrush);

	lives->draw();

	planeA->draw();

	if (!meteoriteList.empty()) {
		for (auto const& i : meteoriteList)
		{
			i->draw();
		}
	}

	if (!bulletList.empty()) {
		for (auto const& i : bulletList)
		{
			i->draw();
		}
	}

	if (planeA->isShooting())
	{
		bulletList.push_back(new Bullet(planeA->get_x(), planeA->get_y(), planeA->get_orientation(), planeA->get_dim_x(), planeA->get_dim_y()));
	}
}

void Game::drawGameoverScreen()
{
	graphics::Brush br;
	br.texture = "Assets\\main\\background.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::Brush transitionBrush;
	transitionBrush.fill_opacity = sinf(graphics::getGlobalTime() / 2000.0f);
	transitionBrush.texture = "Assets\\main\\background_transition.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, transitionBrush);

	graphics::setFont("Assets\\main\\font.ttf");
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 150);

	br.fill_color[0] = 0.3f + glow * 0.7f;
	br.fill_color[1] = 0.3f + glow * 0.7f;
	br.fill_color[2] = 0.3f + glow * 0.7f;
	char info[30];
	sprintf_s(info, "GAME    OVER");
	graphics::drawText((CANVAS_WIDTH / 2) - 350, CANVAS_HEIGHT / 2, 60, info, br);
}

void Game::updateGameoverScreen()
{
}