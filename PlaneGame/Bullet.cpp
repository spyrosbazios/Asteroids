#include "Bullet.h"
#include <graphics.h>
#include "Config.h"

Bullet::Bullet(float plane_x, float  plane_y, float plane_orientation, float plane_dim_x, float plane_dim_y)
{
	isActive = true;
	fly_speed = 100.0f;
	if (plane_orientation == 0.0f)
	{
		pos_x = plane_x;
		pos_y = plane_y - plane_dim_y / 2;
		orientation = plane_orientation;
	}
	else if (plane_orientation == -90.0f)
	{
		pos_x = plane_x + plane_dim_x / 2;
		pos_y = plane_y;
		orientation = plane_orientation;
	}
	else if (plane_orientation == 90.0f)
	{
		pos_x = plane_x - plane_dim_x / 2;
		pos_y = plane_y;
		orientation = plane_orientation;
	}
	else  //(plane_orientation == 180.0f)
	{
		pos_x = plane_x;
		pos_y = plane_y + plane_dim_y / 2;
		orientation = plane_orientation;
	}
}

void Bullet::draw()
{
	graphics::resetPose();
	graphics::Brush br;
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 25);
	br.fill_opacity = glow * 1.0f;
	br.texture = "Assets\\main\\laserBlue.png";
	br.outline_opacity = 0.0f;
	graphics::setOrientation(orientation);
	graphics::drawRect(pos_x, pos_y, 13, 54, br);
}

void Bullet::update()
{
	if (orientation == 0.0f)
	{
		pos_y -= fly_speed * graphics::getDeltaTime() / 100.0f;
	}
	else if (orientation == -90.0f)
	{
		pos_x += fly_speed * graphics::getDeltaTime() / 100.0f;
	}
	else if (orientation == 90.0f)
	{
		pos_x -= fly_speed * graphics::getDeltaTime() / 100.0f;
	}
	else
	{
		pos_y += fly_speed * graphics::getDeltaTime() / 100.0f;
	}

	if (pos_x > CANVAS_WIDTH || pos_x < 0 || pos_y < 0 || pos_y > CANVAS_HEIGHT)
	{
		isActive = false;
	}
}

Disk Bullet::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 30.0f;
	return disk;
}