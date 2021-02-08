///////////////////////////////////////////////////////////////////////
// Game.h -                Game entry                                //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * - This package contains a Game class 
 *
 * Required Files:
 * ---------------
 * Background.h
 *
 * Maintenance History
 * -------------------
 * ver 1.0 : 05 Dec 2020
 * - first release
 */
#include "iostream"
#include "../IBackground/Background.h"

namespace Simple2D
{
	class Game
	{

	public:
		Game();
		~Game();
		void startGame();                      //start the game
	private:
		void fresh();                          //fresh the screen
		Simple2D::Window* pWindow = nullptr;
		Simple2D::IBackground* pback = nullptr;
		
	};
}
