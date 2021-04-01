#include "Plane.h"
#include "Config.h"
#include <iostream>
Plane::Plane()
	:Flyable()

{
	orientation = 0.0f;
	dim_x = 75.0f;
	dim_y = 98.0f;
	pos_x = 1450.0f;
	pos_y = 600.0f;
	fly_speed = 35.0f;
}

Disk Plane::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 34.0f;
	return disk;
}

void Plane::explode()
{
	explode_timeStamp = graphics::getGlobalTime();
	explodeState = true;
}

void Plane::checkExplode()
{
	float current_time = graphics::getGlobalTime();
	if (current_time - explode_timeStamp > 100) {
		explodeState = false;
		planeImage = "Assets\\main\\plane.png";
	}
}

void Plane::draw()
{
	graphics::resetPose();
	graphics::Brush br;
	br.texture = planeImage;
	br.outline_opacity = 0.0f;
	graphics::setOrientation(orientation);
	graphics::drawRect(pos_x, pos_y, 50, 50, br);

	if (isBlinking())
		planeImage = "Assets\\main\\explosion.png";
}

void Plane::update()
{
	checkExplode();

	if (graphics::getKeyState(graphics::SCANCODE_UP))
	{
		orientation = 0.0f;

		if (pos_x - (dim_y / 4) > 0)                                                      //flight boundaries
			pos_y -= fly_speed * graphics::getDeltaTime() / 100.0f;
	}

	if (graphics::getKeyState(graphics::SCANCODE_DOWN))
	{
		orientation = 180.0f;

		if (pos_y + (dim_y / 4) < CANVAS_HEIGHT)
			pos_y += fly_speed * graphics::getDeltaTime() / 100.0f;
	}

	if (graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		orientation = 90.0f;

		if (pos_x - (dim_x / 4) > 0)
			pos_x -= fly_speed * graphics::getDeltaTime() / 100.0f;
	}

	if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		orientation = -90.0f;

		if (pos_x + (dim_x / 4) < CANVAS_WIDTH)
			pos_x += fly_speed * graphics::getDeltaTime() / 100.0f;
	}

	if (graphics::getKeyState(graphics::SCANCODE_M) && (graphics::getGlobalTime() - timeSaved) > cooldown) {
		timeSaved = graphics::getGlobalTime();
		shootState = true;
		graphics::playSound("Assets\\sounds\\shoot.wav", 1.0f, false);
	}
	else
	{
		shootState = false;
	}
}