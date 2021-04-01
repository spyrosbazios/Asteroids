#pragma once
#include "Utils.h"
class Flyable
{
public:
	virtual Disk getCollisionHull() const = 0;

	Flyable();
	Flyable(float dimention_x, float dimention_y, float x, float y);

	float get_orientation();
	void set_orientation(float orient);

	void set_x(float x);
	void set_y(float y);
	void set_dim_x(float x);
	void set_dim_y(float y);

	void set_speed(float speed);
	float get_speed();
	float get_x() const;
	float get_y() const;

	float get_dim_x();
	float get_dim_y();

	bool getState() { return isActive; }
	void setState(bool state) { isActive = state; }
private:

protected:
	bool isActive = true;

	char id;
	float pos_x;							//position
	float pos_y;
	float dim_x;							//dimentions
	float dim_y;
	float orientation;
	float fly_speed = 20;
};
