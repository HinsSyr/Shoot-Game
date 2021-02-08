#ifndef HINTS_H
#define HINTS_H
///////////////////////////////////////////////////////////////////////
// Hints.h                 Hints object                              //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * - This package contains a Hints class that implements IHints
 *   interface.  It also contains a Factory class that creates instances
 *   of Hints.
 *
 * Required Files:
 * ---------------
 * IHints.h
 * Simple2D.h
 * 
 * Maintenance History
 * -------------------
 * ver 1.0 : 05 Dec 2020
 * - first release
 */

#include "IHints.h"
#include "../../Extern/Simple2D/Includes/Simple2D.h"
#include <fstream>
#include <iostream>


namespace Simple2D
{
	class Hints : public IHints
	{
	public:
		Hints();
		~Hints();

		virtual void drawHints() override;
		virtual void increScores(int score) override;
		virtual void increLives(int live) override;
		virtual int getLives() override;
		virtual void drawMenu() override;
		virtual int getNuclear() override;
		virtual void increNuclear(int Nuclear) override;
		virtual void saveScores() override;
		virtual void increLevel(int lv) override;

	private:
		void readScores();                                          //read scores from the file
		Simple2D::Font* pScores = nullptr;
		Simple2D::Font* pLives = nullptr;
		Simple2D::Font* pGameover = nullptr;
		Simple2D::Font* pGameoverHint = nullptr;
		Simple2D::Font* pGameTime = nullptr;
		Simple2D::Font* pNuclear = nullptr;
		Simple2D::Font* pHigestScore = nullptr;
		Simple2D::Font* pDifficulty = nullptr;
		int lives, scores, baseIndex,nuclearNumber,hightestScores,level;
		std::string strHighestScores;

	};


	class HintsFactory {
	public:
		static IHints* createHints()
		{
			Hints* rtn = new Hints();
			return rtn;
		}

	};
}

#endif