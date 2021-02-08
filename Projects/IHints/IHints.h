#ifndef IHINTS_H
#define IHINTS_H
///////////////////////////////////////////////////////////////////////
// IHints.h                Hint interface                            //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

namespace Simple2D
{

	class IHints
	{
	public:
		virtual ~IHints() {};                                  //Release derived and base class resources.
		virtual void drawHints() = 0;                          //Draw hints.
		virtual void increScores(int score) = 0;               //Increase/decrease the scores.
		virtual void increLives(int live) = 0;                 //Increase/decrease the lives.
		virtual int getLives() = 0;                            //Get remaining lives.
		virtual void drawMenu() = 0;                           //Draw the start menu.
		virtual int getNuclear() = 0;                          //Get the remainning nuclears.
		virtual void increNuclear(int Nuclear) = 0;            //Increase/decrease the nuclears.
		virtual void saveScores() = 0;                         //Save scores to file when game over.
		virtual void increLevel(int lv) = 0;                   //Increase/decrease the difficulty.
	};


}
#endif