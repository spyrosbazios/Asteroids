#pragma once
#include "Flyable.h"

Flyable::Flyable() {}

Flyable::Flyable(float dimention_x, float dimention_y, float x, float y)
{
	pos_x = x;
	pos_y = y;
	dim_x = dimention_x;
	dim_y = dimention_y;
}

float Flyable::get_orientation()
{
	return orientation;
}

void Flyable::set_orientation(float orient)
{
	orientation = orient;
}

void Flyable::set_x(float x)
{
	pos_x = x;
}

void Flyable::set_y(float y)
{
	pos_y = y;
}

void Flyable::set_dim_x(float x)
{
	dim_x = x;
}

void Flyable::set_dim_y(float y)
{
	dim_y = y;
}

void Flyable::set_speed(float speed)
{
	fly_speed = speed;
}

float Flyable::get_speed()
{
	return fly_speed;
}

float Flyable::get_x() const
{
	return pos_x;
}

float Flyable::get_y() const
{
	return pos_y;
}

float Flyable::get_dim_x()
{
	return dim_x;
}

float Flyable::get_dim_y()
{
	return dim_y;
}