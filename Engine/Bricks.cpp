#include "Bricks.h"
#include "Colors.h" 


Bricks::Bricks(float x_in, float y_in, Color c)
	:
	pos(Vec2(x_in,y_in)),
	color(c)
{
}

void Bricks::Draw(Graphics& gfx)
{
	if (!isDestroyed)
	{
		gfx.DrawRect(GetRect(), color);
	}
}

RectF Bricks::GetRect() const
{
	return RectF(pos,width,height);
}

// NEW CLASS

RowOfBricks::RowOfBricks(float x_in, float y_in, int rowNumber_in, Color c)
	:
	rowNumber(rowNumber_in)
{
	for (int i = 0; i < nBricksPerRow; i++)
	{
		bricks[i].pos = Vec2(x_in + (Bricks::width+1)*i, float(y_in+(Bricks::height+1)*rowNumber));
		//Color c[3] = { Colors::Blue, Colors::White, Colors::Red };
		bricks[i].color = c;
	}
}
