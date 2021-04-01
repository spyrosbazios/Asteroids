#include "Meteorite.h"
#include "Flyable.h"
#include "Utils.h"
#include "Config.h"
Meteorite::Meteorite() :Flyable()
{
	isActive = true;
	//meteorite initialization
	//random speed
	fly_speed = 20.00f + rand0to1() * 70.00f;

	//set a random size
	size = 20.00f + rand0to1() * 250.00f;
	dim_x = size;
	dim_y = size;

	//pick a random side to spawn (destination side is the opposite)
	/*
		 ________(1)__________
		|                     |
	(4)	|				      | (2)
		|________(3)_________ |
	*/
	spawn_side = int(1 + (rand0to1() * 4));

	//pick a random point in that side
	if (spawn_side == 1)
	{
		pos_x = rand0to1() * CANVAS_WIDTH;
		pos_y = 0 - dim_x;
	}
	else if (spawn_side == 2) {
		pos_x = CANVAS_WIDTH + dim_y;
		pos_y = rand0to1() * CANVAS_HEIGHT;
	}
	else if (spawn_side == 3) {
		pos_x = rand0to1() * CANVAS_WIDTH;
		pos_y = CANVAS_HEIGHT + dim_y;
	}
	else {
		pos_x = 0 - dim_x;
		pos_y = rand0to1() * CANVAS_HEIGHT;
	}
}

Disk Meteorite::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = sqrt(2.0 * (size * size)) / 3;
	return disk;
}

void Meteorite::draw()
{
	graphics::resetPose();
	meteoriteBr.texture = "Assets\\main\\meteorite.png";
	meteoriteBr.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, dim_x, dim_y, meteoriteBr);
}

void Meteorite::update()
{
	if (spawn_side == 1)
	{
		pos_y += fly_speed * graphics::getDeltaTime() / 100.0f;
		if (pos_y > CANVAS_HEIGHT + dim_y) { isActive = false; }
	}
	else if (spawn_side == 2)
	{
		pos_x -= fly_speed * graphics::getDeltaTime() / 100.0f;
		if (pos_x < -dim_x) { isActive = false; }
	}
	else if (spawn_side == 3)
	{
		pos_y -= fly_speed * graphics::getDeltaTime() / 100.0f;
		if (pos_y < -dim_y) { isActive = false; }
	}
	else
	{
		pos_x += fly_speed * graphics::getDeltaTime() / 100.0f;
		if (pos_x > CANVAS_WIDTH + dim_x) { isActive = false; }
	}
}