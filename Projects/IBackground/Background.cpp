///////////////////////////////////////////////////////////////////////
// Background.cpp          Generate environment and all objets       //
//                                                                   //
// ver 1.0                                                           //
// Author: Bo Qiu          Master in Computer Engineering,           //
//                         Syracuse University                       //
//                         (315) 278-2362, qb86880301@gmail.com      //
///////////////////////////////////////////////////////////////////////
#include "Background.h"


namespace Simple2D
{
	Background::Background()
	{
		speedScale = 1;
		menuConfig();
	}

	Background::~Background()
	{
		restartConfig();
	}

	void Background::menuConfig()
	{
		if(!pImageLayout1)
		pImageLayout1 = Simple2D::CreateImage("../../Content/Textures/StarLayer.png");
		if (!pImageLayout2)
		pImageLayout2 = Simple2D::CreateImage("../../Content/Textures/StarLayer.png");
		if (!pImageMoon)
		pImageMoon = Simple2D::CreateImage("../../Content/Textures/Moon.png");
		if(!pHints)
		pHints = Simple2D::HintsFactory::createHints();
		getSize();

		menuFlag = true;
		pauseFlag = false;
		saveScoresFlag = false;

		pressEsc = 0;
		pressSpace = 0;

		posX1 = 800;
		posX2 = 2399;
		posY = 384;

		difficultyBase = 1;
		gameTime = 0;
		gameMainSpeed = 5;

		bulletSpeed = 2 * gameMainSpeed;

		meteoSpawnSpeed = 0.5;
		meteoSpawnTime = 0;
		minMeteoSpeed = gameMainSpeed - 2;
		maxMeteoSpeed = gameMainSpeed + 2;

		enemySpawnTime = 0;
		enemySpawnSpeed = 0.5;
		enemyFireSpeed = 1.2;
		minEnemySpeed = gameMainSpeed - 2;
		maxEnemySpeed = gameMainSpeed + 2;

		UpgradeSpawnSpeed = 15;
		upgradeSpeed = gameMainSpeed;

		myShipSpeed = gameMainSpeed;
		myFireSpeed = 0.1;
		MyshiprespawnTime = 3;
		MyshipLastDieTime = -3;
	}

	void Background::restartConfig()
	{
		if (pImageLayout1)
			Simple2D::DestroyImage(pImageLayout1);
		if (pImageLayout2)
			Simple2D::DestroyImage(pImageLayout2);
		if (pImageMoon)
			Simple2D::DestroyImage(pImageMoon);
		free(pWidth);
		free(pHeight);
		destroyMyship();
		destroyUpgrade();
		destroyHints();
		destroyAllMybullets();
		destroyAllMeteories();
		destroyAllEnemies();
		destroyAllEnemyBullets();
		destroyAllExplosion();

		pImageMoon = nullptr;
		pWidth = nullptr;
		pHeight = nullptr;
		pImageLayout1 = nullptr;
		pImageLayout2 = nullptr;
	}

	void Background::drawBackground()
	{
		if (pImageMoon)
			Simple2D::DrawImage(pImageMoon, 512, 384, 0, 1);
		if (pImageLayout2)
			Simple2D::DrawImage(pImageLayout2, posX2, posY, 0, 1);
		if (pImageLayout1)
			Simple2D::DrawImage(pImageLayout1, posX1, posY, 0, 1);
		// when in menu, we still see the background moves.
		if (menuFlag)   
		{
			pHints->drawMenu();
		}
		// when quit menu, we see the objects moves.
		if (!menuFlag)            
		{
			gameSpeedAdjust();
			pHints->drawHints();
			drawUpgrade();
			drawMybullets();
			drawMeteorites();
			drawEnemies();
			drawEnemeyBullets();
			drawExplosions();
			drawMyship();
		}
	}

	void Background::movement()
	{
		//ECS key responses when in menu
		if (menuFlag)         
		{
			if (Simple2D::IsKeyReleased(Simple2D::KEY_SPACE)) {

				pressSpace = 0;
			}

			if (Simple2D::IsKeyPressed(Simple2D::KEY_SPACE))
			{
				pressSpace = 1;
			}
			if (pressSpace)
			{
				gameTime = GetGameTime();
				menuFlag = false;
			}

		}
		//background position changes
		posX1 = posX1 - 2 * speedScale;
		posX2 = posX2 - 2 * speedScale;
		if (posX1 <= -800)
			posX1 = 2399;
		if (posX2 <= -800)
			posX2 = 2399;
		//KEY_P resonses when it is not in menu flow,pause the game.
		if (Simple2D::IsKeyPressed(KEY_P) && !menuFlag)
		{
			pauseFlag = !pauseFlag;
		}
		//if game is resumed, some key should be reset.
		if (pauseFlag) resumeGame();
		//if it is not in menu flow neither game is paused, objects will move. Or if game over(lives<=0), objects will still move however player doesn't have a ship.
		if ((!menuFlag && !pauseFlag) || pHints->getLives() <= 0)
		{
			if (pHints->getLives() > 0)
			{
				createMyship();
			}
			else
			{
				//game over
				if (Simple2D::IsKeyReleased(Simple2D::KEY_ESCAPE)) {

					pressEsc = 0;
				}

				if (Simple2D::IsKeyPressed(Simple2D::KEY_ESCAPE))
				{
					pressEsc = 1;
				}
				if (!saveScoresFlag)
				{
					pHints->saveScores();
					saveScoresFlag = true;
				}
				if (pressEsc)
				{
					//release all resources, and configure it again.
					restartConfig();
					menuConfig();
				}
			}
			//create objects and turn on objects's movement.
			createUpgrade();
			createMybullets();
			createMeteorites();
			createEnemies();
			createEnemyBullets();
		}


	}

	void Background::drawMyship()
	{
		if (pship != nullptr  )
		{
			//everytime when ship respawn, it has 5 seconds invincible status(can't be destroyed).
			pship->invincibleEvent();
			pship->drawShip();
		}

	}

	void Background::drawMybullets()
	{
		for (int i = 0; i < MyBullets.size(); i++)
		{

			if (MyBullets[i] != nullptr)
			{
				//release player's bullets resources when they go out of screen.
				if (MyBullets[i]->getPosx()-MyBullets[i]->getWidth()/2 < 0 || MyBullets[i]->getPosx()+MyBullets[i]->getWidth()/2 > 1023)
				{
					destroyMybullets(i);
				}
				else
					MyBullets[i]->drawBullets(true);
			}
		}
	}

	void Background::drawMeteorites()
	{
		for (int i = 0; i < Meteorites.size(); i++)
		{

			if (Meteorites[i] != nullptr)
			{
				//release meteorite resources when they go out of screen.
				if (Meteorites[i]->getPosx() < Meteorites[i]->getDesx() )
				{
					destroyMeteories(i);
				}
				else
					Meteorites[i]->drawMeteorite();
			}
		}
	}

	void Background::drawEnemies()
	{
		
		for (int i = 0; i < Enemies.size(); i++)
		{

			if (Enemies[i] != nullptr)
			{
				//release enemies resources when they go out of screen.
				if (Enemies[i]->getPosx() < -128)
				{
					destroyEnemies(i);
				}
				else
					Enemies[i]->drawShip();
			}
		}
	}

	void Background::drawEnemeyBullets()
	{
		for (int i = 0; i < EnemyBullets.size(); i++)
		{

			if (EnemyBullets[i] != nullptr)
			{
				//release enemies' bullets resources when they go out of screen.
				if (EnemyBullets[i]->getPosx() - EnemyBullets[i]->getWidth() / 2 < 0 || EnemyBullets[i]->getPosx() + EnemyBullets[i]->getWidth() / 2 > 1023)
				{
					destroyEnemyBullets(i);
				}
				else
					EnemyBullets[i]->drawBullets(false);
			}
		}
	
	
	}

	void Background::drawExplosions()
	{
		for (int i = 0; i < Explosions.size(); i++)
		{

			if (Explosions[i] != nullptr)
			{
				//release explosions resources when explosion lasts over 0.2 seconds
				if (Explosions[i]->getDuration() > 0.2)
				{
					destroyExplosion(i);
				}
				else
					Explosions[i]->drawExplosion();
			}
		}
	}

	void Background::drawUpgrade()
	{
		if (pUpgrade != nullptr)
		{
			//release upgrade resources when they go out of screen.
			if (pUpgrade->getPosx() < -50)
			{
				 destroyUpgrade();
			}
			else
			{
				pUpgrade->drawUpgrade();
			}

		}
	}

	void Background::createMyship(int tp)
	{
		if (pship == nullptr  && Simple2D::GetGameTime() - MyshipLastDieTime > MyshiprespawnTime)
		{
			pship = Simple2D::SpaceshipFactory::createMyship(tp,myShipSpeed, speedScale);
			pship->upgrade(tp);
		}
		if(pship!=nullptr)
		pship->movement();
		useNuclear();
		adjustDifficultWithTime();
	}

	void Background::createUpgrade()
	{
		if (pUpgrade == nullptr&& Simple2D::GetGameTime()-UpgradeSpawnTime>=UpgradeSpawnSpeed)
		{
			pUpgrade = Simple2D::UpgradeFactory::createUpgrades(gameMainSpeed, speedScale);
			UpgradeSpawnTime = Simple2D::GetGameTime();
		}
		if(pUpgrade != nullptr)
		pUpgrade->movement();
		
	}

	void Background::createExplosions(int& type, float& posX, float& posY)
	{
		
			Simple2D::IExplosion* explosion = Simple2D::ExplosionFactory::createExplosions(type, posX, posY);
			//clean the container if there are some un-null pointers
			while (!nullptrExplosionsIndex.empty() && Explosions[nullptrExplosionsIndex.back()] != nullptr)
			{
				nullptrExplosionsIndex.pop_back();
			}
			//if there are null pointers, reuse them
			if (!nullptrExplosionsIndex.empty())
			{
				Explosions[nullptrExplosionsIndex.back()] = explosion;
				nullptrExplosionsIndex.pop_back();
			}
			//else we apply new memory for container.
			else
			{
				Explosions.push_back(explosion);
			}

	}

	void Background::createMybullets()
	{
		//KEY_SPACE responses 
		if (Simple2D::IsKeyReleased(Simple2D::KEY_SPACE))
		{
			pressSpace = 0;
		}

		if (Simple2D::IsKeyPressed(Simple2D::KEY_SPACE))
		{
			pressSpace = 1;
		}

		if (pship != nullptr)
		{
			if (pressSpace && Simple2D::GetGameTime() - pship->getLastFiretime() >= myFireSpeed)
			{
				float shipPosx = pship->getPosx();
				for (int k = 0; k < pship->getType(); k++)
				{
					float shipPosy = pship->getPosy() - k * 10;
					Simple2D::IBullets* bullet = Simple2D::BulletsFactory::createBullet(shipPosx, shipPosy , bulletSpeed, true, speedScale);
					//clean the container if there are some un-null pointers
					while (!nullptrMyBulletsIndex.empty() && MyBullets[nullptrMyBulletsIndex.back()] != nullptr)
					{
						nullptrMyBulletsIndex.pop_back();
					}
					//if there are null pointers, reuse them
					if (!nullptrMyBulletsIndex.empty())
					{
						MyBullets[nullptrMyBulletsIndex.back()] = bullet;
						nullptrMyBulletsIndex.pop_back();
					}
					//else we apply new memory for container.
					else
					{
						MyBullets.push_back(bullet);
					}
					pship->setLastFiretime();
				}

			}


		}
		for (int i = 0; i < MyBullets.size(); i++)
		{
			if (MyBullets[i] != nullptr)
			{
				MyBullets[i]->movement(true);
			}
		}
	}

	void Background::createEnemyBullets()
	{
		
		for (int i = 0; i < Enemies.size(); i++)
		{
			if (Enemies[i] != nullptr)
			{
				
				if (Simple2D::GetGameTime() - Enemies[i]->getLastFiretime() >= enemyFireSpeed)
				{
					float EnemyPosx = Enemies[i]->getPosx();
					float EnemyPosy = Enemies[i]->getPosy();
					Simple2D::IBullets* bullet = Simple2D::BulletsFactory::createBullet(EnemyPosx, EnemyPosy, bulletSpeed, false, speedScale);
					//clean the container if there are some un-null pointers
					while (!nullptrEnemyBulletsIndex.empty() && EnemyBullets[nullptrEnemyBulletsIndex.back()] != nullptr)
					{
						nullptrEnemyBulletsIndex.pop_back();
					}
					//if there are null pointers, reuse them
					if (!nullptrEnemyBulletsIndex.empty())
					{
						EnemyBullets[nullptrEnemyBulletsIndex.back()] = bullet;
						nullptrEnemyBulletsIndex.pop_back();
					}
					//else we apply new memory for container.
					else
					{
						EnemyBullets.push_back(bullet);
					}
					Enemies[i]->setLastFiretime(); 
				}
			}
		}

		for (int i = 0; i < EnemyBullets.size(); i++)
		{
			if (EnemyBullets[i] != nullptr)
			{
				EnemyBullets[i]->movement(false);
			}
		}
	
	}

	void Background::createEnemies()
	{
		Simple2D::ISpaceships* enemy = nullptr;
		if (Simple2D::GetGameTime() - enemySpawnTime >= enemySpawnSpeed)
		{
			//get random enemy spaceship shape.
			int tp = getRandomNumber(1, 3);
			enemy = Simple2D::EnemyFactory::createEnemy(tp,minEnemySpeed,maxEnemySpeed,speedScale);
			enemySpawnTime = Simple2D::GetGameTime();
		
		}
		//clean the container if there are some un-null pointers
		while (!nullptrEnemyIndex.empty() && Enemies[nullptrEnemyIndex.back()] != nullptr)
		{
			nullptrEnemyIndex.pop_back();
		}
		//if there are null pointers, reuse them
		if (!nullptrEnemyIndex.empty() && enemy != nullptr)
		{
			Enemies[nullptrEnemyIndex.back()] = enemy;
			nullptrEnemyIndex.pop_back();
		}
		//else we apply new memory for container.
		else if (enemy != nullptr)
		{
			Enemies.push_back(enemy);
		}

		for (int i = 0; i < Enemies.size(); i++)
		{
			if (Enemies[i] != nullptr)
			{
				Enemies[i]->movement();
			}
		}
	}

	void Background::createMeteorites()
	{
		Simple2D::IMeteorite* meteorite = nullptr;
		if (Simple2D::GetGameTime() - meteoSpawnTime >= meteoSpawnSpeed)
		{
			int tp = getRandomNumber(1, 4);
			meteorite = Simple2D::MeteoriteFactory::createMeteorite(tp,minMeteoSpeed,maxMeteoSpeed,speedScale);
			meteoSpawnTime = Simple2D::GetGameTime();
		}
		//clean the container if there are some un-null pointers
		while (!nullptrMeteoIndex.empty() && Meteorites[nullptrMeteoIndex.back()] != nullptr)
		{
			nullptrMeteoIndex.pop_back();
		}
		//if there are null pointers, reuse them
		if (!nullptrMeteoIndex.empty() && meteorite != nullptr)
		{
			Meteorites[nullptrMeteoIndex.back()] = meteorite;
			nullptrMeteoIndex.pop_back();
		}
		//else we apply new memory for container.
		else if (meteorite != nullptr)
		{
			Meteorites.push_back(meteorite);
		}

		for (int i = 0; i < Meteorites.size(); i++)
		{
			if (Meteorites[i] != nullptr)
			{
				Meteorites[i]->movement();
			}
		}
	}

	void Background::destroyMybullets(int& i)
	{
		delete MyBullets[i];
		MyBullets[i] = nullptr;
		nullptrMyBulletsIndex.push_back(i);
	}

	void Background::destroyMeteories(int& i)
	{
		delete Meteorites[i];
		Meteorites[i] = nullptr;
		nullptrMeteoIndex.push_back(i);
	}

	void Background::destroyEnemies(int& i)
	{
		delete Enemies[i];
		Enemies[i] = nullptr;
		nullptrEnemyIndex.push_back(i);
	}

	void Background::destroyEnemyBullets(int& i)
	{
		delete EnemyBullets[i];
		EnemyBullets[i] = nullptr;
		nullptrEnemyBulletsIndex.push_back(i);
	}

	void Background::destroyExplosion(int& i)
	{
		delete Explosions[i];
		Explosions[i] = nullptr;
		nullptrExplosionsIndex.push_back(i);
	}

	void Background::destroyUpgrade()
	{
		delete pUpgrade;
		pUpgrade = nullptr;
	}

	void Background::destroyHints()
	{
		delete pHints;
		pHints = nullptr;
	}

	void Background::destroyMyship()
	{
		MyshipLastDieTime = Simple2D::GetGameTime();
		pHints->increLives(-1);
		delete pship;
		pship = nullptr;
	}

	void Background::destroyAllMybullets()
	{
		for (int i = 0; i < MyBullets.size(); i++)
		{
			delete MyBullets[i];
			MyBullets[i] = nullptr;
		}

	}

	void Background::destroyAllMeteories()
	{
		for (int i = 0; i < Meteorites.size(); i++)
		{
			if (Meteorites[i])
			{
				//when meteorites being destroyed, release resources.
				int type = 2;
				float posX = Meteorites[i]->getPosx();
				float posY = Meteorites[i]->getPosy();
				createExplosions(type, posX, posY);
			}
			delete Meteorites[i];
			Meteorites[i] = nullptr;
		}
	}

	void Background::destroyAllEnemies()
	{
		for (int i = 0; i < Enemies.size(); i++)
		{

			if (Enemies[i])
			{
				//when enemies being destroyed, release resources.
				int type = 2;
				float posX = Enemies[i]->getPosx();
				float posY = Enemies[i]->getPosy();
				createExplosions(type, posX, posY);
			}
			delete Enemies[i];
			Enemies[i] = nullptr;
		}
	}

	void Background::destroyAllEnemyBullets()
	{
		for (int i = 0; i < EnemyBullets.size(); i++)
		{
			delete EnemyBullets[i];
			EnemyBullets[i] = nullptr;
		}
	}

	void Background::destroyAllExplosion()
	{
		for (int i = 0; i < Explosions.size(); i++)
		{
			delete Explosions[i];
			Explosions[i] = nullptr;
		}
	}

	void Background::collisionDetection()
	{
		 collisionMyshipAndMeteo();
		 collisionMyshipAndEnemy();
		 collisionMyshipAndEnemyBullet();
		 collisionMybulletAndMeteo();
		 collisionMybulletAndEnemy();
		 collisionMyshipAndUpgrade();
	}

	void Background::collisionMyshipAndUpgrade()
	{
		if (pUpgrade != nullptr && pship != nullptr)
		{
			float shipPosx = pship->getPosx();
			float shipPosy = pship->getPosy();
			float shipWidth = pship->getWidth() / 2;
			float shipHeight = pship->getHeight() / 2;
			float shipRight = shipPosx + shipWidth;
			float shipLeft = shipPosx - shipWidth;
			float shipTop = shipPosy + shipHeight;
			float shipBot = shipPosy - shipHeight;
			int curtype = pship->getType();

			float upgradePosx = pUpgrade->getPosx();
			float upgradePosy = pUpgrade->getPosy();
			float upgradeWdith = pUpgrade->getWidth() / 2;
			float upgradeHeight = pUpgrade->getHeight() / 2;
			float upgradeRight = upgradePosx + upgradeWdith;
			float upgradeLeft = upgradePosx - upgradeWdith;
			float upgradeTop = upgradePosy + upgradeHeight;
			float upgradeBot = upgradePosy - upgradeHeight;

			if (shipRight > upgradeLeft && shipRight < upgradeRight && ((shipTop > upgradeTop && shipBot < upgradeBot) || (shipTop < upgradeTop && shipBot > upgradeBot)
				|| (shipTop > upgradeBot && shipTop < upgradeTop) || (shipBot > upgradeBot && shipBot < upgradeTop))) // right collision
			{

				destroyUpgrade();
				curtype++;
				if (curtype >= 3)
				{
					//if myship on type3, one more upgrade equals one nuclear
					pHints->increNuclear(1);
					curtype = 3;
				}
				pship->upgrade(curtype);

			}
			else if (shipLeft < upgradeRight && shipLeft > upgradeLeft && ((shipTop > upgradeTop && shipBot < upgradeBot) || (shipTop < upgradeTop && shipBot > upgradeBot)
				|| (shipTop > upgradeBot && shipTop < upgradeTop) || (shipBot > upgradeBot && shipBot < upgradeTop))) // left collision
			{
				destroyUpgrade();
				curtype++;
				if (curtype >= 3)
				{
					//if myship on type3, one more upgrade equals one nuclear
					pHints->increNuclear(1);
					curtype = 3;
				}
				pship->upgrade(curtype);
			}
			else if (shipTop > upgradeBot && shipTop < upgradeTop && ((shipLeft > upgradeLeft && shipRight < upgradeRight) || (shipLeft < upgradeLeft && shipRight > upgradeRight)
				|| (shipRight > upgradeLeft && shipRight < upgradeRight) || (shipLeft > upgradeLeft && shipLeft < upgradeRight))) //top collision
			{
				destroyUpgrade();
				curtype++;
				if (curtype >= 3)
				{
					//if myship on type3, one more upgrade equals one nuclear
					pHints->increNuclear(1);
					curtype = 3;
				}
				pship->upgrade(curtype);
			}
			else if (shipBot < upgradeTop && shipBot > upgradeBot && ((shipLeft > upgradeLeft && shipRight < upgradeRight) || (shipLeft < upgradeLeft && shipRight > upgradeRight)
				|| (shipRight > upgradeLeft && shipRight < upgradeRight) || (shipLeft > upgradeLeft && shipLeft < upgradeRight)))// bot collision
			{
				destroyUpgrade();
				curtype++;
				if (curtype >= 3)
				{
					//if myship on type3, one more upgrade equals one nuclear
					pHints->increNuclear(1);
					curtype = 3;
				}
				pship->upgrade(curtype);
			}

		}


	}

	void Background::collisionMyshipAndMeteo()
	{
		if (pship != nullptr)
		{
			int type = 2;
			float shipPosx = pship->getPosx();
			float shipPosy = pship->getPosy();
			float shipWidth = pship->getWidth() / 2;
			float shipHeight = pship->getHeight() / 2;
			float shipRight = shipPosx + shipWidth;
			float shipLeft = shipPosx - shipWidth;
			float shipTop = shipPosy + shipHeight;
			float shipBot = shipPosy - shipHeight;

			for (int i = 0; i < Meteorites.size(); i++)
			{
				if (Meteorites[i] != nullptr)
				{
					float meteoPosx = Meteorites[i]->getPosx();
					float meteoPosy = Meteorites[i]->getPosy();
					float meteoWidth= Meteorites[i]->getWidth() / 2;
					float meteoHeight= Meteorites[i]->getHeight() / 2;
					float meteoRight = meteoPosx + meteoWidth;
					float meteoLeft = meteoPosx - meteoWidth;
					float meteoTop = meteoPosy + meteoHeight;
					float meteoBot = meteoPosy - meteoHeight;
					if (shipRight > meteoLeft && shipRight < meteoRight && ((shipTop > meteoTop && shipBot < meteoBot) || (shipTop < meteoTop && shipBot > meteoBot)
						|| (shipTop > meteoBot && shipTop < meteoTop) || (shipBot > meteoBot && shipBot < meteoTop))) // right collision
					{
						if (pship)
						{
							//if ship is invincible, then destryoe meteorites, otherwise destroy myship
							if (pship->isInvincible())
								destroyMeteories(i);
							else
							{
								destroyMyship();
							}
							createExplosions(type, shipRight, shipPosy);
						}
					}
					else if (shipLeft < meteoRight && shipLeft > meteoLeft && ((shipTop > meteoTop && shipBot < meteoBot) || (shipTop < meteoTop && shipBot > meteoBot)
						|| (shipTop > meteoBot && shipTop < meteoTop) || (shipBot > meteoBot && shipBot < meteoTop))) // left collision
					{
						if (pship)
						{
							if (pship->isInvincible())
								destroyMeteories(i);
							else
							{
								
								destroyMyship();
							}
							createExplosions(type, shipLeft, shipPosy);
						}
					}
					else if (shipTop > meteoBot && shipTop < meteoTop && ((shipLeft > meteoLeft && shipRight < meteoRight) || (shipLeft < meteoLeft && shipRight > meteoRight)
						|| (shipRight > meteoLeft && shipRight < meteoRight) || (shipLeft > meteoLeft && shipLeft < meteoRight))) //top collision
					{
						if (pship)
						{
							if (pship->isInvincible())
								destroyMeteories(i);
							else
							{
								
								destroyMyship();
							}
							createExplosions(type, shipPosx, shipTop);
						}
					}
					else if (shipBot < meteoTop && shipBot > meteoBot && ((shipLeft > meteoLeft && shipRight < meteoRight) || (shipLeft < meteoLeft && shipRight > meteoRight)
						|| (shipRight > meteoLeft && shipRight < meteoRight) || (shipLeft > meteoLeft && shipLeft < meteoRight)))// bot collision
					{
						if (pship)
						{
							if (pship->isInvincible())
								destroyMeteories(i);
							else
							{
								
								destroyMyship();
							}
							createExplosions(type, shipPosx, shipBot);
						}
					}

				}
			}
		}
	}

	void Background::collisionMyshipAndEnemy()
	{
		if (pship != nullptr)
		{
			int type = 2;
			float shipPosx = pship->getPosx();
			float shipPosy = pship->getPosy();
			float shipWidth = pship->getWidth() / 2;
			float shipHeight = pship->getHeight() / 2;
			float shipRight = shipPosx + shipWidth;
			float shipLeft = shipPosx - shipWidth;
			float shipTop = shipPosy + shipHeight;
			float shipBot = shipPosy - shipHeight;

			for (int i = 0; i < Enemies.size(); i++)
			{
				if (Enemies[i] != nullptr)
				{
					float enemyPosx = Enemies[i]->getPosx();
					float enemyPosy = Enemies[i]->getPosy();
					float enemyWidth = Enemies[i]->getWidth() / 2;
					float enemyHeight = Enemies[i]->getHeight() / 2;
					float enemyRight = enemyPosx + enemyWidth;
					float enemyLeft = enemyPosx - enemyWidth;
					float enemyTop = enemyPosy + enemyHeight;
					float enemyBot = enemyPosy - enemyHeight;
					if (shipRight > enemyLeft && shipRight < enemyRight && ((shipTop > enemyTop && shipBot < enemyBot) || (shipTop < enemyTop && shipBot > enemyBot)
						|| (shipTop > enemyBot && shipTop < enemyTop) || (shipBot > enemyBot && shipBot < enemyTop))) // right collision
					{

						if (pship)
						{
							//if ship is invincible, then destryoe enemies, otherwise destroy myship
							if (pship->isInvincible())
								destroyEnemies(i);
							else
							{
								destroyMyship();
							}
							createExplosions(type, shipRight, shipPosy);
						}
					}
					else if (shipLeft < enemyRight && shipLeft > enemyLeft && ((shipTop > enemyTop && shipBot < enemyBot) || (shipTop < enemyTop && shipBot > enemyBot)
						|| (shipTop > enemyBot && shipTop < enemyTop) || (shipBot > enemyBot && shipBot < enemyTop))) // left collision
					{
						if (pship)
						{
							if (pship->isInvincible())
								destroyEnemies(i);
							else
							{

								destroyMyship();
							}
							createExplosions(type, shipLeft, shipPosy);
						}
					}
					else if (shipTop > enemyBot && shipTop < enemyTop && ((shipLeft > enemyLeft && shipRight < enemyRight) || (shipLeft < enemyLeft && shipRight > enemyRight)
						|| (shipRight > enemyLeft && shipRight < enemyRight) || (shipLeft > enemyLeft && shipLeft < enemyRight))) //top collision
					{
						if (pship)
						{
							if (pship->isInvincible())
								destroyEnemies(i);
							else
							{

								destroyMyship();
							}
							createExplosions(type, shipPosx, shipTop);
						}
					}
					else if (shipBot < enemyTop && shipBot > enemyBot && ((shipLeft > enemyLeft && shipRight < enemyRight) || (shipLeft < enemyLeft && shipRight > enemyRight)
						|| (shipRight > enemyLeft && shipRight < enemyRight) || (shipLeft > enemyLeft && shipLeft < enemyRight)))// bot collision
					{
						if (pship)
						{
							if (pship->isInvincible())
								destroyEnemies(i);
							else
							{
								destroyMyship();
							}
							createExplosions(type, shipPosx, shipBot);
						}
					}

				}
			}
		}
	}

	void Background::collisionMyshipAndEnemyBullet()
	{
		if (pship != nullptr)
		{
			int type = 2;
			float shipPosx = pship->getPosx();
			float shipPosy = pship->getPosy();
			float shipWidth = pship->getWidth() / 2;
			float shipHeight = pship->getHeight() / 2;
			float shipRight = shipPosx + shipWidth;
			float shipLeft = shipPosx - shipWidth;
			float shipTop = shipPosy + shipHeight;
			float shipBot = shipPosy - shipHeight;

			for (int i = 0; i < EnemyBullets.size(); i++)
			{
				if (EnemyBullets[i] != nullptr)
				{
					float enemyBulletPosx = EnemyBullets[i]->getPosx();
					float enemyBulletPosy = EnemyBullets[i]->getPosy();
					float enemyBulletWidth = EnemyBullets[i]->getWidth() / 2;
					float enemyBulletHeight = EnemyBullets[i]->getHeight() / 2;
					float enemyBulletRight = enemyBulletPosx + enemyBulletWidth;
					float enemyBulletLeft = enemyBulletPosx - enemyBulletWidth;
					float enemyBulletTop = enemyBulletPosy + enemyBulletHeight;
					float enemyBulletBot = enemyBulletPosy - enemyBulletHeight;
					if (shipRight > enemyBulletLeft && shipRight < enemyBulletRight && ((shipTop > enemyBulletTop && shipBot < enemyBulletBot) || (shipTop < enemyBulletTop && shipBot > enemyBulletBot)
						|| (shipTop > enemyBulletBot && shipTop < enemyBulletTop) || (shipBot > enemyBulletBot && shipBot < enemyBulletTop))) // right collision
					{
						destroyEnemyBullets(i);
						if (pship && !pship->isInvincible())
						{
							createExplosions(type, shipRight, shipPosy);
							destroyMyship();
						}
					}
					else if (shipLeft < enemyBulletRight && shipLeft > enemyBulletLeft && ((shipTop > enemyBulletTop && shipBot < enemyBulletBot) || (shipTop < enemyBulletTop && shipBot > enemyBulletBot)
						|| (shipTop > enemyBulletBot && shipTop < enemyBulletTop) || (shipBot > enemyBulletBot && shipBot < enemyBulletTop))) // left collision
					{
						destroyEnemyBullets(i);
						if (pship && !pship->isInvincible())
						{
							createExplosions(type, shipLeft, shipPosy);
							destroyMyship();
						}
					}
					else if (shipTop > enemyBulletBot && shipTop < enemyBulletTop && ((shipLeft > enemyBulletLeft && shipRight < enemyBulletRight) || (shipLeft < enemyBulletLeft && shipRight > enemyBulletRight)
						|| (shipRight > enemyBulletLeft && shipRight < enemyBulletRight) || (shipLeft > enemyBulletLeft && shipLeft < enemyBulletRight))) //top collision
					{
						destroyEnemyBullets(i);
						if (pship && !pship->isInvincible())
						{
							createExplosions(type, shipPosx, shipTop);
							destroyMyship();
						}
					}
					else if (shipBot < enemyBulletTop && shipBot > enemyBulletBot && ((shipLeft > enemyBulletLeft && shipRight < enemyBulletRight) || (shipLeft < enemyBulletLeft && shipRight > enemyBulletRight)
						|| (shipRight > enemyBulletLeft && shipRight < enemyBulletRight) || (shipLeft > enemyBulletLeft && shipLeft < enemyBulletRight)))// bot collision
					{
						destroyEnemyBullets(i);
						if (pship && !pship->isInvincible())
						{
							createExplosions(type, shipPosx, shipBot);
							destroyMyship();
						}
					}

				}
			}
		}

	}

	void Background::collisionMybulletAndEnemy()
	{

		for (int i = 0; i < MyBullets.size(); i++)
		{
			if (MyBullets[i] != nullptr)
			{
				int type1 = 1;
				float bulletPosx = MyBullets[i]->getPosx();
				float bulletPosy = MyBullets[i]->getPosy();
				float bulletWidth = MyBullets[i]->getWidth() / 2;
				float bulletHeight = MyBullets[i]->getHeight() / 2;
				float bulletRight = bulletPosx + bulletWidth;
				float bulletLeft = bulletPosx - bulletWidth;
				float bulletTop = bulletPosy + bulletHeight;
				float bulletBot = bulletPosy - bulletHeight;

				for (int j = 0; j < Enemies.size(); j++)
				{
					if (Enemies[j] != nullptr)
					{
						int type2 = 2;
						float enemyPosx = Enemies[j]->getPosx();
						float enemyPosy = Enemies[j]->getPosy();
						float enemyWidth = Enemies[j]->getWidth() / 2;
						float enemyHeight = Enemies[j]->getHeight() / 2;
						float enemyRight = enemyPosx + enemyWidth;
						float enemyLeft = enemyPosx - enemyWidth;
						float enemyTop = enemyPosy + enemyHeight;
						float enemyBot = enemyPosy - enemyHeight;
						if (bulletRight > enemyLeft && bulletRight < enemyRight && ((bulletTop > enemyTop && bulletBot < enemyBot) || (bulletTop < enemyTop && bulletBot > enemyBot)
							|| (bulletTop > enemyBot && bulletTop < enemyTop) || (bulletBot > enemyBot && bulletBot < enemyTop))) // right collision
						{
							createExplosions(type1, bulletRight, bulletPosy);
							destroyMybullets(i);
							Enemies[j]->increHitCount(1);
							if (Enemies[j]->getHitCount() >= Enemies[j]->getMaxHit())
							{
								createExplosions(type2, enemyPosx, enemyPosy);
								pHints->increScores(Enemies[j]->getMaxHit() * 10);
								destroyEnemies(j);
							}
						}
						else if (bulletLeft < enemyRight && bulletLeft > enemyLeft && ((bulletTop > enemyTop && bulletBot < enemyBot) || (bulletTop < enemyTop && bulletBot > enemyBot)
							|| (bulletTop > enemyBot && bulletTop < enemyTop) || (bulletBot > enemyBot && bulletBot < enemyTop))) // left collision
						{
							createExplosions(type1, bulletLeft, bulletPosy);
							destroyMybullets(i);
							Enemies[j]->increHitCount(1);
							if (Enemies[j]->getHitCount() >= Enemies[j]->getMaxHit())
							{
								createExplosions(type2, enemyPosx, enemyPosy);
								pHints->increScores(Enemies[j]->getMaxHit() * 10);
								destroyEnemies(j);
							}
						}
						else if (bulletTop > enemyBot && bulletTop < enemyTop && ((bulletLeft > enemyLeft && bulletRight < enemyRight) || (bulletLeft < enemyLeft && bulletRight > enemyRight)
							|| (bulletRight > enemyLeft && bulletRight < enemyRight) || (bulletLeft > enemyLeft && bulletLeft < enemyRight))) //top collision
						{
							createExplosions(type1, bulletTop, bulletPosx);
							destroyMybullets(i);
							Enemies[j]->increHitCount(1);
							if (Enemies[j]->getHitCount() >= Enemies[j]->getMaxHit())
							{
								createExplosions(type2, enemyPosx, enemyPosy);
								pHints->increScores(Enemies[j]->getMaxHit() * 10);
								destroyEnemies(j);
							}
						}
						else if (bulletBot < enemyTop && bulletBot > enemyBot && ((bulletLeft > enemyLeft && bulletRight < enemyRight) || (bulletLeft < enemyLeft && bulletRight > enemyRight)
							|| (bulletRight > enemyLeft && bulletRight < enemyRight) || (bulletLeft > enemyLeft && bulletLeft < enemyRight)))// bot collision
						{
							createExplosions(type1, bulletBot, bulletPosx);
							destroyMybullets(i);
							Enemies[j]->increHitCount(1);
							if (Enemies[j]->getHitCount() >= Enemies[j]->getMaxHit())
							{
								createExplosions(type2, enemyPosx, enemyPosy);
								pHints->increScores(Enemies[j]->getMaxHit() * 10);
								destroyEnemies(j);
							}
						}

					}
				}

			}

		}

	}

	void Background::collisionMybulletAndMeteo()
	{

		
		for (int i = 0; i < MyBullets.size(); i++)
		{
			if (MyBullets[i] != nullptr)
			{
				int type1 = 1;
				float bulletPosx = MyBullets[i]->getPosx();
				float bulletPosy = MyBullets[i]->getPosy();
				float bulletWidth= MyBullets[i]->getWidth() / 2;
				float bulletHeight= MyBullets[i]->getHeight() / 2;
				float bulletRight = bulletPosx + bulletWidth;
				float bulletLeft = bulletPosx - bulletWidth;
				float bulletTop = bulletPosy + bulletHeight;
				float bulletBot = bulletPosy - bulletHeight;

				for (int j = 0; j < Meteorites.size(); j++)
				{
					if (Meteorites[j] != nullptr)
					{
						int type2 = 2;
						float meteoPosx = Meteorites[j]->getPosx();
						float meteoPosy = Meteorites[j]->getPosy();
						float meteoWidth = Meteorites[j]->getWidth() / 2;
						float meteoHeight = Meteorites[j]->getHeight() / 2;
						float meteoRight = meteoPosx + meteoWidth;
						float meteoLeft = meteoPosx - meteoWidth;
						float meteoTop = meteoPosy + meteoHeight;
						float meteoBot = meteoPosy - meteoHeight;
						if (bulletRight > meteoLeft && bulletRight < meteoRight && ((bulletTop > meteoTop && bulletBot < meteoBot) || (bulletTop < meteoTop && bulletBot > meteoBot)
							|| (bulletTop > meteoBot && bulletTop < meteoTop) || (bulletBot > meteoBot && bulletBot < meteoTop))) // right collision
						{
							
							createExplosions(type1, bulletRight, bulletPosy);
							destroyMybullets(i);
							Meteorites[j]->increHitCount(1);
							if (Meteorites[j]->getHitCount() >= Meteorites[j]->getMaxHit())
							{
								createExplosions(type2, meteoPosx, meteoPosy);
								pHints->increScores(Meteorites[j]->getMaxHit() );
								destroyMeteories(j);
							}
						}
						else if (bulletLeft < meteoRight && bulletLeft > meteoLeft && ((bulletTop > meteoTop && bulletBot < meteoBot) || (bulletTop < meteoTop && bulletBot > meteoBot)
							|| (bulletTop > meteoBot && bulletTop < meteoTop) || (bulletBot > meteoBot && bulletBot < meteoTop))) // left collision
						{
							createExplosions(type1, bulletLeft, bulletPosy);
							destroyMybullets(i);
							Meteorites[j]->increHitCount(1);
							if (Meteorites[j]->getHitCount() >= Meteorites[j]->getMaxHit())
							{
								createExplosions(type2, meteoPosx, meteoPosy);
								pHints->increScores(Meteorites[j]->getMaxHit() );
								destroyMeteories(j);
							}
						}
						else if (bulletTop > meteoBot && bulletTop < meteoTop && ((bulletLeft > meteoLeft && bulletRight < meteoRight) || (bulletLeft < meteoLeft && bulletRight > meteoRight)
							|| (bulletRight > meteoLeft && bulletRight < meteoRight) || (bulletLeft > meteoLeft && bulletLeft < meteoRight))) //top collision
						{
							createExplosions(type1, bulletTop, bulletPosx);
							destroyMybullets(i);
							Meteorites[j]->increHitCount(1);
							if (Meteorites[j]->getHitCount() >= Meteorites[j]->getMaxHit())
							{
								createExplosions(type2, meteoPosx, meteoPosy);
								pHints->increScores(Meteorites[j]->getMaxHit() );
								destroyMeteories(j);
							}
						}
						else if (bulletBot < meteoTop && bulletBot > meteoBot && ((bulletLeft > meteoLeft && bulletRight < meteoRight) || (bulletLeft < meteoLeft && bulletRight > meteoRight)
							|| (bulletRight > meteoLeft && bulletRight < meteoRight) || (bulletLeft > meteoLeft && bulletLeft < meteoRight)))// bot collision
						{
							createExplosions(type1, bulletBot, bulletPosx);
							destroyMybullets(i);
							Meteorites[j]->increHitCount(1);
							if (Meteorites[j]->getHitCount() >= Meteorites[j]->getMaxHit())
							{
								createExplosions(type2, meteoPosx, meteoPosy);
								pHints->increScores(Meteorites[j]->getMaxHit());
								destroyMeteories(j);
							}
						}

					}
				}

			}

		}

	}

	void Background::resumeGame()
	{
		pressSpace = 0;
		if(pship!=nullptr)
		pship->resumeGame();
	}

	void Background::gameSpeedAdjust()
	{
		
		if(  Simple2D::IsKeyPressed(Simple2D::KEY_F1) || Simple2D::IsKeyPressed(Simple2D::KEY_F2))
		{

			if (Simple2D::IsKeyPressed(Simple2D::KEY_F1))
			{
				gameMainSpeed--;
					if (gameMainSpeed <= 4) gameMainSpeed = 4;
			}
			if (Simple2D::IsKeyPressed(Simple2D::KEY_F2))
			{
				gameMainSpeed++;
					if (gameMainSpeed >= 15) gameMainSpeed = 15;
			}

			bulletSpeed = 2 * gameMainSpeed;
			minMeteoSpeed = gameMainSpeed - 2;
			if (minMeteoSpeed <= 2) minMeteoSpeed = 2;
			maxMeteoSpeed = gameMainSpeed + 2;
			if (maxMeteoSpeed >= 17) maxMeteoSpeed = 17;

			
			minEnemySpeed = gameMainSpeed - 2;
			if (minEnemySpeed <= 2) minEnemySpeed = 2;
			maxEnemySpeed = gameMainSpeed + 2;
			if (maxEnemySpeed >= 17) maxEnemySpeed = 17;

			myShipSpeed = gameMainSpeed;
			upgradeSpeed = gameMainSpeed;

			for (int i = 0; i < Meteorites.size(); i++)
			{
				if(Meteorites[i] != nullptr)
				Meteorites[i]->setSpeed(minMeteoSpeed, maxMeteoSpeed);
			}

			for (int i = 0; i < MyBullets.size(); i++)
			{
				if (MyBullets[i] != nullptr)
				MyBullets[i]->setSpeed(bulletSpeed);
			}

			for (int i = 0; i < EnemyBullets.size(); i++)
			{
				if (EnemyBullets[i] != nullptr)
				EnemyBullets[i]->setSpeed(bulletSpeed);
			}

			for (int i = 0; i < Enemies.size(); i++)
			{
				if (Enemies[i] != nullptr)
				Enemies[i]->setSpeed(minEnemySpeed, maxEnemySpeed);
			}
			if (pship != nullptr)
			pship->setSpeed(myShipSpeed, myShipSpeed);
			if (pUpgrade != nullptr)
			pUpgrade->setSpeed(upgradeSpeed);
		}

		CPUscaleChange();

	}

	void Background::CPUscaleChange()
	{
	
		if (Simple2D::IsKeyPressed(Simple2D::KEY_F11))
		{
			if (speedScale == 1) speedScale = 0.05;
			else speedScale = 1;

			for (int i = 0; i < Meteorites.size(); i++)
			{
				if (Meteorites[i] != nullptr)
					Meteorites[i]->setSpeedScale(speedScale);
			}

			for (int i = 0; i < MyBullets.size(); i++)
			{
				if (MyBullets[i] != nullptr)
					MyBullets[i]->setSpeedScale(speedScale);
			}

			for (int i = 0; i < EnemyBullets.size(); i++)
			{
				if (EnemyBullets[i] != nullptr)
					EnemyBullets[i]->setSpeedScale(speedScale);
			}

			for (int i = 0; i < Enemies.size(); i++)
			{
				if (Enemies[i] != nullptr)
					Enemies[i]->setSpeedScale(speedScale);
			}

			if(pship != nullptr)
			pship->setSpeedScale(speedScale);
			if(pUpgrade !=nullptr)
			pUpgrade->setSpeedScale(speedScale);

		}
	
	}

	void Background::useNuclear()
	{
		if (  Simple2D::IsKeyPressed(KEY_N)   )
		{
			if (pship && pHints->getNuclear() > 0)
			{
				pHints->increNuclear(-1);
				destroyAllMeteories();
				destroyAllEnemies();
				destroyAllEnemyBullets();

			}
		}

	}

	void Background::adjustDifficultWithTime()
	{
		if (Simple2D::GetGameTime()-gameTime > difficultyBase * 30)
		{
			enemyFireSpeed -= 0.2;
			if (enemyFireSpeed < 0.35) enemyFireSpeed = 0.35;
			enemySpawnSpeed -= 0.1;
			if (enemySpawnSpeed < 0.15) enemySpawnSpeed = 0.15;
			meteoSpawnSpeed -= 0.1;
			if (meteoSpawnSpeed) meteoSpawnSpeed = 0.15;
			pHints->increLevel(1);
			difficultyBase++;
		}
	}

	void Background::getSize()
	{
		pWidth = (int*)malloc(sizeof(int));
		pHeight = (int*)malloc(sizeof(int));
		if (pImageLayout1)
			Simple2D::GetImageSize(pImageLayout1, pWidth, pHeight);
	}

	int Background::getRandomNumber(int a, int b)
	{
		return (rand() % (b - a + 1)) + a;
	}
	
}

#ifdef TEST_BACKGROUND
int main()
{



	return 0;
}
#endif

