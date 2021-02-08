///////////////////////////////////////////////////////////////////////
// Game.cpp -              Game entry                                //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////


#include "../Projects/VS_2019/Game.h"



namespace Simple2D
{
	Game::Game()
	{
		pWindow = Simple2D::CreateWindow("ShooterGame", 1024, 768);
		pback = Simple2D::BackgroundFactory::createBackground();
	}
	Game::~Game()
	{
		if(pWindow)
		Simple2D::DestroyWindow(pWindow);
		delete pback;
		pback = nullptr;
		pWindow = nullptr;

	}

	void Game::startGame()
	{
		fresh();
	}

	void Game::fresh()
	{
		while (!Simple2D::ShouldWindowClose(pWindow))
		{
			pback->drawBackground();
			Simple2D::RefreshWindowBuffer(pWindow);
			pback->movement();
			pback->collisionDetection();	
		}

	}

}

int main(int argc, char *argv[])
{
	Simple2D::Game* pGame = new Simple2D::Game();
	pGame->startGame();
	return 0;
}

