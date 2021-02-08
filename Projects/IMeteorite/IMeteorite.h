#ifndef IMETEORITE_H
#define IMETEORITE_H
///////////////////////////////////////////////////////////////////////
// IMeteorite.h            Meteorite interface                       //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

namespace Simple2D
{

	class IMeteorite
	{
	public:
		virtual ~IMeteorite() {};                             //Release derived and base class resources.
		virtual void drawMeteorite() = 0;                     //Draw meteorites
		virtual float getPosx() = 0;                          //Get meteorite X-axis position.
		virtual float getPosy() = 0;                          //Get meteorite Y-axis position.
		virtual void movement() = 0;                          //Turn on the meteorite movement.
		virtual int getDesx() = 0;                            //Get the meteorite destion X-axis position.
		virtual int getDesy() = 0;                            //Get the meteorite destion Y-axis position.
		virtual int getHeight() = 0;                          //Get the meteorite height.
		virtual int getWidth() = 0;                           //Get the meteorite width.
		virtual void increHitCount(int count) = 0;            //Increase/decrease the count of being hit
		virtual int getHitCount() = 0;                        //Get the current count of being hit
		virtual int getMaxHit() = 0;                          //Get the maximum count of hit
		virtual void increMaxHit(int count) = 0;              //Increase/decrease the count of being hit
		virtual void setSpeed(int &minSp, int &maxSp) = 0;      //Set meteorite speed range.
		virtual int getMaxSpeed() = 0;                        //Get the maximum speed.
		virtual int getMinSpeed() = 0;                        //Get the minimum spped.
		virtual void setSpeedScale(float &scale) = 0;          //Change the objects' movement coefficient
		
	};


}
#endif