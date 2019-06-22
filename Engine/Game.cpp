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
#include "Colors.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(rd()),
	ball( Vec2(700.0f,200.0f), Vec2(-3.0f,5.0f)*60.0f ),
	walls( Vec2(0.0f,0.0f) , gfx.ScreenWidth-1 , gfx.ScreenHeight-1 ),
	paddle(gfx.ScreenWidth/2,gfx.ScreenHeight-200.0f),
	//bricks( 100 ,100, Colors::Blue),
	//bricksRow(100.0f,200.0f,1),
	padSound({ L"Sounds\\arkpad.wav" } ),
	brickSound({ L"Sounds\\arkbrick.wav" })
{
	Color c[3] = { Colors::Blue, Colors::White, Colors::Red };
	for (int i = 0; i < nRows; i++)
	{
		//bricks[i] = Bricks(float(100 + 100 * i), 100.0f, Colors::Blue);
		bricksRow[i] = RowOfBricks(3.0f, float(100.0f), i, c[i % nRows] );
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
	//gfx.DrawRect(walls.left, walls.top, walls.right, walls.bottom, Colors::Red);
	const float dt = frametimer.Mark();
	
	paddle.Update(wnd.kbd, walls, dt);
	if (ball.DoPaddleCollision(paddle))
	{
		padSound.Play();
	}
	for (int i = 0; i < RowOfBricks::nBricksPerRow; i++)
	{
		//if (ball.DoBrickCollision(bricks[i]))
		//{
			//test.Play(rng);
		//}
		for (int j = 0; j < nRows; j++)
		{
			if (ball.DoBrickCollision(bricksRow[j].bricks[i]))
			{
				brickSound.Play(rng);
			}
		}
	}
	
	ball.Update(dt);
	
	if (ball.DoWallCollision(walls))
	{
		//test.Play();
	}
		
	
	/*
	if (ball.DoWallCollision(walls))
	{
		ball.Update(dt);
	}
	*/
	
}

void Game::ComposeFrame()
{
	paddle.Draw(gfx);
	ball.Draw(gfx);
	for (int i = 0; i < RowOfBricks::nBricksPerRow; i++)
	{
		//bricks[i].Draw(gfx);
		for (int j = 0; j < nRows; j++)
		{
			bricksRow[j].bricks[i].Draw(gfx);
		}
	}
	
}
