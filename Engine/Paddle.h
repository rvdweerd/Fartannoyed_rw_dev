#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"
#include "Vec2.h"
#include "Keyboard.h"

class Paddle {
public:
	Paddle() = default;
	Paddle( Vec2 pos_in, Color c_in);
	Paddle(Vec2 pos_in, float halfWidth_in, float halfHeight_in, Color c_in);
	void Draw(Graphics &gfx);
	bool DoPaddleCollision( Ball& ball , float dt);
	bool SquashesLeft(const Ball& ball, const RectF& walls, Vec2 incrementVec);
	bool SquashesRight(const Ball& ball, const RectF& walls, Vec2 incrementVec);
	bool SquashesTop(const Ball& ball, const RectF& walls, Vec2 incrementVec);
	bool SquashesBottom(const Ball& ball, const RectF& walls, Vec2 incrementVec);
	void Update(int variant, const Keyboard& kbd, float dt, const RectF& walls, const Ball& ball);
	Vec2 velocity = Vec2(0, 0);
	void ResetCoolDown();
private:
	Vec2 pos;//= Vec2( 300.0f , 500.0f );
	Color c;// = Colors::White;
	float speed = 4 * 60.0f;
	float halfWidth = 60.0f;
	float halfHeight =  10.0f;
	bool coolDown = false;
};