///////////////////////////////////////////////////////////////////////
// Explosion.cpp           Explosion object                          //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

#include "Explosion.h"


namespace Simple2D
{
	Explosion::Explosion(int& tp, float& posX, float &posY) : posX(posX),posY(posY)
	{
		pImageExplosion = Simple2D::CreateImage("../../Content/Textures/Explosion_" + std::to_string(tp) + ".png");
		createTime = Simple2D::GetGameTime();
		rotate = getRandomNumber(-180, 180);
	}

	Explosion::~Explosion()
	{
		if (pImageExplosion)
			Simple2D::DestroyImage(pImageExplosion);
		pImageExplosion = nullptr;
	}

	void Explosion::drawExplosion()
	{
		if (pImageExplosion)
			Simple2D::DrawImage(pImageExplosion, posX, posY, rotate, 1);
	}

	float Explosion::getDuration()
	{
		return Simple2D::GetGameTime() - createTime;
	}

	int Explosion::getRandomNumber(int a, int b)
	{
		return (rand() % (b - a + 1)) + a;
	}

}

#ifdef TEST_EXPLOSION
int main()
{



	return 0;
}
#endif

