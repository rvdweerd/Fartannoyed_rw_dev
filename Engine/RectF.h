#pragma once
#include "Vec2.h"

class RectF {
public: 
	RectF();
	RectF(float top_in, float left_in, float bottom_in, float right_in);
	RectF(Vec2 topleft, Vec2 bottomright);
	RectF(Vec2 topleft, float width, float height);
private:
	float left;
	float right;
	float top;
	float bottom;
};