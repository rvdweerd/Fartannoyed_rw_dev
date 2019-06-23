#include "Brick.h"

Brick::Brick(const RectF rect_in, Color col_in)
	:
	rect(rect_in),
	c(col_in)
{
}

void Brick::Draw(Graphics& gfx) 
{
	if (!isDestroyed)
	{
		gfx.DrawRect(rect, c);
	}
}

bool Brick::DoBallCollision(Ball& ball)
{
	if ( !isDestroyed && rect.IsOverlappingWith(ball.GetRect()) )
	{
		ball.ReboundY();
		isDestroyed = true;
		return true;
	}
	return false;
}


