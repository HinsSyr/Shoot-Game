#ifndef BACKGROUND_H
#define BACKGROUND_H
///////////////////////////////////////////////////////////////////////
// Background.h -          Generate environment and all objets       //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////

/*
 * Package Operations:
 * -------------------
 * - This package contains a Background class that implements IBackground
 *   interface.  It also contains a Factory class that creates instances
 *   of Background.
 * - In this package, all objects will be generated, includes Bullets, Myspaceship, enemy etc.
 *   The interaction between all objects will be handled in this packge.
 *   Game flow design is also put in this package.
 * 
 * Required Files:
 * ---------------
 * IBackground.h
 * Simple2D.h
 * Meteorite.h      Meteorite.cpp
 * Enemy.h          Enemy.cpp
 * MySpaceship.h    MySpaceship.cpp
 * Hints.h          Hints.cpp
 * Explosion.h      Explosion.cpp
 * Upgrade.h        Upgrade.cpp
 * Bullets.h        Bullets.cpp
 * 
 * Maintenance History
 * -------------------
 * ver 1.0 : 05 Dec 2020
 * - first release
 */


#include <vector>
#include <iostream>
#include "IBackground.h"
#include "../../Extern/Simple2D/Includes/Simple2D.h"
#include "../IMeteorite/Meteorite.h"
#include "../ISpaceships/Enemy.h"
#include "../ISpaceships/MySpaceship.h"
#include "../IHints/Hints.h"
#include "../IExplosion/Explosion.h"
#include "../IUpgrade/Upgrade.h"
#include "../IBullets/Bullets.h"


namespace Simple2D
{
	class Background : public IBackground
	{

	public:
		Background();
		~Background();
		virtual void drawBackground() override;
		virtual void movement() override;
		virtual void collisionDetection() override;
		
		
	private:

		void collisionMyshipAndMeteo();                         //collision detection between player's ship and meteorites.
		void collisionMyshipAndEnemy();                         //collision detection between player's ship and enemies.
		void collisionMyshipAndEnemyBullet();                   //collision detection between player's ship and enemies' bullets.
		void collisionMyshipAndUpgrade();                       //collision detection between player's ship and upgrades.
		void collisionMybulletAndMeteo();                       //collision detection between player's bullets and meteorites.
		void collisionMybulletAndEnemy();                       //collision detection between player's bullets and enemies.

		void createMeteorites();                                      //create meteorite objects.
		void createEnemyBullets();                                    //create enemies' bullets objects.
		void createEnemies();                                         //create enemies objects.
		void createMybullets();                                       //create player's bullets objects.
		void createExplosions(int &type,float &posX, float &posY);    //create explosion objects.
		void createUpgrade();                                         //create upgrade objects.
		void createMyship(int tp=1);                                  //create player's ship objects.

		void drawEnemeyBullets();                                     //draw enemies' bullets
		void drawMeteorites();                                        //draw meteorites
		void drawEnemies();                                           //draw enemies
		void drawMybullets();                                         //draw player's bullets
		void drawExplosions();                                        //draw explosions
		void drawUpgrade();                                           //draw upgrade
		void drawMyship();                                            //draw player's ship
	
		void destroyMybullets(int &i);                                //release player' bullet resources by id
		void destroyMeteories(int &i);                                //release meteorite resources by id
		void destroyEnemies(int &i);                                  //release enemy resources by id
		void destroyEnemyBullets(int &i);                             //release enemies' bullets resources by id
		void destroyExplosion(int &i);                                //release explosion resources by id
		void destroyUpgrade();                                        //release all upgrade resources
		void destroyHints();                                          //release all hints resources
		void destroyMyship();                                         //release all player' ship resources

		void destroyAllMybullets();                                   //release all player' bullets resources
		void destroyAllMeteories();                                   //release all meteorites resources
		void destroyAllEnemies();                                     //release all enemies resources
		void destroyAllEnemyBullets();                                //release all enemies' bullets resources
		void destroyAllExplosion();                                   //release all explosions resources

		void resumeGame();                                            //Operations when game is being unpaused.
		void menuConfig();                                            //configuration the menu
		void restartConfig();                                         //configuration all variable
		void getSize();                                               //get image size

		//adjust the game difficulty when time flows includes:enemies respawn time gap, enemies' bullets respawn time gap ,meteorites repawn time gap
		void adjustDifficultWithTime();                  
		int getRandomNumber(int a, int b);                            //get random number from [A,B]
		void gameSpeedAdjust();                                       //adjust objects movement speed(posX and posY offsets value).
		void CPUscaleChange();                                        //Change the objects' movement coefficient
		void useNuclear();                                            //player uses nuclear event.

		Image* pImageLayout1 = nullptr;
		Image* pImageLayout2 = nullptr;
		Image* pImageMoon = nullptr;
		Simple2D::ISpaceships* pship = nullptr;
		Simple2D::IHints* pHints = nullptr;
		Simple2D::IUpgrade* pUpgrade = nullptr;
		float gameTime, enemySpawnTime, meteoSpawnTime,enemySpawnSpeed,meteoSpawnSpeed,enemyFireSpeed,myFireSpeed,UpgradeSpawnSpeed,UpgradeSpawnTime, speedScale;
		float posX1, posX2, posY;
		int bulletSpeed, minMeteoSpeed, maxMeteoSpeed, myShipSpeed, minEnemySpeed, maxEnemySpeed, gameMainSpeed, upgradeSpeed, MyshiprespawnTime, MyshipLastDieTime, difficultyBase;
		int pressSpace, pressEsc;
		int* pWidth, * pHeight;
		bool menuFlag, pauseFlag, saveScoresFlag;

		std::vector<IBullets*> EnemyBullets;                        //restore all pointers point to enemies' bullets resources.
		std::vector<IBullets*> MyBullets;                           //restore all pointers point to player' bullets resources.
		std::vector<IMeteorite*> Meteorites;                        //restore all pointers point to meteorites resources.
		std::vector<ISpaceships*> Enemies;                          //restore all pointers point to enemies resources.
		std::vector<IExplosion*> Explosions;                        //restore all pointers point to explosions resources.

		std::vector<int> nullptrEnemyBulletsIndex;                  //restore null pointers'index in EnemyBullets, resue them.
		std::vector<int> nullptrMyBulletsIndex;                     //restore null pointers'index in MyBullets, resue them.
		std::vector<int> nullptrMeteoIndex;                         //restore null pointers'index in Meteorites, resue them.
		std::vector<int> nullptrEnemyIndex;                         //restore null pointers'index in Enemies, resue them.
		std::vector<int> nullptrExplosionsIndex;                    //restore null pointers'index in Explosions, resue them.

	
	};


	class BackgroundFactory {
	public:
		static IBackground* createBackground()
		{
			Background* rtn = new Background();
			return rtn;
		}


	};
}

#endif