#ifndef UPGRADE_H
#define UPGRADE_H

///////////////////////////////////////////////////////////////////////
// Upgrade.h               Upgrade object                            //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * - This package contains a Upgrade class that implements IUpgrade
 *   interface.  It also contains a Factory class that creates instances
 *   of Upgrade.
 *
 * Required Files:
 * ---------------
 * IUpgrade.h
 * Simple2D.h
 *
 * Maintenance History
 * -------------------
 * ver 1.0 : 05 Dec 2020
 * - first release
 */
#include "IUpgrade.h"
#include "../../Extern/Simple2D/Includes/Simple2D.h"
#include <iostream>

namespace Simple2D
{
	class Upgrade : public IUpgrade
	{
	public:
		Upgrade(int &sp,float &sps);
		~Upgrade();

		virtual void drawUpgrade() override;
		virtual int getHeight() override;
		virtual int getWidth() override;
		virtual void movement() override;
		virtual void setSpeed(int& sp) override;
		virtual void setSpeedScale(float& sps) override;
		virtual float getPosx() override;
		virtual float getPosy() override;
	private:
		int getRandomNumber(int a, int b);                 //get random number from [A,B]
		void randomPos();                                  //Upgrade born in random places
		void getSize();
		Simple2D::Image* pImageUpgrade = nullptr;
		int* pWidth, *pHeight;
		float posX, posY, speedScale;
		int speed, speedY;
	};


	class UpgradeFactory {
	public:
		static IUpgrade* createUpgrades(int &sp,float &sps)
		{
			Upgrade* rtn = new Upgrade(sp,sps);
			return rtn;
		}


	};
}

#endif