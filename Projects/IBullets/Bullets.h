#ifndef BULLETS_H
#define BULLETS_H
///////////////////////////////////////////////////////////////////////
// Bullets.h               Bullets object                            //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * - This package contains a Bullets class that implements IBullets
 *   interface.  It also contains a Factory class that creates instances
 *   of Bullets.
 *
 * Required Files:
 * ---------------
 * IBullets.h
 * Simple2D.h
 *
 * Maintenance History
 * -------------------
 * ver 1.0 : 05 Dec 2020
 * - first release
 */

#include "IBullets.h"
#include "../../Extern/Simple2D/Includes/Simple2D.h"
#include <iostream>


namespace Simple2D
{
	class Bullets : public IBullets
	{

	public:
		 Bullets(float &shipPosx, float &shipPosy, int& sp, bool isMyship, float &sps);
		 ~Bullets();

		 virtual void drawBullets(bool isMyship) override;
		 virtual void movement(bool isMyship) override;
		 virtual float getPosx() override;
		 virtual float getPosy() override;
		 virtual int getHeight() override;
		 virtual int getWidth() override;
		 virtual void setSpeed(int &sp) override;
		 virtual int getSpeed() override;
		 virtual void setSpeedScale(float &scale) override;

	private:
		void getSize();
		Image* pImageBullet = nullptr;
		float posX, posY, speedScale;
		int* pWidth, * pHeight;
		int speed;
	};


	class BulletsFactory {
	public:
		static IBullets* createBullet(float &shipPosx, float &shipPosy, int& sp , bool isMyship , float &sps)
		{
			Bullets* rtn = new Bullets( shipPosx,  shipPosy, sp, isMyship,sps);
			return rtn;
		}


	};
}

#endif