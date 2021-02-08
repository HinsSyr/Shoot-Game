///////////////////////////////////////////////////////////////////////
// Hints.cpp               Hints object                              //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

#include "Hints.h"



namespace Simple2D
{
	Hints::Hints()
	{
		pScores = Simple2D::CreateFont("../../Content/Fonts/AGENCYB.TTF",30);
		pLives = Simple2D::CreateFont("../../Content/Fonts/AGENCYB.TTF", 30);
		pGameover = Simple2D::CreateFont("../../Content/Fonts/AGENCYB.TTF", 150);
		pGameoverHint = Simple2D::CreateFont("../../Content/Fonts/AGENCYB.TTF", 40);
		pNuclear = Simple2D::CreateFont("../../Content/Fonts/AGENCYB.TTF", 30);
		pHigestScore = Simple2D::CreateFont("../../Content/Fonts/AGENCYB.TTF", 30);
		pDifficulty = Simple2D::CreateFont("../../Content/Fonts/AGENCYB.TTF", 30);
		scores = 0;
		lives = 3;
		nuclearNumber = 3;
		baseIndex = 1;
		level = 0;
		readScores();
	}

	Hints::~Hints()
	{
		if (pScores)
			Simple2D::DestroyFont(pScores);
		if (pLives)
			Simple2D::DestroyFont(pLives);
		if (pGameover)
			Simple2D::DestroyFont(pGameover);
		if (pGameoverHint)
			Simple2D::DestroyFont(pGameoverHint);
		if (pNuclear)
			Simple2D::DestroyFont(pNuclear);
		if (pHigestScore)
			Simple2D::DestroyFont(pHigestScore);
		if (pDifficulty)
			Simple2D::DestroyFont(pDifficulty);
		pDifficulty = nullptr;
		pHigestScore = nullptr;
		pNuclear = nullptr;
		pScores = nullptr;
		pLives = nullptr;
		pGameoverHint = nullptr;
		pGameTime = nullptr;
	}

	void Hints::drawHints()
	{
		if (pScores)
			Simple2D::DrawString(pScores, "Scores: " + std::to_string(scores), 512, 720, 0, 1);
		if (pLives)
			Simple2D::DrawString(pLives, "Lives x" + std::to_string(lives), 256, 720, 0, 1);
		if (pHigestScore)
			Simple2D::DrawString(pHigestScore, "Highest Scores: " + std::to_string(hightestScores), 768, 720, 0, 1);
		if (pNuclear)
			Simple2D::DrawString(pNuclear, "Nucler x" + std::to_string(nuclearNumber), 256, 50, 0, 1);
		if (pDifficulty)
			Simple2D::DrawString(pDifficulty, "Difficulty: " + std::to_string(level), 768, 50, 0, 1);

		if (lives == 0)
		{
			if (pGameover)
				Simple2D::DrawString(pGameover, "GAME OVER!", 512, 384, 0, 1);
			if (pGameoverHint)
				Simple2D::DrawString(pGameoverHint, "Press ECS back to menu", 512, 184, 0, 1);
		}

	}

	void Hints::drawMenu()
	{
		if (pGameover)
			Simple2D::DrawString(pGameover, "STARWAR 2020", 512, 384, 0, 1);
		if (pGameoverHint)
			Simple2D::DrawString(pGameoverHint, "Press SPACE to start game", 512, 184, 0, 1);
	}

	void Hints::increScores(int score)
	{
		scores += score;
		//when player gets 2000 scores, he will get one more live.
		if (scores > baseIndex*2000 )
		{
			lives++;
			baseIndex++;
		}
		if (scores > hightestScores)
		{
			hightestScores = scores;
		}
	}

	void Hints::increLives(int live)
	{
		lives += live;
		if (lives <= 0)
			lives = 0;
	}

	 int Hints::getLives()
	{
		 return lives;
	}

	 int Hints::getNuclear()
	 {
		 return nuclearNumber;
	 }

	 void Hints::increNuclear(int Nuclear)
	 {
		 nuclearNumber += Nuclear;
		 if (nuclearNumber <= 0)
			 nuclearNumber = 0;
	 }

	 void Hints::readScores()
	 {
		 std::ifstream readFile("../../Content/HightestScores.txt");
		 readFile >> strHighestScores;
		 readFile.close();
		 hightestScores = std::stoi(strHighestScores);
	 }

	 void Hints::saveScores()
	 {
		 std::ofstream saveFile("../../Content/HightestScores.txt");
		 saveFile << hightestScores;
		 saveFile.close();
	 }

	 void Hints::increLevel(int lv)
	 {
		 level += lv;
		 if (level >= 5) level = 5;
	 }

}

#ifdef TEST_HINTS
int main()
{



	return 0;
}
#endif

