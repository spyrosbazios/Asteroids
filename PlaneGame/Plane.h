#pragma once
#include "Flyable.h"
#include "Bullet.h"
#include "GameObj.h"
#include "Game.h"
#include "graphics.h"
#include <deque>
class Plane : public Flyable, GameObj
{
public:
	Plane();

	virtual void draw() override;			//implementation of the GameObj interface
	virtual void update() override;
	Disk getCollisionHull() const override;	//implementation of the flyable interface (logic : we have to track collisions for all flyable objects)

	bool isShooting() { return shootState; }
	bool isBlinking() { return explodeState; }		// explode state after plane crashes
	void explode();
private:
	bool shootState = false;
	bool a = true;
	float timeSaved = 0.00f;				//used to count the delay between firings in update()
	bool state = true;						//  >>                  >>                         >>
	float cooldown = 200.00f;

	bool explodeState = false;
	float explode_timeStamp;
	void checkExplode();
	std::string planeImage = "Assets\\main\\plane.png";
};
