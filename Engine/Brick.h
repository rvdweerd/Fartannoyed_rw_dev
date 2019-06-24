#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick {
public:
	Brick() = default;
	Brick(const RectF rect_in, Color col_in);
	void Draw(Graphics& gfx, float brickPadding);
	bool DoBallCollision(Ball& ball, float dt);
	float CheckBallCollision(Ball& ball, float dt);
private:
	RectF rect;
	Color c;
	bool isDestroyed = false;

};
