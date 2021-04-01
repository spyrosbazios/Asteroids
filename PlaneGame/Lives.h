#pragma once
#include "GameObj.h"

class Lives : public GameObj
{
public:
	virtual void draw() override;				//implementation of the GameObj interface
	virtual void update() override;
	bool gameoverCheck() { return gameover; }
	void dieOnce();
private:
	int hearts = 3;
	bool gameover = false;
};
