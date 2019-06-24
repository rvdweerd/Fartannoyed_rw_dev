#include "Brick.h"

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
	{
		isDestroyed = true;
		float mu = std::abs(ball.vel.x) * dt;
		if (ball.GetRect().right < rect.left + mu)
		{
			ball.ReboundX();
			ball.pos.x = max( ball.radius, rect.left - ball.radius );
			return true;
		}
		else if (ball.GetRect().left > rect.right - mu)
		{
			ball.ReboundX();
			ball.pos.x = min( rect.right + ball.radius, Graphics::ScreenWidth - ball.radius);
			return true;
		}
		ball.ReboundY();
		ball.pos.y += ball.vel.y * dt;
		return true;
	}
	return false;
}

float Brick::CheckBallCollision(Ball& ball, float dt)
{
	if (!isDestroyed && rect.IsOverlappingWith(ball.GetRect()))
	{
		Vec2 dist = ball.pos - rect.GetCenter();
		return dist.GetLengthSq();
	}
	else
	{
		return 100000.0f;
	}
}


