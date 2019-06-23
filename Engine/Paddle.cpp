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

bool Paddle::DoPaddleCollision( Ball& ball ) 
{
	RectF padRect = RectF::FromCenter(pos, halfWidth, halfHeight);
	if (padRect.IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		return true;
	}
	return false;
}

void Paddle::Update(const Keyboard& kbd , float dt, const RectF& walls)
{
	float increment = speed * dt;
	if ( kbd.KeyIsPressed(VK_LEFT) )
	{
		if (RectF::FromCenter(pos, halfWidth, halfHeight).left >= increment)
		{
			pos.x -= increment;
		}
		else
		{
			pos.x = halfWidth;
		}
	}
	else if ( kbd.KeyIsPressed(VK_RIGHT) )
	{
		if (RectF::FromCenter(pos, halfWidth, halfHeight).right <= Graphics::ScreenWidth - increment)
		{
			pos.x += increment;
		}
		else
		{
			pos.x = Graphics::ScreenWidth - halfWidth;
		}

	}
}


