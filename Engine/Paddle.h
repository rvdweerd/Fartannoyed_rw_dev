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
	void Draw(Graphics &gfx);
	bool DoPaddleCollision( Ball& ball , float dt);
	void Update(const Keyboard& kbd, float dt, const RectF& walls, const Ball& ball);
	Vec2 velocity = Vec2(0, 0);
private:
	Vec2 pos;//= Vec2( 300.0f , 500.0f );
	Color c;// = Colors::White;
	float speed = 2 * 60.0f;
	float halfWidth = 60.0f;
	float halfHeight =  40.0f;
};