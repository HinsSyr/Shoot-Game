#ifndef MYSPACESHIP_H
#define MYSPACESHIP_H
///////////////////////////////////////////////////////////////////////
// MySpaceship.h -         Player's spaceship                        //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * - This package contains a MySpaceship class that implements ISpaceship
 *   interface.  It also contains a Factory class that creates instances
 *   of MySpaceship.
 *
 * Required Files:
 * ---------------
 * ISpaceships.h 
 * Simple2D.h
 *
 * Maintenance History
 * -------------------
 * ver 1.0 : 05 Dec 2020
 * - first release
 */

#include "../../Extern/Simple2D/Includes/Simple2D.h"
#include "ISpaceships.h"
#include <iostream>


namespace Simple2D
{
	class MySpaceship : public ISpaceships
	{

	public:
		MySpaceship(int tp,int& sp, float &sps);
		virtual ~MySpaceship();

		virtual void movement() override;
		virtual void drawShip() override;
		virtual float getPosx() override;
		virtual float getLastFiretime() override;
		virtual float getPosy() override;
		virtual void setLastFiretime() override;
		virtual int getHeight() override;
		virtual int getWidth() override;
		virtual void increHitCount(int count) override;
		virtual int getHitCount() override;
		virtual int getMaxHit() override;
		virtual void increMaxHit(int count) override;
		virtual void setSpeed(int &minSp, int &maxSp) override;
		virtual int getMaxSpeed() override;
		virtual int getMinSpeed() override;
		virtual void resumeGame() override;
		virtual void setSpeedScale(float &scale) override;
		virtual int getType() override;
		virtual void upgrade(int &tp) override;
		virtual bool isInvincible() override;
		virtual void invincibleEvent() override;
		
	private:
		void getSize();                            //Get the height and width of image.
		Simple2D::Image* pImageShip = nullptr;
		int* pWidth, * pHeight;
		int pressL = 0, pressR = 0, pressU = 0, pressD = 0, h = 0, v = 0, type, maxHits, countHits, speed;
		float posX, posY, lastFiretime, speedScale, invincStartTime;
		bool invincibleFlag;
	};


	class SpaceshipFactory {
	public:
		static ISpaceships* createMyship(int tp,int& sp, float &sps)
		{
			MySpaceship* rtn = new MySpaceship(tp, sp, sps);
			return rtn;
		}


	};
}

#endif