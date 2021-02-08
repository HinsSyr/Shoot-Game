///////////////////////////////////////////////////////////////////////
// Enemy.cpp -             Enemy's spaceship                         //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

#include "Enemy.h"



namespace Simple2D
{
	Enemy::Enemy(int& tp, int& minSp, int& maxSp, float &sps) : type(tp),minSpeed(minSp),maxSpeed(maxSp),maxHits(tp),speedScale(sps)
	{
		pImageEnemy = Simple2D::CreateImage("../../Content/Textures/Enemy_" + std::to_string(tp) + ".png");
		lastFiretime = 0;
		countHits = 0;
		randomPos();
		 getSize();
	}

	Enemy::~Enemy()
	{
		if(pImageEnemy)
		Simple2D::DestroyImage(pImageEnemy);
		free(pWidth);
		free(pHeight);
		pWidth = nullptr;
		pHeight = nullptr;
		pImageEnemy = nullptr;
	}

	float Enemy::getLastFiretime()
	{
		return lastFiretime;
	}

	void Enemy::randomPos()
	{
		speed = getRandomNumber(minSpeed,maxSpeed);
		speedY = speed * 0.2;
		posX = getRandomNumber(1050,1500);
		posY = getRandomNumber(100, 650);
		//moving from right to left center
		if(posY < 384)
		{
			speedY = -speedY;
		}
	}

	int Enemy::getRandomNumber(int a, int b)
	{
		return (rand() % (b - a + 1)) + a;
	}

	void Enemy::movement()
	{

		posX -= speed * speedScale;
		posY = posY + speedY*0.2* speedScale;

	}

	void Enemy::drawShip()
	{
		//The image of type3 is reverse, so rotate it back.
		if (pImageEnemy)
		{
			if (type == 3)
				Simple2D::DrawImage(pImageEnemy, (float)posX, (float)posY, 180, 1);
			else
				Simple2D::DrawImage(pImageEnemy, (float)posX, (float)posY, 0, 1);
		}
	}
	
	float Enemy::getPosx()
	{
		return posX;
	}

	float Enemy::getPosy()
	{
		return posY;
	}

	 void Enemy::setLastFiretime()
	{
		 lastFiretime=Simple2D::GetGameTime();
	}

	 void Enemy::getSize()
	 {
		 pWidth = (int*)malloc(sizeof(int));
		 pHeight = (int*)malloc(sizeof(int));
		 if (pImageEnemy)
			 Simple2D::GetImageSize(pImageEnemy, pWidth, pHeight);
	 }

	 int Enemy::getHeight()
	 {
	 
		 return *pHeight;
	 }

	 int Enemy::getWidth()
	 {
		 return *pWidth;
	 }

	 void Enemy::increHitCount(int count)
	 {
		 countHits += count;
	 }

	 int Enemy::getHitCount()
	 {
		 return countHits;
	 }

	 int Enemy::getMaxHit()
	 {
		 return maxHits;
	 }

	 void Enemy::increMaxHit(int count)
	 {
		 maxHits += count;
	 }

	 void Enemy::setSpeed(int &minSp, int &maxSp)
	 {
		 minSpeed = minSp;
		 maxSpeed = maxSp;
		 if (speed > maxSp) speed = maxSp;
		 if (speed < minSp) speed = minSp;
		 if (speedY > 0)
			 speedY = speed / 2;
		 else
			 speedY = -speed / 2;
	 }

	 int Enemy::getMaxSpeed()
	 {
		 return maxSpeed;
	 }

	 int Enemy::getMinSpeed()
	 {
		 return minSpeed;
	 }

	 void Enemy::resumeGame()
	 {
	 }

	 void Enemy::setSpeedScale(float &scale)
	 {
		 speedScale = scale;
	 }

	 int Enemy::getType()
	 {
		 return type;
	 }

	 void Enemy::upgrade(int &tp)
	 {
	 }

	 bool Enemy::isInvincible()
	 {
		 return false;
	 }

	 void Enemy::invincibleEvent()
	 {
	 }

}

#ifdef TEST_ENEMY
int main()
{



	return 0;
}
#endif

