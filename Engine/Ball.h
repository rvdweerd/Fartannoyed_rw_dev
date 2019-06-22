#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "RectF.h"
#include "Paddle.h"

class Ball {

public:
	Ball() = default;
	Ball(Vec2 in_pos, Vec2 in_vel);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool DoWallCollision(const RectF& walls);
	bool DoPaddleCollision(const Paddle& paddle);
	RectF GetRect() const;
	void ReboundX();
	void ReboundY();

private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;

};