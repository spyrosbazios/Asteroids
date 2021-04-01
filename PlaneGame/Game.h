#pragma once
#include "Plane.h"
#include "Bullet.h"
#include "Meteorite.h"
#include "Lives.h"
#include <list>

class Plane;								//forward declaration

class Game
{
public:
	Game();
	void init();
	void draw();
	void update();

	std::list <Meteorite*> meteoriteList;
	std::list <Bullet*> bulletList;

private:
	Plane* planeA = nullptr;
	Lives* lives = nullptr;
	float timeSaved;						//used to count 500ms in spawMeteorite()
	bool state = true;

	void spawnMeteorite();
	void checkMeteorite();
	void checkBullet();
	void checkCollisionBullet();
	void checkCollisionPlane();
	void checkGameover();

	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_GAMEOVER } status_t;
	status_t status = STATUS_START;
	void updateStartScreen();
	void updateGameScreen();

	void drawStartScreen();
	void drawGameScreen();

	void drawGameoverScreen();
	void updateGameoverScreen();
};
