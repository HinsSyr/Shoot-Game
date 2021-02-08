///////////////////////////////////////////////////////////////////////
// MySpaceship.cpp         Player's spaceship                        //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

#include "MySpaceship.h"



namespace Simple2D
{
	MySpaceship::MySpaceship(int tp, int& sp, float &sps) :  type(tp), speed(sp), speedScale(sps)
	{
		pImageShip = Simple2D::CreateImage("../../Content/Textures/Player_" + std::to_string(tp) + ".png");
		posX = 300;
		posY = 300;
		lastFiretime = 0;
		maxHits = 1;
		countHits = 0;
		getSize();
		invincibleFlag = false;
		invincStartTime = 0;
	}

	MySpaceship::~MySpaceship()
	{
		if(pImageShip)
		Simple2D::DestroyImage(pImageShip);
		free(pWidth);
		free(pHeight);
		pWidth = nullptr;
		pHeight = nullptr;
		pImageShip = nullptr;
	}

	float MySpaceship::getPosx()
	{
		return posX;
	}

	float MySpaceship::getPosy()
	{
		return posY;
	}

	float MySpaceship::getLastFiretime()
	{
		return lastFiretime;
	}

	void MySpaceship::setLastFiretime()
	{
		lastFiretime = Simple2D::GetGameTime();
		
	}

	void MySpaceship::movement()
	{
		/* The player could control the ship by WASD and ARROW in order to avoid the key conflict
   * At least i met this problem (Can't press 2 ARROWS+SPACE at one time) when designing the game.
*/
		if (Simple2D::IsKeyReleased(Simple2D::KEY_D)) { pressR = 0; }
		if (Simple2D::IsKeyReleased(Simple2D::KEY_A)) { pressL = 0; }
		if (Simple2D::IsKeyReleased(Simple2D::KEY_W)) { pressU = 0; }
		if (Simple2D::IsKeyReleased(Simple2D::KEY_S)) { pressD = 0; }

		if (Simple2D::IsKeyPressed(Simple2D::KEY_A))
		{
			pressL = 1;
		}

		if (Simple2D::IsKeyPressed(Simple2D::KEY_W))
		{
			pressU = 1;

		}

		if (Simple2D::IsKeyPressed(Simple2D::KEY_D))
		{
			pressR = 1;
		}


		if (Simple2D::IsKeyPressed(Simple2D::KEY_S))
		{
			pressD = 1;

		}

		if (Simple2D::IsKeyReleased(Simple2D::KEY_RIGHT_ARROW)) { pressR = 0; }
		if (Simple2D::IsKeyReleased(Simple2D::KEY_LEFT_ARROW)) { pressL = 0; }
		if (Simple2D::IsKeyReleased(Simple2D::KEY_UP_ARROW)) { pressU = 0; }
		if (Simple2D::IsKeyReleased(Simple2D::KEY_DOWN_ARROW)) { pressD = 0; }

		if (Simple2D::IsKeyPressed(Simple2D::KEY_LEFT_ARROW))
		{
			pressL = 1;
		}

		if (Simple2D::IsKeyPressed(Simple2D::KEY_UP_ARROW))
		{
			pressU = 1;

		}

		if (Simple2D::IsKeyPressed(Simple2D::KEY_RIGHT_ARROW))
		{
			pressR = 1;
		}


		if (Simple2D::IsKeyPressed(Simple2D::KEY_DOWN_ARROW))
		{
			pressD = 1;

		}

		/*If player holds two opposite keys, like UP and DOWN, the ship should be static,
		//when release one of them, the ship will go to the opposite side.
		*/
		if (pressL * pressR || !(pressL + pressR))
		{
			h = 0;
		}
		else
		{
			if (pressL) { h = -speed; }
			if (pressR) { h = speed; }
		}

		if (pressU * pressD || !(pressU + pressD))
		{
			v = 0;
		}
		else
		{
			if (pressU) { v = speed; }
			if (pressD) { v = -speed; }
		}
		posX += h * speedScale;
		posY += v * speedScale;
		if (posX + *pWidth / 2 > 1023) posX = 1023 - *pWidth / 2;
		if (posX - *pWidth / 2 < 0) posX = *pWidth / 2;
		if (posY + *pHeight / 2 > 683) posY = 683 - *pHeight / 2;
		if (posY - *pHeight / 2 < 83) posY = *pHeight / 2 + 83;

	}

	void MySpaceship::drawShip()
	{
		if (pImageShip)
			Simple2D::DrawImage(pImageShip, (float)posX, (float)posY, 0, 1);
	}

	void MySpaceship::getSize()
	{
		pWidth = (int*)malloc(sizeof(int));
		pHeight = (int*)malloc(sizeof(int));
		if(pImageShip)
		Simple2D::GetImageSize(pImageShip, pWidth, pHeight);
		
	}
	
	int MySpaceship::getHeight()
	{
		return  *pHeight;
	}

	int MySpaceship::getWidth()
	{
		return  *pWidth;
	}

	void MySpaceship::increHitCount(int count)
	{
		countHits += count;
	}

	int MySpaceship::getHitCount()
	{
		return countHits;
	}

	int MySpaceship::getMaxHit()
	{
		return maxHits;
	}

	void MySpaceship::increMaxHit(int count)
	{
		maxHits += count;
	}

	void MySpaceship::setSpeed(int &minSp, int &maxSp)
	{
		speed = minSp;
	}

	int MySpaceship::getMaxSpeed()
	{
		return speed;
	}

	int MySpaceship::getMinSpeed()
	{
		return speed;
	}

	void MySpaceship::resumeGame()
	{
		//after resume the game, the key value will be reset.
		pressL = 0;
		pressR = 0;
		pressU = 0;
		pressD = 0;
	}

	void MySpaceship::setSpeedScale(float &scale)
	{
		speedScale = scale;
	}

	int MySpaceship::getType()
	{
		return type;
	}

	void MySpaceship::upgrade(int &tp)
	{
		//when upgrading, the ship should be invincible.
		invincibleFlag = true;
		invincStartTime = Simple2D::GetGameTime();
		type = tp;
		if(pImageShip)
		Simple2D::DestroyImage(pImageShip);
		pImageShip = Simple2D::CreateImage("../../Content/Textures/Player_" + std::to_string(tp) + ".png");
		getSize();
	}

	bool MySpaceship::isInvincible()
	{
		return invincibleFlag;
	}

	void MySpaceship::invincibleEvent()
	{
		//The default ship invincible time is 5 seconds.
		if (invincibleFlag && Simple2D::GetGameTime() - invincStartTime <= 5)
		{

			float count = Simple2D::GetGameTime() - (int)Simple2D::GetGameTime();
			//for every 1 second, the ship image is being drawed and deleted to achieve the blink effect.
			if ((count > 0.15 && count < 0.25) || (count > 0.4 && count < 0.5) || (count > 0.65 && count < 0.75) || (count > 0.75 && count < 0.9))
			{
				if (pImageShip)
				{
					Simple2D::DestroyImage(pImageShip);
					pImageShip = nullptr;
				}
			}
			else
			{
				if (pImageShip == nullptr)
				{
					pImageShip = Simple2D::CreateImage("../../Content/Textures/Player_" + std::to_string(type) + ".png");
					getSize();
				}
			}
		}
		//quit the invincible status
		else if (Simple2D::GetGameTime() - invincStartTime > 5)
		{
			if (pImageShip == nullptr)
			{
				pImageShip = Simple2D::CreateImage("../../Content/Textures/Player_" + std::to_string(type) + ".png");
				getSize();
			}
			invincibleFlag = false;
			
		}
	}

	
}

#ifdef TEST_MYSPACESHIP
int main()
{



	return 0;
}
#endif

