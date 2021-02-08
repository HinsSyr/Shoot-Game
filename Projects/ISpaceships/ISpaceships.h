#ifndef ISPACESHIPS_H
#define ISPACESHIPS_H
///////////////////////////////////////////////////////////////////////
// ISpaceships.h -         Spaceship interface                       //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////


namespace Simple2D
{

	class ISpaceships
	{
	public:
		virtual ~ISpaceships() {};                      //Release derived and base class resources.
		virtual void movement() = 0 ;                   //Turn on the spaceship movement.
		virtual void drawShip() = 0;                    //Draw the spaceship
		virtual float getPosx() = 0;                    //Get the spaceship X-axis position.
		virtual float getPosy() = 0;                    //Get the spaceship Y-axis position.
		virtual float getLastFiretime() = 0;            //Get the lastest shooting time.
		virtual void setLastFiretime() = 0;             //Set the lastest shooting time.
		virtual int getHeight() = 0;                    //Get the spaceship height.
		virtual int getWidth() = 0;                     //Get the spaceship width.
		virtual void increHitCount(int count) = 0;      //Increase/decrease the count of being hit
		virtual int getHitCount() = 0;                  //Get the current count of being hit
		virtual int getMaxHit() = 0;                    //Get the maximum count of hit
		virtual void increMaxHit(int count) = 0;        //Increase/decrease the count of being hit
		virtual void setSpeed(int &minSp, int &maxSp) = 0;  //Set spaceship speed range.
		virtual int getMaxSpeed() = 0;                    //Get the maximum speed.
		virtual int getMinSpeed() = 0;                    //Get the minimum spped.
		virtual void resumeGame() = 0;                    //Operations when game is being unpaused.
		virtual void setSpeedScale(float &scale) = 0;      //Change the objects' movement coefficient
		virtual int getType() = 0;                        //Get the type of spaceship
		virtual void upgrade(int &tp) = 0;                 //Upgrade operation
		virtual bool isInvincible() = 0;                  //Get the invincible status
		virtual void invincibleEvent() = 0;               //Invincible operations
	private:

	};


}
#endif