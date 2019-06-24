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
	ball( Vec2(500.0f,450.0f), Vec2(3.0f,0.0f)*60.0f ),
	walls( Vec2(0.0f,0.0f) , gfx.ScreenWidth , gfx.ScreenHeight ),
	pad( Vec2(200.0f, 450.0f) , Colors::White)
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
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = frametimer.Mark();
	ball.Update(dt);	
	ball.DoWallCollision(walls);	

	for (int i = 0; i < nBricks; i++)
	{
		if (brick[i].DoBallCollision(ball))
		{
			break;
		}
	}

	pad.Update(wnd.kbd, dt, walls, ball);
	pad.DoPaddleCollision(ball,dt);

	

}

void Game::ComposeFrame()
{
	
	for (int i = 0; i < nBricks; i++)
	{
		brick[i].Draw(gfx, brickPadding);
	}
	
	pad.Draw(gfx);
	ball.Draw(gfx);
}
