///////////////////////////////////////////////////////////////////////
// Upgrade.cpp -           Upgrade object                            //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

#include "Upgrade.h"


namespace Simple2D
{
	Upgrade::Upgrade(int &sp, float &sps) : speedScale(sps),speed(sp)
	{
		pImageUpgrade = Simple2D::CreateImage("../../Content/Textures/Upgrade.png");
		getSize();
		randomPos();
	}

	Upgrade::~Upgrade()
	{
		if(pImageUpgrade)
		Simple2D::DestroyImage(pImageUpgrade);
		free(pWidth);
		free(pHeight);
		pImageUpgrade = nullptr;
		pWidth = nullptr;
		pHeight = nullptr;
	}

	void Upgrade::drawUpgrade()
	{
		if (pImageUpgrade)
			Simple2D::DrawImage(pImageUpgrade, posX, posY, 0, 1);
	}

	void Upgrade::randomPos()
	{
		posX = getRandomNumber(1050,1100);
		posY = getRandomNumber(150, 650);
		//move from right to left center
		if (posY >400)
		{
			speedY = speed;
		}
		else
		{
			speedY = -speed;
		}
	}

	void Upgrade::movement()
	{
		posX = posX - speed * speedScale;
		posY = posY - speedY * 0.3 * speedScale;
	}

	int Upgrade::getRandomNumber(int a, int b)
	{
		return (rand() % (b - a + 1)) + a;
	}

	void Upgrade::getSize()
	{
		pWidth = (int*)malloc(sizeof(int));
		pHeight = (int*)malloc(sizeof(int));
		if(pImageUpgrade)
		Simple2D::GetImageSize(pImageUpgrade, pWidth, pHeight);
	}

	int Upgrade::getHeight()
	{
		return *pHeight;
	}

	int Upgrade::getWidth()
	{
		return *pWidth;
	}

	void Upgrade::setSpeed(int& sp)
	{
		speed = sp;
		if (speedY > 0)
			speedY = speed;
		else
			speedY =- speed;
	}

	void Upgrade::setSpeedScale(float& sps)
	{
		speedScale = sps;
	}

	float Upgrade::getPosx()
	{
		return posX;
	}

	float Upgrade::getPosy()
	{
		return posY;
	}
	
}

#ifdef TEST_UPGRADE
int main()
{



	return 0;
}
#endif

