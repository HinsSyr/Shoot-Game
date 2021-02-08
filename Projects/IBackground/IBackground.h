#ifndef IBACKGROUND_H
#define IBACKGROUND_H
///////////////////////////////////////////////////////////////////////
// IBackground.h           Background interface                      //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

namespace Simple2D
{

	class IBackground
	{
	public:
		virtual ~IBackground() {};                   //Release derived and base class resources.
		virtual void drawBackground() = 0;           //Draw background,includes all objects' drawing.
		virtual void movement() = 0;                 //Background movement,includes all objects' movement.
		virtual void collisionDetection() = 0;       //Detect collisions between objects.
		
	};


}
#endif