///////////////////////////////////////////////////////////////////////
// Meteorite.cpp           Meteorite object                          //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

#include "Meteorite.h"



namespace Simple2D
{
	Meteorite::Meteorite(int &tp,int &minSp, int &maxSp, float &sps) : maxHits(tp),minSpeed(minSp),maxSpeed(maxSp),speedScale(sps)
	{
		pImageMeteorite = Simple2D::CreateImage("../../Content/Textures/Meteorite_"+std::to_string(tp)+".png");
		countHits = 0;
		getSize();
		randomPos();
	}

	Meteorite::~Meteorite()
	{
		if(pImageMeteorite)
		Simple2D::DestroyImage(pImageMeteorite);
		free(pWidth);
		free(pHeight);
		pWidth = nullptr;
		pHeight = nullptr;
		pImageMeteorite = nullptr;
	}

	void Meteorite::drawMeteorite()
	{
		if(pImageMeteorite)
		Simple2D::DrawImage(pImageMeteorite, posX , posY, rotate, scale);
	}

	float Meteorite::getPosx()
	{
		return posX;
	}

	float Meteorite::getPosy()
	{
		return posY;
	}

	void Meteorite::movement()
	{
		posX = posX - speed*speedScale;
		if (goUp)
			posY = posY + speedY * 0.2 * speedScale;
		else
			posY = posY - speedY * 0.2 * speedScale;
	}

	int Meteorite::getRandomNumber(int a, int b)
	{
		return (rand() % (b - a + 1)) + a;
	}

	int Meteorite::getDesx()
	{
		return desX;

	}

	int Meteorite::getDesy()
	{
		return desY;
	}
	
	void Meteorite::randomPos()
	{
		speed = getRandomNumber(minSpeed, maxSpeed);
		speedY = speed / 2;
		scale = 1;
		rotate = getRandomNumber(-180,180);
		posY = getRandomNumber(-256, 1024);

		if (posY > 896 || posY < -128) posX = getRandomNumber(768, 1280);
		else
		{
			posX = getRandomNumber(1152, 1280);
		}

		desX = -128;
		desY = getRandomNumber(100, 700);
	
		if (posY < desY)
			goUp = true;
		else
			goUp = false;	
	}

	void Meteorite::getSize()
	{
		pWidth = (int*)malloc(sizeof(int));
		pHeight = (int*)malloc(sizeof(int));
		if(pImageMeteorite)
		Simple2D::GetImageSize(pImageMeteorite, pWidth, pHeight);
	}

	int Meteorite::getHeight()
	{
		return *pHeight;
	}

	int Meteorite::getWidth()
	{
		return *pWidth;
	}

	void Meteorite::increHitCount(int count)
	{
		countHits += count;
	}

	int Meteorite::getHitCount()
	{
		return countHits;
	}

	int Meteorite::getMaxHit()
	{
		return maxHits;
	}

	void Meteorite::increMaxHit(int count)
	{
		maxHits += count;
	}

	void Meteorite::setSpeed(int &minSp, int &maxSp)
	{
		minSpeed = minSp;
		maxSpeed = maxSp;
		if (speed > maxSp) speed = maxSp;
		if (speed < minSp) speed = minSp;
		speedY = speed / 2;
	}

	int Meteorite::getMaxSpeed()
	{
		return maxSpeed;
	}

	int Meteorite::getMinSpeed()
	{
		return minSpeed;
	}

	void Meteorite::setSpeedScale(float &scale)
	{
		speedScale = scale;
	}

}

#ifdef TEST_METEORITE
int main()
{



	return 0;
}
#endif

