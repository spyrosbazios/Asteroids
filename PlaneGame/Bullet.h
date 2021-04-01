#pragma once
#include "Flyable.h"
#include "GameObj.h"
class Bullet : public Flyable, GameObj
{
public:
	Bullet(float planeX, float  planeY, float planeOrientation, float planeDimX, float planeDimY);
	~Bullet();
	void draw() override;						//implementation of the GameObj interface
	void update() override;
	Disk getCollisionHull() const override;		//implementation of the flyable interface (logic : we have to track collisions for all flyable objects)

private:
};
