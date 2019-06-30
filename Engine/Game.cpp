/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Vec2.h"
#include "RectF.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	//walls( Vec2(0.0f,0.0f) , gfx.ScreenWidth , gfx.ScreenHeight )
	walls(Vec2(100.0f, 0.0f), 400, 600)
	
{
	for (Paddle& p : pad)
	{
		p = Paddle(Vec2(300.0f, gfx.ScreenHeight - 100.0f), Colors::White);
		//pad2(Vec2(10.0f, 300.0f), 10.0f, 60.0f, Colors::White)
	}
	
	for (Ball& b : ball)
	{
		b = Ball(Vec2(300.0f, walls.bottom - 50.0f), Vec2(2.0f, -0.0f) * 60.0f);
		b.ballEffect = ballEffect;
	}


	Color brickColors[4] = { Colors::Yellow , Colors::Blue, Colors::Green, Colors::Red };
	int i = 0;
	for (int x = 0; x < nBricksHorizontal; x++)
	{
		for (int y = 0; y < nBricksVertical; y++)
		{
			brick[i] = Brick( RectF( topleftBrickField + Vec2( x*brickWidth  , y*brickHeight ) , brickWidth, brickHeight), brickColors[y%4] );
			i++;
		}
	}
}

void Game::Go()
{
	
	gfx.BeginFrame();
	
	/*float elapsedTime = frametimer.Mark();
	while (elapsedTime  > 0.0f)
	{
		const float dt = std::min(0.01f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}*/
	const float dt = frametimer.Mark();

	UpdateModel(dt);
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (!GameOver)
	{
		
		//const float dt = frametimer.Mark();
		for (Ball& b : ball)
		{
			if (wnd.kbd.KeyIsPressed(0x24)) { b.vel *= 1.01f; }
			if (wnd.kbd.KeyIsPressed(0x23)) { b.vel *= 0.99f; }
			b.Update(dt);
			if (b.DoWallCollision(walls))
			{
				int count = 0;
				for (int i = 0; i < nBalls; i++)
				{
					if (ball[i].ballGameOver) { count++; }
				}
				if (count == nBalls)
				{
					GameOver = true;
				}
			}
			/*{
				pad.ResetCoolDown();
				pad2.ResetCoolDown();
			}*/

			int collisionIndex = -1;
			float minDist = brickWidth * brickWidth;
			for (int i = 0; i < nBricks; i++)
			{
				float brickDist = brick[i].CheckBallCollision(b, dt, brickWidth * brickWidth);
				if (brickDist < minDist - 1.0f)
				{
					minDist = brickDist;
					collisionIndex = i;
				}
			}

			if (collisionIndex >= 0)
			{
				brick[collisionIndex].DoBallCollision(b, dt);
				//pad.ResetCoolDown();
				//pad2.ResetCoolDown();
			}


			for (int i =0; i<nPads;i++)
			{
				pad[i].Update(i+1, wnd.kbd, dt, walls, b);
				pad[i].DoPaddleCollision(b, dt);
			}
			
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			GameOver = false;
			
			for (Ball& b : ball)
			{
				b.Reset();
			}
		}
	}
	
	
}

void Game::ComposeFrame()
{
	gfx.DrawRectLines(walls.GetPadded(1), Colors::White);

	for (int i = 0; i < nBricks; i++)
	{
		brick[i].Draw(gfx, brickPadding);
	}
	
	for (Paddle& p : pad)
	{
		p.Draw(gfx);
	}
	
	for (Ball& b : ball)
	{
		b.Draw(gfx);
	}
	if (GameOver)
	{
		SpriteCodex::DrawGameOver(Vec2(400.0f, 100.0f), gfx);
	}
}
