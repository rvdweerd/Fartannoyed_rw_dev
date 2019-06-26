#include "Brick.h"
#include "Game.h"
#include <assert.h>

Brick::Brick(const RectF rect_in, Color col_in)
	:
	rect(rect_in),
	c(col_in)
{
}

void Brick::Draw(Graphics& gfx, float brickPadding)
{
	if (!isDestroyed)
	{
		gfx.DrawRect( rect.GetPadded(brickPadding) , c);
	}
}

bool Brick::DoBallCollision(Ball& ball, float dt)
{
	//if ( !isDestroyed && rect.IsOverlappingWith(ball.GetRect()) )
	assert(!isDestroyed && rect.IsOverlappingWith(ball.GetRect()));
	{
		isDestroyed = true;
		float mu = std::abs(ball.vel.x) * dt;
		if (ball.GetRect().right < rect.left + mu)
		{
			if (ball.vel.x < 0)
			{
				ball.ReboundY();
			}
			else
			{
				ball.ReboundX();
			}
			ball.pos.x = max( ball.radius, rect.left - ball.radius );
			return true;
		}
		else if (ball.GetRect().left > rect.right - mu)
		{
			if (ball.vel.x > 0)
			{
				ball.ReboundY();
			}
			else
			{
				ball.ReboundX();
			}
			ball.pos.x = min( rect.right + ball.radius, Graphics::ScreenWidth - ball.radius);
			return true;
		}
		ball.ReboundY();
		ball.pos.y += ball.vel.y * dt;
		return true;
	}
	return false;
}

float Brick::CheckBallCollision(Ball& ball, float dt, float b2)
{
	if (!isDestroyed && rect.IsOverlappingWith(ball.GetRect()))
	{
		//Vec2 dist = ball.pos - rect.GetCenter();
		//return dist.GetLengthSq();
		return (ball.pos - rect.GetCenter()).GetLengthSq();
	}
	else
	{
		return b2;// 100000.0f;
	}
}


