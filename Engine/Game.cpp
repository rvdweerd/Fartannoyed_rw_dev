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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ball( Vec2(394.0f,270.0f), Vec2(0.0f,-0.0f)*60.0f ),
	walls( Vec2(0.0f,0.0f) , gfx.ScreenWidth , gfx.ScreenHeight ),
	pad( Vec2(200.0f, 450.0f) , Colors::White),
	pad2(Vec2(100.0f, 450.0f), Colors::White)
{
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
	float elapsedTime = frametimer.Mark();
	while (elapsedTime  > 0.0f)
	{
		const float dt = std::min(0.01f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	//const float dt = frametimer.Mark();
	ball.Update(dt);	
	if (ball.DoWallCollision(walls))
	{
		pad.ResetCoolDown();
		pad2.ResetCoolDown();
	}

	int collisionIndex = -1;
	float minDist=brickWidth*brickWidth;
	for (int i = 0; i < nBricks; i++)
	{
		float brickDist = brick[i].CheckBallCollision(ball, dt,brickWidth*brickWidth);
		if ( brickDist < minDist-1.0f)
		{
			minDist = brickDist;
			collisionIndex = i;
		}
	}

	if ( collisionIndex >= 0 )
	{
		brick[collisionIndex].DoBallCollision(ball, dt);
		pad.ResetCoolDown();
		pad2.ResetCoolDown();
	}
	


	pad.Update(1, wnd.kbd, dt, walls, ball);
	pad2.Update(2, wnd.kbd, dt, walls, ball);
	pad.DoPaddleCollision(ball,dt);
	pad2.DoPaddleCollision(ball, dt);

	

}

void Game::ComposeFrame()
{
	
	for (int i = 0; i < nBricks; i++)
	{
		brick[i].Draw(gfx, brickPadding);
	}
	
	pad.Draw(gfx);
	pad2.Draw(gfx);
	ball.Draw(gfx);
}
