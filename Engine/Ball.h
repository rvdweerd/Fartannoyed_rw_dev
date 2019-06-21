#pragma once
#include "Vec2.h"
#include "Graphics.h"

class Ball {

public:
	Ball() = default;
	Ball(Vec2 in_pos, Vec2 in_vel);
	void Draw(Graphics& gfx) const;
	void Update(float dt);

private:
	Vec2 pos;
	Vec2 vel;

};