#pragma once
#include "Utils.h"

class GameObj								// Each gameObj (plane, bullet) has to implement a draw() and update() function.
{
public:

	virtual void draw() = 0;
	virtual void update() = 0;
};
