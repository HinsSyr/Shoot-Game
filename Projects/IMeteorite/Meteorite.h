#ifndef METEORITE_H
#define METEORITE_H
///////////////////////////////////////////////////////////////////////
// Meteorite.h             Meteorite object                          //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * - This package contains a Meteorite class that implements IMeteorite
 *   interface.  It also contains a Factory class that creates instances
 *   of Meteorite.
 *
 * Required Files:
 * ---------------
 * IMeteorite.h
 * Simple2D.h
 *
 * Maintenance History
 * -------------------
 * ver 1.0 : 05 Dec 2020
 * - first release
 */


#include "IMeteorite.h"
#include "../../Extern/Simple2D/Includes/Simple2D.h"
#include <iostream>

namespace Simple2D
{
	class Meteorite : public IMeteorite
	{

	public:
		Meteorite(int &tp, int& minSp, int& maxSp, float &sps);
		~Meteorite();
		virtual void drawMeteorite() override;
		virtual float getPosx() override;
		virtual float getPosy() override;
		virtual void movement() override;
		virtual int getDesx() override;
		virtual int getDesy() override;
		virtual int getHeight() override;
		virtual int getWidth() override;
		virtual void increHitCount(int count) override;
		virtual int getHitCount() override;
		virtual int getMaxHit() override;
		virtual void increMaxHit(int count) override;
		virtual void setSpeed(int &minSp, int &maxSp) override;
		virtual int getMaxSpeed() override;
		virtual int getMinSpeed() override;
		virtual void setSpeedScale(float &scale) override;

	private:
		void getSize();
		void randomPos();                                              //meteorites born in random places
		int getRandomNumber(int a, int b);                             //get random number from [A,B]
		Simple2D::Image* pImageMeteorite = nullptr;
		float  posX, posY, speedScale;
		int speed, scale, rotate, desX, desY, speedX, speedY, minSpeed, maxSpeed, countHits, maxHits;
		int* pWidth, * pHeight;
		bool goUp;
	};


	class MeteoriteFactory {
	public:
		static IMeteorite* createMeteorite(int &tp, int& minSp, int& maxSp, float &sps)
		{
			Meteorite* rtn = new Meteorite(tp,minSp,maxSp,sps);
			return rtn;
		}


	};
}

#endif