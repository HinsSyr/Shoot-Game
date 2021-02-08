#ifndef EXPLOSION_H
#define EXPLOSION_H
///////////////////////////////////////////////////////////////////////
// Explosion.h             Explosion object                          //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * - This package contains a Explosion class that implements IExplosion
 *   interface.  It also contains a Factory class that creates instances
 *   of Explosion.
 *
 * Required Files:
 * ---------------
 * IExplosion.h
 * Simple2D.h
 *
 * Maintenance History
 * -------------------
 * ver 1.0 : 05 Dec 2020
 * - first release
 */


#include "IExplosion.h"
#include "../../Extern/Simple2D/Includes/Simple2D.h"
#include <iostream>

namespace Simple2D
{
	class Explosion : public IExplosion
	{
	public:
		Explosion(int &tp,float &posX, float &posY);
		~Explosion();

		virtual void drawExplosion() override;
		virtual float getDuration() override;
	private:
		int getRandomNumber(int a, int b);                   //get the random number from [A,B]
		Simple2D::Image* pImageExplosion = nullptr;
		float posX, posY, createTime;
		int rotate;

	};


	class ExplosionFactory {
	public:
		static IExplosion* createExplosions(int& tp, float& posX, float& posY)
		{
			Explosion* rtn = new Explosion(tp,posX,posY);
			return rtn;
		}

	};
}

#endif