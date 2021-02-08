#ifndef ENEMY_H
#define ENEMY_H
///////////////////////////////////////////////////////////////////////
// Enemy.h                 Enemy spaceship                           //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * - This package contains a Enemy class that implements ISpaceship
 *   interface.  It also contains a Factory class that creates instances
 *   of Enemy.
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
	class Enemy : public ISpaceships
	{
	public:
		Enemy(int& tp,int& minSp, int& maxSp, float &sps);
		virtual ~Enemy();

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
		void getSize();
		void randomPos();                          //Enemies born in random places
		int getRandomNumber(int a, int b);         //get random number from [A,B]
		Simple2D::Image* pImageEnemy = nullptr;
		float posX, posY, lastFiretime, speedScale;
		int speed, speedY, type, countHits, maxHits, minSpeed, maxSpeed;
		int* pHeight, * pWidth;
	};


	class EnemyFactory {
	public:
		static ISpaceships* createEnemy(int& tp, int& minSp, int& maxSp, float &sps)
		{
			Enemy* rtn = new Enemy(tp,minSp,maxSp,  sps);
			return rtn;
		}


	};
}

#endif