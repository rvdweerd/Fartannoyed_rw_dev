#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "RectF.h"

class Ball {

public:
	Ball() = default;
	Ball(Vec2 in_pos, Vec2 in_vel);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool DoWallCollision(const RectF& walls);
	RectF GetRect() const;
	void ReboundX();
	void ReboundY();
	void ReboundY(float padLeft, float padRight);
	void Reset();

public:
	bool ballGameOver = false;
	float ballEffect = 0;
	Vec2 pos;
	Vec2 vel;
public:
	static constexpr float radius = 7.0f;
};