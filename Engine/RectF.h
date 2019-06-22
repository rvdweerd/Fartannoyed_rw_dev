#pragma once
#include "Vec2.h"

class RectF {
public: 
	RectF();
	RectF(float top_in, float left_in, float bottom_in, float right_in);
	RectF(const Vec2& topleft, const Vec2& bottomright);
	RectF(const Vec2& topleft, float width, float height);
	static RectF FromCenter(const Vec2& center, float halfWidth, float halfHeight);
	bool IsOverlappingWith(const RectF& other) const;
	bool IsWithinVerticals(const RectF& other) const;
	bool IsWithinHorizontals(const RectF& other) const;
	RectF Crop(const float clipSize) const;
public:
	float left;
	float right;
	float top;
	float bottom;
};