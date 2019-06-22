#pragma once
#include "Vec2.h"
#include "Colors.h"
#include "Graphics.h"

class Bricks {
public:
	Bricks() = default;
	Bricks(float x_in, float y_in, Color c);
	void Draw(Graphics& gfx);
	RectF GetRect() const;
	bool isDestroyed = false;
public:
	Vec2 pos;
	static constexpr int width = 87;
	static constexpr int height = 20;
	Color color;
	
};

class RowOfBricks {
public:
	RowOfBricks() = default;
	RowOfBricks(float x_in, float y_in, int rowNumber_in, Color c);
public:
	static constexpr int nBricksPerRow = 9;
	Bricks bricks[nBricksPerRow];
	int rowNumber;
};