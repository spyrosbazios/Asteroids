#include "Lives.h"
#include "graphics.h"
#include "Config.h"

void Lives::draw()
{
	graphics::Brush Br;
	Br.outline_opacity = 0.0f;
	Br.texture = "Assets\\main\\" + std::to_string(hearts) + ".png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 5, 174, 50, Br);
}

void Lives::update()
{
}

void Lives::dieOnce()
{
	if (hearts == 1)
		gameover = true;

	hearts -= 1;
}