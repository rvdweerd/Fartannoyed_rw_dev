#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(Vec2 in_pos, Vec2 in_vel)
	:
	pos(in_pos),
	vel(in_vel)
{
}

void Ball::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{
	pos += vel*dt;
}

bool Ball::DoWallCollision(const RectF& walls)
{
	bool collided=false;
	const RectF balRect = GetRect();
	//RectF ballBox(pos_tmp.y - radius, pos_tmp.x - radius, pos_tmp.y + radius, pos_tmp.x + radius);
	//if (!ballBox.IsOverlappingWith( walls.Crop(14.0f) ) )
	
	if ( balRect.right >= walls.right ) 
	{
		//pos.x += walls.right - balRect.right;
		pos.x = walls.right - radius;
		ReboundX();
		collided = true;
	}
	else if ( balRect.left <= walls.left) 
	{
		//pos.x += walls.left - balRect.left;
		pos.x = walls.left + radius;
		ReboundX();
		collided = true;
	}
	if ( balRect.top <= walls.top )
	{
		//pos.y += walls.top - balRect.top;
		pos.y = walls.top + radius;
		ReboundY();
		collided = true;
	}
	else if ( balRect.bottom >= walls.bottom)
	{
		//pos.y += walls.bottom - balRect.bottom;
		pos.y = walls.bottom - radius;
		ReboundY();
		collided = true;
	}
	return collided;
}

bool Ball::DoPaddleCollision(const Paddle& paddle)
{
	bool collided = false;
	const RectF balRect = GetRect();
	const RectF paddleRect = paddle.GetRect();
	if (balRect.IsOverlappingWith(paddleRect))
	{
		if (balRect.IsWithinVerticals(paddleRect) && vel.y > 0) 
		{
			pos.y = paddleRect.top-radius;
			if (Paddle::speedY > std::abs(vel.y))
			{
				vel.y *= (Paddle::speedY / std::abs(vel.y)) * 1.05f;
			}
			ReboundY();
		}
		else if (balRect.IsWithinVerticals(paddleRect) && vel.y < 0)
		{
			pos.y = paddleRect.bottom+radius;
			if (Paddle::speedY > std::abs(vel.y))
			{
				vel.y *= (Paddle::speedY / std::abs(vel.y)) * 1.05f;
			}
			ReboundY();
		}
		else if (balRect.IsWithinHorizontals(paddleRect) && vel.x>0)
		{
			pos.x = paddleRect.left - radius;
			if (Paddle::speedX > std::abs(vel.x))
			{
				vel.x *= (Paddle::speedX / std::abs(vel.x)) * 1.05f;
			}
			ReboundX();
		}
		else if (balRect.IsWithinHorizontals(paddleRect) && vel.x < 0)
		{
			pos.x = paddleRect.right + radius;
			if (Paddle::speedX > std::abs(vel.x))
			{
				vel.x *= (Paddle::speedX / std::abs(vel.x)) * 1.05f;
			}
			ReboundX();
		}
		else
		{
			ReboundX();
			ReboundY();
		}
		collided = true;
	}
	return collided;
}

bool Ball::DoBrickCollision(Bricks& brick)
{
	RectF ballRect = GetRect();
	RectF brickRect = brick.GetRect();
	bool collided = false;
	if (!brick.isDestroyed && ballRect.IsOverlappingWith(brickRect))
	{
		brick.isDestroyed = true;
		//ReboundX();
		ReboundY();
		collided = true;
	}

	return collided;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}
