#ifndef UPGRADE_H
#define UPGRADE_H

#include <vector>
#include "IMeteorite.h"
#include "../../Extern/Simple2D/Includes/Simple2D.h"


namespace Simple2D
{
	class Upgrade : public IMeteorite
	{

	public:
		Upgrade(int& tp, int& minSp, int& maxSp, float sps);
		~Upgrade();
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

		virtual void setSpeed(int minSp, int maxSp) override;
		virtual int getMaxSpeed() override;
		virtual int getMinSpeed() override;
		virtual void setSpeedScale(float scale) override;

	private:
		void getSize();
		int getRandomNumber(int a, int b);
		void randomPos();
		Simple2D::Image* pImageMeteorite = nullptr;
		float  posX, posY;
		int speed, scale, rotate, desX, desY, speedX, speedY;
		int* pWidth, * pHeight;
		int countHits, maxHits;
		int minSpeed, maxSpeed;
		float speedScale;

	};


	class MeteoriteFactory {
	public:
		static IMeteorite* createMeteorite(int& tp, int& minSp, int& maxSp, float sps)
		{
			Meteorite* rtn = new Meteorite(tp, minSp, maxSp, sps);
			return rtn;
		}


	};
}

#endif