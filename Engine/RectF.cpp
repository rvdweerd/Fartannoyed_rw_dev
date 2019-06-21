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

RectF::RectF(Vec2 topleft, Vec2 bottomright)
	:
	RectF(topleft.y,topleft.x,bottomright.y,bottomright.x)
{
	assert( topleft.x < bottomright.x && topleft.y < bottomright.y);
}

RectF::RectF(Vec2 topleft, float width, float height)
	:
	RectF(topleft, topleft + Vec2(width,height) )
{
	assert(width > 0 && height > 0);
}
