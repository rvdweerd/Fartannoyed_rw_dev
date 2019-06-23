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
	const RectF ballRect = GetRect();
	
	if ( ballRect.right > walls.right ) 
	{
		pos.x = walls.right - radius;
		ReboundX();
		collided = true;
	}
	else if ( ballRect.left < walls.left) 
	{
		pos.x = walls.left + radius;
		ReboundX();
		collided = true;
	}
	else if ( ballRect.top < walls.top )
	{
		pos.y = walls.top + radius;
		ReboundY();
		collided = true;
	}
	else if ( ballRect.bottom > walls.bottom)
	{
		pos.y = walls.bottom - radius;
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
