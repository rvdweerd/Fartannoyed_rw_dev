#include "Paddle.h"
//#include "RectF.h"



Paddle::Paddle(Vec2 pos_in, Color c_in)
	:
	pos(pos_in),
	c(c_in)
{
}

Paddle::Paddle(Vec2 pos_in, float halfWidth_in, float halfHeight_in, Color c_in)
	:
	pos(pos_in),
	c(c_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in)
{
}

void Paddle::Draw(Graphics& gfx)
{
	gfx.DrawRect( RectF::FromCenter(pos, halfWidth, halfHeight) , c );
}

bool Paddle::DoPaddleCollision( Ball& ball, float dt ) 
{
	if (!coolDown) 
	{
		RectF padRect = RectF::FromCenter(pos, halfWidth, halfHeight);
		if (padRect.IsOverlappingWith(ball.GetRect()))
		{
			float mu = std::abs(ball.vel.x - velocity.x) * dt;
			if (ball.GetRect().right <= padRect.left + mu)
			{
				if (ball.vel.x < 0)
				{
					ball.ReboundY( padRect.left , padRect.right );
				}
				else
				{
					ball.ReboundX();
				}
				ball.pos.x = padRect.left - ball.radius + velocity.x * dt;
				if (ball.pos.x < ball.radius) { ball.pos.x = ball.radius; }
				if (velocity.x < ball.vel.x && velocity.x < 0) { ball.vel.x = velocity.x; }
				//coolDown = true;
				return true;
			}
			else if (ball.GetRect().left >= padRect.right - mu)
			{
				if (ball.vel.x > 0)
				{
					ball.ReboundY(padRect.left, padRect.right);
				}
				else
				{
					ball.ReboundX();
				}
				ball.pos.x = padRect.right + ball.radius + velocity.x * dt;
				if (ball.pos.x > Graphics::ScreenWidth - ball.radius) { ball.pos.x = Graphics::ScreenWidth - ball.radius; }
				if (velocity.x > ball.vel.x && velocity.x > 0) { ball.vel.x = velocity.x; }

				//coolDown = true;
				return true;
			}

			mu = std::abs(ball.vel.y - velocity.y) * dt;
			if (ball.GetRect().bottom <= padRect.top + mu)
			{
				if (ball.vel.y < 0)
				{
					ball.ReboundX();
				}
				else
				{
					ball.ReboundY(padRect.left, padRect.right);
				}
				ball.pos.y = padRect.top - ball.radius + velocity.y * dt;
				if (ball.pos.y < ball.radius) { ball.pos.y = ball.radius; }
				if (velocity.y < ball.vel.y && velocity.y < 0) { ball.vel.y = velocity.y; }
				//coolDown = true;
				return true;
			}
			else if (ball.GetRect().top >= padRect.bottom - mu)
			{
				if (ball.vel.y > 0)
				{
					ball.ReboundX();
				}
				else
				{
					ball.ReboundY(padRect.left, padRect.right);
				}
				ball.pos.y = padRect.bottom + ball.radius + velocity.y * dt;
				if (ball.pos.y > Graphics::ScreenHeight - ball.radius) { ball.pos.y = Graphics::ScreenHeight - ball.radius; }
				if (velocity.y > ball.vel.y && velocity.y > 0) { ball.vel.y = velocity.y; }
				//coolDown = true;
				return true;
			}
		}
	}
	return false;
}

bool Paddle::SquashesLeft(const Ball& ball, const RectF& walls, Vec2 incrementVec)
{
	RectF padRect = RectF::FromCenter(pos, halfWidth, halfHeight);
	return
		(int(ball.pos.x) == int(ball.radius+walls.left)										// ball touches left wall
			&& ball.pos.y >= padRect.top && ball.pos.y <= padRect.bottom					// ball y-position is between paddle top and bottom
			&& padRect.left + incrementVec.x < ball.radius * 2+walls.left);					// if paddle moves left it would overlap with ball
}
bool Paddle::SquashesRight(const Ball& ball, const RectF& walls, Vec2 incrementVec)
{
	RectF padRect = RectF::FromCenter(pos, halfWidth, halfHeight);
	return
		(int(ball.pos.x) == int(walls.right - ball.radius)									// ball touches right wall		
			&& ball.pos.y >= padRect.top && ball.pos.y <= padRect.bottom					// ball y-position is between paddle top and bottom
			&& padRect.right + incrementVec.x > walls.right - ball.radius * 2);				// if paddle moves right it would overlap with ball
}
bool Paddle::SquashesTop(const Ball& ball, const RectF& walls, Vec2 incrementVec)
{
	RectF padRect = RectF::FromCenter(pos, halfWidth, halfHeight);
	return
		(int(ball.pos.y) == int(ball.radius + walls.top)									// ball touches top wall		
			&& ball.pos.x >= padRect.left && ball.pos.x <= padRect.right					// ball x-position is between paddle left and right
			&& padRect.top + incrementVec.y < ball.radius * 2 + walls.top);					// if paddle moves up it would overlap with ball
}
bool Paddle::SquashesBottom(const Ball& ball, const RectF& walls, Vec2 incrementVec)
{
	RectF padRect = RectF::FromCenter(pos, halfWidth, halfHeight);
	return
		(int(ball.pos.y) == int(walls.bottom - ball.radius)									// ball touches bottom wall		
			&& ball.pos.x >= padRect.left && ball.pos.x <= padRect.right					// ball x-position is between paddle left and right
			&& padRect.bottom + incrementVec.y > walls.bottom - ball.radius * 2);			// if paddle moves down it would overlap with ball
}

void Paddle::Update(int variant, const Keyboard& kbd , float dt, const RectF& walls, const Ball& ball)
{
	float increment = speed * dt;
	velocity = Vec2(0, 0);
		
	if ( (variant == 2 && kbd.KeyIsPressed( 0x41 )) ||
		  variant == 1 && kbd.KeyIsPressed(VK_LEFT) )
	{
		if ( SquashesLeft( ball , walls, Vec2(-increment,0.0f) ) )
		{
			pos.x = halfWidth + 2* ball.radius + walls.left;
		}
		else if (RectF::FromCenter(pos, halfWidth, halfHeight).left < increment + walls.left)
		{
			pos.x = halfWidth + walls.left;
		}
		else
		{
			pos.x -= increment;
			velocity.x = -speed;
		}
	}
	else if ( (variant == 2 && kbd.KeyIsPressed(0x44)) ||
		       variant == 1 && kbd.KeyIsPressed(VK_RIGHT) )
	{
		if ( SquashesRight( ball, walls, Vec2(increment,0.0f) ) )
		{
			pos.x = walls.right - halfWidth - 2 * ball.radius ;
		}
		else if (RectF::FromCenter(pos, halfWidth, halfHeight).right > walls.right - increment)
		{
			//pos.x = Graphics::ScreenWidth - halfWidth;
			pos.x = walls.right - halfWidth;
		}
		else
		{
			pos.x += increment;
			velocity.x = speed;
		}

	}
	
	if (	variant == 2 && kbd.KeyIsPressed(0x57) ||
			variant == 1 && kbd.KeyIsPressed(VK_UP) )
	{
		if ( SquashesTop(ball, walls, Vec2(0.0f,-increment) ) )
		{
			pos.y = 2 * ball.radius + halfHeight + walls.top;  //bug need to be fixed
		}
		else if (RectF::FromCenter(pos, halfWidth, halfHeight).top < walls.top +increment)
		{
			pos.y = halfHeight + walls.top;
		}
		else
		{
			pos.y -= increment;
			velocity.y = -speed;
		}
	}
	else if (	variant == 2 && kbd.KeyIsPressed(0x53) ||
				variant == 1 && kbd.KeyIsPressed(VK_DOWN))
	{
		if (SquashesBottom(ball, walls, Vec2(0.0f,increment)))
		{
			pos.y = walls.bottom - halfHeight - 2 * ball.radius;
		}
		else if (RectF::FromCenter(pos, halfWidth, halfHeight).bottom > walls.bottom - increment)
		{
			pos.y = walls.bottom - halfHeight;
		}
		else
		{
			pos.y += increment;
			velocity.y = speed;
		}

	}
	
}

void Paddle::ResetCoolDown()
{
	coolDown = false;
}


