#include "RectF.h"
#include <assert.h>

RectF::RectF()
	:
	RectF(0.0f,0.0f,0.0f,0.0f)
{
	//*this = RectF(0.0f, 0.0f, 0.0f, 0.0f);
}

RectF::RectF(float top_in, float left_in, float bottom_in, float right_in)
	:
	top(top_in),
	left(left_in),
	bottom(bottom_in),
	right(right_in)
{
	assert( top <= bottom && right >= left);
}

RectF::RectF(const Vec2& topleft, const Vec2& bottomright)
	:
	RectF(topleft.y,topleft.x,bottomright.y,bottomright.x)
{
	assert( topleft.x < bottomright.x && topleft.y < bottomright.y);
}

RectF::RectF(const Vec2& topleft, float width, float height)
	:
	RectF(topleft, topleft + Vec2(width,height) )
{
	assert(width > 0 && height > 0);
}

RectF RectF::FromCenter(const Vec2& center, float halfWidth, float halfHeight)
{
	Vec2 boxVec(halfWidth,halfHeight);
	return RectF(center - boxVec , center + boxVec);
}

bool RectF::IsOverlappingWith(const RectF& other) const
{
	return 
		( top  <= other.bottom && bottom >= other.top  &&
		  left <= other.right  && right  >= other.left );
}

RectF RectF::Crop(const float clipSize) const
{
	return RectF(top + clipSize, left + clipSize, bottom-clipSize, right-clipSize);
}

RectF RectF::GetPadded(float padding)
{
	return RectF( top + padding, left + padding, bottom - padding, right - padding);
}

