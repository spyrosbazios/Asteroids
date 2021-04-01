#include <graphics.h>
#include "Game.h"
#include "Config.h"

void draw()
{
	Game* game = reinterpret_cast<Game*>(graphics::getUserData());
	game->draw();
}

void update(float dt)
{
	Game* game = reinterpret_cast<Game*>(graphics::getUserData());
	game->update();
}

int main()
{
	Game myGame;

	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Plane Game");
	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	graphics::setFullScreen(true);
	graphics::setFont("Assets\\font.ttf");

	graphics::setUserData(&myGame);
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	myGame.init();

	graphics::startMessageLoop();
	graphics::destroyWindow();
	return 0;
}