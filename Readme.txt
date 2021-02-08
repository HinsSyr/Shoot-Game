IDE: Visual Studio 2019
CPU: I5-8400, 6 cores, 2.8GHZ

Compile step: 
	1. Open /Projects/VS_2019/ShooterGame.sln
	2. Rebuild solution or press F5
	3. Enter the game

Game rules:
	1. In menu, press SPACE to start the game
	2. Control the spaceship by WASD or ARROW
	3. Press SPACE for shooting.
	4. Press N for using nuclear clean all enemies and meteorites.
	5. Meteorites scores are 1, 2,3,4
        6. Enemies scores are 10,20,30
	7. When getting every 2000 scores, live plus one.
	8. When gettting upgrade on highest, nuclear plus one.
	9. Game end and press ESC back to the menu.
	
Game hotkeys:
	1. press P for pause the game.
	2. press F1 to slow downthe game.
	3. press F2 to speed up the game.
	4. press F11 to change the objects move speed from two mode.(see remaining issues 1)
	


Remaining issues:
  I coded on my PC and everything worked good, when i tested on my laptop, some issues came up:
	1. The objects move significantly fast on laptop, so i add an coefficient on object movement to slower it down.
	   Press F11 turn it on if it runs super fast on your computer. 
	   I think it might caused by different CPU, the game FPS goes out of 60.
	   For reference, my laptop CPU is I7-8550U, 8 cores, 1.8GHZ
	2. The screen size is super small on my laptop however it is good on my PC. 
	   Even though i lower down the input screen paraments in the code.
	3. The game memory usage is steadily at 40M-70M on my PC
 	   However in my laptop, it increases to 100M,200M,300M
