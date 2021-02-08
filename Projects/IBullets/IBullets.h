#ifndef IBULLETS_H
#define IBULLETS_H
///////////////////////////////////////////////////////////////////////
// IBullets.h -            Bullets interface                         //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////
namespace Simple2D
{

	class IBullets
	{
	public:
		virtual ~IBullets() {};                                    //Release derived and base class resources.
		virtual void movement(bool isMyship) = 0;                  //Turn on the bullets movement.
		virtual void drawBullets(bool isMyship) = 0;               //Draw bullets
		virtual float getPosx() = 0;                               //Get bullet X-axis position.
		virtual float getPosy() = 0;                               //Get bullet Y-axis position.
		virtual int getHeight() = 0;                               //Get bullet height.
		virtual int getWidth() = 0;                                //Get bullet width.
		virtual void setSpeed(int &sp) = 0;                        //Set bullet  moving speed.
		virtual int getSpeed() = 0;                                //Get bullet moving speed.
		virtual void setSpeedScale(float &scale) = 0;              //Change the objects' movement coefficient
	};


}
#endif