#include "Paddle.h"
//#include "RectF.h"



Paddle::Paddle(Vec2 pos_in, Color c_in)
	:
	pos(pos_in),
	c(c_in)
{
}

void Paddle::Draw(Graphics& gfx)
{
	gfx.DrawRect( RectF::FromCenter(pos, halfWidth, halfHeight) , c );
}

bool Paddle::DoPaddleCollision( Ball& ball, float dt ) 
{
	RectF padRect = RectF::FromCenter(pos, halfWidth, halfHeight);
	if (padRect.IsOverlappingWith(ball.GetRect()))
	{
		float mu = std::abs(ball.vel.x - velocity.x)*dt;
		if (ball.GetRect().right < padRect.left + mu)
		{
			ball.ReboundX();
			ball.pos.x = padRect.left - ball.radius + velocity.x*dt;
			if (ball.pos.x < ball.radius) { ball.pos.x = ball.radius;}
			if (velocity.x < ball.vel.x && velocity.x<0) { ball.vel.x = velocity.x; }
			
			return true;
		}
		else if (ball.GetRect().left > padRect.right - mu)
		{
			ball.ReboundX();
			ball.pos.x = padRect.right + ball.radius + velocity.x * dt;
			if (ball.pos.x > Graphics::ScreenWidth - ball.radius) { ball.pos.x = Graphics::ScreenWidth - ball.radius; }
			if (velocity.x > ball.vel.x && velocity.x > 0) { ball.vel.x = velocity.x; }
			return true;
		}
		ball.ReboundY();
		
	}
	return false;
}

void Paddle::Update(const Keyboard& kbd , float dt, const RectF& walls, const Ball& ball)
{
	float increment = speed * dt;
	velocity = Vec2(0, 0);
	if ( kbd.KeyIsPressed(VK_LEFT) )
	{
		if ( int(ball.pos.x) == int(ball.radius) 
			 && RectF::FromCenter(pos, halfWidth, halfHeight).left - increment < ball.radius * 2 )
		{
			pos.x = halfWidth + 2* ball.radius;
		}
		else if (RectF::FromCenter(pos, halfWidth, halfHeight).left < increment)
		{
			pos.x = halfWidth;
		}
		else
		{
			pos.x -= increment;
			velocity.x = -speed;
		}
	}
	else if ( kbd.KeyIsPressed(VK_RIGHT) )
	{
		if ( int(ball.pos.x) == int(Graphics::ScreenWidth-ball.radius ) 
			 && RectF::FromCenter(pos, halfWidth, halfHeight).right + increment > Graphics::ScreenWidth - ball.radius * 2 )
		{
			pos.x = Graphics::ScreenWidth - halfWidth - 2 * ball.radius ;
		}
		else if (RectF::FromCenter(pos, halfWidth, halfHeight).right > Graphics::ScreenWidth - increment)
		{
			pos.x = Graphics::ScreenWidth - halfWidth;
		}
		else
		{
			pos.x += increment;
			velocity.x = speed;
		}

	}
}


