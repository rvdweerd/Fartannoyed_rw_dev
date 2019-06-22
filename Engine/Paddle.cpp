#include "Paddle.h"
#include "RectF.h"

Paddle::Paddle()
	:
	pos(Vec2(0.0f, 0.0f))
{
}

Paddle::Paddle(float x, float y)
	:
	pos(Vec2(x, y))
{
}

void Paddle::Draw( Graphics& gfx)
{
	gfx.DrawRect(RectF(pos, float(width), float(height)), rimColor);
	gfx.DrawRect(RectF(pos+Vec2(15,0), float(width-30), float(height)), bodyColor);
}

void Paddle::Update(const Keyboard& kbd, RectF walls, float dt)
{
	//const RectF paddleRect = GetRect();
	if (kbd.KeyIsPressed(VK_RIGHT)) 
	{ 
		pos.x += speed * dt;
		if ((pos.x + width) >= walls.right)
		{
			pos.x = walls.right - width;
		}
	}
	 if (kbd.KeyIsPressed(VK_LEFT)) 
	{ 
		pos.x -= speed * dt;
		if (pos.x <= walls.left)
		{
			pos.x = walls.left;
		}
	}
	 if (kbd.KeyIsPressed(VK_UP)) 
	{ 
		pos.y -= speed / 2 * dt;
		if (pos.y  <= walls.top)
		{
			pos.y = walls.top;
		}
	}
	 if (kbd.KeyIsPressed(VK_DOWN)) 
	{ 
		 pos.y += speed / 2 * dt; 
		 if (pos.y + height  >= walls.bottom)
		{
			 pos.y = walls.bottom - height;
		}
	}
}

RectF Paddle::GetRect() const
{
	return RectF(pos, width, height);
}

