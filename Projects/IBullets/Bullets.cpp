///////////////////////////////////////////////////////////////////////
// Bullets.cpp             Bullets object                            //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

#include "Bullets.h"

namespace Simple2D
{
	Bullets::Bullets(float& shipPosx, float& shipPosy, int& sp, bool isMyship, float& sps) : posX(shipPosx), posY(shipPosy), speed(sp), speedScale(sps)
	{
		if (isMyship)
			pImageBullet = Simple2D::CreateImage("../../Content/Textures/PlayerBullet.png");
		else
			pImageBullet = Simple2D::CreateImage("../../Content/Textures/EnemyBullet.png");
		getSize();
	}

	Bullets::~Bullets()
	{
		if(pImageBullet)
		Simple2D::DestroyImage(pImageBullet);
		free(pWidth);
		free(pHeight);
		pWidth = nullptr;
		pHeight = nullptr;
		pImageBullet = nullptr;
	}

	void Bullets::drawBullets(bool isMyship)
	{
		if (pImageBullet)
		{
			if (isMyship)
				Simple2D::DrawImage(pImageBullet, (float)posX, (float)posY, 0, 1);
			else
				Simple2D::DrawImage(pImageBullet, (float)posX, (float)posY, 180, 1);
		}
	}
	
	void Bullets::movement(bool isMyship)
	{
		if (isMyship)
			posX += speed* speedScale;
		else
			posX -= speed* speedScale;
	}
	
	float Bullets::getPosx()
	{
		return posX;
	}

	float Bullets::getPosy()
	{
		return posY;
	}

	void Bullets::getSize()
	{
		pWidth = (int*)malloc(sizeof(int));
		pHeight = (int*)malloc(sizeof(int));
		if (pImageBullet)
			Simple2D::GetImageSize(pImageBullet, pWidth, pHeight);
	}

	int Bullets::getHeight()
	{
		return *pHeight;
	}

	int Bullets::getWidth()
	{
		return *pWidth;
	}


	void Bullets::setSpeed(int &sp)
	{
		speed = sp;
	}

	int Bullets::getSpeed()
	{
		return speed;
	}

	void Bullets::setSpeedScale(float &scale)
	{
		speedScale = scale;
	
	}
}

#ifdef TEST_BULLETS
int main()
{



	return 0;
}
#endif

