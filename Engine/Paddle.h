#pragma once
#include "Vec2.h"
#include "Colors.h"
#include "Graphics.h"
#include "Keyboard.h"

class Paddle {
public:
	Paddle();
	Paddle(float x, float y);
	void Draw( Graphics& gfx);
	void Update(const Keyboard& kbd, RectF walls, float dt);
	RectF GetRect() const;
	static constexpr float speedX = 6.0f * 60;
	static constexpr float speedY = 6.0f * 60;
private:
	Vec2 pos;
	static constexpr Color bodyColor = Colors::LightGray;
	static constexpr Color rimColor = Colors::Red;

	static constexpr int width = 200;
	static constexpr int height = 15;
};