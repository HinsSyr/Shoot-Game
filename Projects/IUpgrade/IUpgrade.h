#ifndef IUPGRADE_H
#define IUPGRADE_H
///////////////////////////////////////////////////////////////////////
// IUpgrade.h              Upgrade interface                         //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////


namespace Simple2D
{

	class IUpgrade
	{
	public:
		virtual ~IUpgrade() {};                                  //Release derived and base class resources.
		virtual void drawUpgrade() = 0;                          //Draw Upgrade
		virtual void movement() = 0;                             //Upgrade movement
		virtual int getHeight() = 0;                             //Get upgrade height
		virtual int getWidth() = 0;                              //Get upgrade width
		virtual void setSpeed(int& sp) = 0;                      //Set upgrade move speed
		virtual void setSpeedScale(float& sps) = 0;              //Change the objects' movement coefficient
		virtual float getPosx() = 0;                             //Get upgrade X-axis position
		virtual float getPosy() = 0;                             //Get upgrade Y-axis position
	};


}
#endif