#pragma once
#include "Flyable.h"
#include "GameObj.h"
#include <graphics.h>

class Meteorite : public Flyable, GameObj
{
public:
	Meteorite();
	virtual void draw() override;				//implementation of the GameObj interface
	virtual void update() override;
	Disk getCollisionHull() const override;		//implementation of the flyable interface (logic : we have to track collisions for all flyable objects)

private:
	int spawn_side;
	graphics::Brush meteoriteBr;
	float size;
	float color = 1.00f;
};
