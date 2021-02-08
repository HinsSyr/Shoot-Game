#ifndef IEXPLOSION_H
#define IEXPLOSION_H

///////////////////////////////////////////////////////////////////////
// IExplosion.h            Explosion interface                       //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

namespace Simple2D
{

	class IExplosion
	{
	public:
		virtual ~IExplosion() {};                           //Release derived and base class resources.
		virtual void drawExplosion() = 0;                   //Draw explosion.
		virtual float getDuration() = 0;                    //get the duration time of explosion.
	};


}
#endif