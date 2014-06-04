#include "arenas.h"

using namespace std;

contactListener contact_handler;

void makeArena(const int &n)
{
	Log("makeArena called, building arena %d\n", n);

	if (n == 0)
	{
		current_arena = 0;
		Log("&myPlayerFoot before = %p\nmyPlayer = %p\n", myPlayerFoot, myPlayer);
		myPlayer = addPlayer(350.0f, -350.0f, player_width, player_height, world, myGun, myPlayerFoot);
		Log("&myPlayerFoot after = %p\nmyPlayer = %p\n", myPlayerFoot, myPlayer);
		myPlayer->SetUserData((void *)((char *)"player"));

		gameFloor = addRect(xres * 5.0f, 0.0f, xres*10.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"floor portalable");
		gameFloor->SetAwake(false);

		addRect(0.0f, -0.500f*yres, 50.0f, 1.0f*yres, 0.0f, 0.2f, 2, (char *)"lower third left wall")->SetAwake(false);
		addRect(0.0f, -1.50f*yres, 50.0f, 1.5f*yres, 0.0f, 0.2f, 2, (char *)"middle third left wall portalable")->SetAwake(false);
		addRect(0.0f, -2.5f*yres, 50.0f, 1.5f*yres, 0.0f, 0.2f, 2, (char *)"upper third left wall")->SetAwake(false);
		((b2Body *)(addRect(xres*10.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"right wall portalable", 180.0f)))->SetAwake(false);//right wall

		myButton = addRect(5.5f*xres, -28.0f, 100.0f, 50.0f, 0.7f, 0.7f, 2, (char *)"button 1");
		turrets[0].turret = addTurret(b2Vec2(0.0f, -yres), b2Vec2(50.0f, 100.0f), false, 45.0f, 90.0f, world);
		turrets[0].turret->SetUserData((void *)((char *)"turret"));
		turrets[0].max_angle = 135.0f;
		turrets[0].min_angle = 45.0f;
		turrets[0].angleSpeed = 0.10f;
		gunEnemy1 = addGunEnemy(b2Vec2(xres*8.0f, -64.0f), b2Vec2(150, 200), 0, world);
		gunEnemy1->SetUserData((void *)((char *)"enemy left"));
		gunEnemy2 = addGunEnemy(b2Vec2(xres*9.0f, -64.0f), b2Vec2(150, 200), 1, world);
		gunEnemy2->SetUserData((void *)((char *)"enemy"));
		addMirror(b2Vec2(2.0f*xres, -1*yres), b2Vec2(40.0f, 150.0f), 0.0f, world);
		platforms[0].platform = addMovingPlatform(b2Vec2(2.5f*xres, -0.5*yres), b2Vec2(150.0f, 40.0f), world);
		platforms[0].start = platforms[0].platform->GetPosition();
		platforms[0].end = b2Vec2(2.5f*xres*P2M, -1.5*yres*P2M);
		platforms[0].speed = 4.0f;
		platforms[0].active = true;
		platforms[0].direction = (1/getMagnitude(platforms[0].end - platforms[0].start)) * (platforms[0].end - platforms[0].start);
		((b2Body *)(addRect(xres*9.4f, -150.0f, 20.0f, 300.0f, 0.0f, 0.2f, 2, (char *)"end", 180.0f)))->SetAwake(false);// end point

		addObstacles();
	}

	/* add a bionic goat to frolic through level */
	if (n == 1)
	{
		current_arena = 1;
		myPlayer = addPlayer(350.0f, -350.0f, player_width, player_height, world, myGun, myPlayerFoot);
		myPlayer->SetUserData((void *)((char *)"player"));

		gameFloor = addRect(xres * 2.0f, 0.0f, xres*4.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"floor portalable");
		gameFloor->SetAwake(false);
		addRect(xres * 1.5f, -yres*5, xres*3.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"ceiling portalable");

		((b2Body *)(addRect(0.0f, -2.5*yres, 50, yres*5, 0.0f, 0.2f, 2, (char *)"left wall")))->SetAwake(false);//left wall
		((b2Body *)(addRect(xres*3.0f, -2.5*yres, 50, yres*5, 0.0f, 0.2f, 2, (char *)"right wall")))->SetAwake(false);//right wall
		((b2Body *)(addRect(xres*9.4f, -150.0f, 20.0f, 300.0f, 0.0f, 0.2f, 2, (char *)"end", 180.0f)))->SetAwake(false);// end point

		//Lens Box
		addRect(200, -yres*4, 400, 50, 0.0f, 0.2f, 2, (char *)"bottom portalable");
		addRect(400, -yres*4 - 85, 50, 170, 0.0f, 0.2f, 2, (char *)"right bottom portable");
		addRect(400, -yres*5 + 105, 50, 170, 0.0f, 0.2f, 2, (char *)"right top portalable");
        addMovingPlatform(b2Vec2(40, -4.5*yres), b2Vec2(75.0f, 200.0f), world)->SetUserData((void *)((char *)"lens 0"));
		//

        addRect(xres * 1.0f, onFloor - 15.0f, 100.0f, 100.0f, 0.9f, 0.2f, 1);//cube1
        addRect(xres * 1.5f, onFloor - 15.0f, 100.0f, 100.0f, 0.9f, 0.2f, 1);//cube2

        //top left turret
		turrets[0].turret = addTurret(b2Vec2(125.0f, -yres*4 + 75), b2Vec2(50.0f, 100.0f), false, 180.0f, 180.0f, world);
		turrets[0].turret->SetUserData((void *)((char *)"turret"));
		turrets[0].max_angle = 180.0f;
		turrets[0].min_angle = 180.0f;
		turrets[0].angleSpeed = 0.0f;
		
		//mirror1
        platforms[0].platform = addMovingPlatform(b2Vec2(150, -1.5*yres), b2Vec2(300.0f, 50.0f), world);
		platforms[0].platform->SetUserData((void *)((char *)"mirror"));
		//platforms[0].start = platforms[0].platform->GetPosition();
		//platforms[0].end = b2Vec2((150)*P2M, (-2.0f*yres)*P2M);
		platforms[0].speed = 0.0f;
		platforms[0].active = true;
		//platforms[0].direction = (1/getMagnitude(platforms[0].end - platforms[0].start)) * (platforms[0].end - platforms[0].start);
		platforms[0].angleActive = true;
		platforms[0].angleSpeed = 0.15f;
		platforms[0].platform->SetAngularVelocity(platforms[0].angleSpeed);
		platforms[0].maxAngle = 45.0f;
		platforms[0].minAngle = 0.0f;

        //mirror2
        platforms[1].platform = addMovingPlatform(b2Vec2(1750, -1.5*yres), b2Vec2(300.0f, 50.0f), world);
		platforms[1].platform->SetUserData((void *)((char *)"mirror"));
		//platforms[1].start = platforms[1].platform->GetPosition();
		//platforms[1].end = b2Vec2((1000)*P2M, (-2.0f*yres)*P2M);
		platforms[1].speed = 0.0f;
		platforms[1].active = true;
		//platforms[1].direction = (1/getMagnitude(platforms[1].end - platforms[1].start)) * (platforms[1].end - platforms[1].start);
		platforms[1].angleActive = true;
		platforms[1].angleSpeed = 0.15f;
		platforms[1].platform->SetAngularVelocity(platforms[1].angleSpeed);
		platforms[1].maxAngle = 0.0f;
		platforms[1].minAngle = -45.0f;
        
        //mirror3
        platforms[5].platform = addMovingPlatform(b2Vec2(1750, -4.5*yres), b2Vec2(300.0f, 50.0f), world);
		platforms[5].platform->SetUserData((void *)((char *)"mirror"));
		//platforms[5].start = platforms[5].platform->GetPosition();
		//platforms[5].end = b2Vec2((1000)*P2M, (-2.0f*yres)*P2M);
		platforms[5].speed = 0.0f;
		platforms[5].active = true;
		//platforms[5].direction = (1/getMagnitude(platforms[5].end - platforms[5].start)) * (platforms[5].end - platforms[5].start);
		platforms[5].angleActive = true;
		platforms[5].angleSpeed = 0.15f;
		platforms[5].platform->SetAngularVelocity(platforms[5].angleSpeed);
		platforms[5].maxAngle = 45.0f;
		platforms[5].minAngle = 0.0f;

        //updown middle
        platforms[2].platform = addMovingPlatform(b2Vec2(600, -1.0*yres), b2Vec2(200.0f, 50.0f), world);
		platforms[2].platform->SetUserData((void *)((char *)"moving"));
		platforms[2].start = platforms[2].platform->GetPosition();
		platforms[2].end = b2Vec2((600)*P2M, (-4.5f*yres)*P2M);
		platforms[2].speed = 5.0f;
		platforms[2].active = true;
		platforms[2].direction = (1/getMagnitude(platforms[2].end - platforms[2].start)) * (platforms[2].end - platforms[2].start);
        
        //downup
        platforms[3].platform = addMovingPlatform(b2Vec2(800, -4.5*yres), b2Vec2(200.0f, 50.0f), world);
		platforms[3].platform->SetUserData((void *)((char *)"moving"));
		platforms[3].start = platforms[3].platform->GetPosition();
		platforms[3].end = b2Vec2((800)*P2M, (-0.5f*yres)*P2M);
		platforms[3].speed = 5.0f;
		platforms[3].active = true;
		platforms[3].direction = (1/getMagnitude(platforms[3].end - platforms[3].start)) * (platforms[3].end - platforms[3].start);
        
        //updown middle
        platforms[4].platform = addMovingPlatform(b2Vec2(1000, -0.0*yres), b2Vec2(200.0f, 50.0f), world);
		platforms[4].platform->SetUserData((void *)((char *)"moving"));
		platforms[4].start = platforms[4].platform->GetPosition();
		platforms[4].end = b2Vec2((1000)*P2M, (-4.5f*yres)*P2M);
		platforms[4].speed = 5.0f;
		platforms[4].active = true;
		platforms[4].direction = (1/getMagnitude(platforms[4].end - platforms[4].start)) * (platforms[4].end - platforms[4].start);
        
	}
	/* add companion cube */
	if (n == 2)
	{
		current_arena = 2;
		myPlayer = addPlayer(350.0f, -350.0f, player_width, player_height, world, myGun, myPlayerFoot);
		myPlayer->SetUserData((void *)((char *)"player"));

		gameFloor = addRect(xres * 5.0f, 0.0f, xres*10.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"floor portalable");
		gameFloor->SetAwake(false);

		((b2Body *)(addRect(0.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"left wall portalable")))->SetAwake(false);//left wall
		((b2Body *)(addRect(xres*10.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"right wall portalable")))->SetAwake(false);//right wall
		((b2Body *)(addRect(xres*9.4f, -150.0f, 20.0f, 300.0f, 0.0f, 0.2f, 2, (char *)"end", 180.0f)))->SetAwake(false);// end point
		addRect(xres * 1.0f + 65.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//bottom right
	}
	/* spikes */
	if (n == 3)
	{
		current_arena = 3;
		myPlayer = addPlayer(310.0f, -1.87f * yres, player_width, player_height, world, myGun, myPlayerFoot);
		myPlayer->SetUserData((void *)((char *)"player"));

		gameFloor = addRect(xres * 5.0f + 400.0f, 0.0f, xres*10.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"main floor 2 portalable");
		gameFloor->SetAwake(false);

		((b2Body *)(addRect(425.0f, (-2.45f*yres), 50.0f, yres*0.8f, 0.0f, 0.2f, 2, (char *)"left wall 3 portalable")))->SetAwake(false);// left wall 3
		((b2Body *)(addRect(425.0f, (-0.7f*yres), 50.0f, yres*1.3f, 0.0f, 0.2f, 2, (char *)"left wall 2 portalable")))->SetAwake(false);// left wall 2
		((b2Body *)(addRect(25.0f, (-1.70f*yres), 50.0f, yres*0.5f, 0.0f, 0.2f, 2, (char *)"left wall 1 portalable")))->SetAwake(false);// left wall 1
		((b2Body *)(addRect(225.0f, (-1.4f*yres), 450.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"left floor 1 portalable")))->SetAwake(false);// left floor 1
		((b2Body *)(addRect(225.0f, (-2.0f*yres), 450.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"ceiling 0 portalable")))->SetAwake(false);// ceiling 0
		((b2Body *)(addRect(725.0f, (-2.8f*yres), 600.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"ceiling 1 portalable")))->SetAwake(false);// ceiling 1
		((b2Body *)(addRect(2100.0f, (-2.8f*yres), 2400.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"ceiling 2")))->SetAwake(false);// ceiling 2
		((b2Body *)(addRect(1100.0f, (-1.1f*yres), 50.0f, yres*2.2f, 0.0f, 0.2f, 2, (char *)"wall 4 portalable")))->SetAwake(false);// wall 4
		((b2Body *)(addRect(1375.0f, (-50.0f), 550.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"spike 1 deadly")))->SetAwake(false);// spike floor 1
		((b2Body *)(addRect(2225.0f, (-50.0f), 550.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"spike 2 deadly")))->SetAwake(false);// spike floor 2

		((b2Body *)(addRect(2500.0f, (-1.1f*yres), 50.0f, yres*2.2f, 0.0f, 0.2f, 2, (char *)"wall 5 portalable")))->SetAwake(false);// wall 5
		((b2Body *)(addRect(3475.0f, (-1.8f*yres), 300.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"floor 3")))->SetAwake(false);// floor 3
		((b2Body *)(addRect(3600.0f, (-2.1f*yres), 50.0f, yres*1.25f, 0.0f, 0.2f, 2, (char *)"wall 6 portalable")))->SetAwake(false);// wall 6
		turrets[0].turret = addTurret(b2Vec2(2500.0f, -0.4 * yres), b2Vec2(50.0f, 100.0f), false, 45.0f, 90.0f, world);
		turrets[0].turret->SetUserData((void *)((char *)"turret"));
		((b2Body *)(addRect(4750.0f, (-2.8f*yres), 2900.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"ceiling 3 portalable")))->SetAwake(false);// ceiling 3
		((b2Body *)(addRect(4900.0f, (-1.6f*yres), 900.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"right floor 3 portalable")))->SetAwake(false);// right floor 3
		mines[0].mine = addRect(4300, -2.2f*yres, 150.0f, 150.0f, 0.7f, 0.9f, 3, (char *)"mine deadly"); // mine
		((b2Body *)(addRect(xres*9.4f, -150.0f, 20.0f, 300.0f, 0.0f, 0.2f, 2, (char *)"end", 180.0f)))->SetAwake(false);// end point

		((b2Body *)(addRect(xres*8.3f, (-1.4f*yres), 50, yres*2.8f, 0.0f, 0.2f, 2, (char *)"right wall portalable")))->SetAwake(false);//right wall
		addRect(xres * 8.1f + 65.0f, onFloor - 25.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);// a block
		addRect(xres * 8.1f, onFloor - 25.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);// another block
	}
	Log("done!\n");
}

void addObstacles(void)
{
	//top of floor is yres-50-25 = yres-75
	addRect(xres * 1.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//bottomleft of stack
	addRect(xres * 1.0f + 65.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//bottom right
	addRect(xres * 1.0f + 32.5f, onFloor - 20.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//top

	addStairs();

	b2Body * awall;
	awall = addRect(2500.0f, onFloor - 350.0f, 50.0f, 250.0f, 0.7f, 0.7f, 2, (char *)"angled wall portalable top");
	awall->SetTransform((awall->GetPosition()), (-45.0f * D2R));
	awall->SetAwake(false);
	awall = (addRect(2500.0f, onFloor - 300.0f, 50.0f, 250.0f, 0.7f, 0.7f, 2, (char *)"angled wall portalable bottom"));
	awall->SetTransform((awall->GetPosition()), (135.0f * D2R));
	platform = addRect(4.0f*xres, -0.33f*yres, 250, 30, 2.0f, 0.9f, 3, (char *)"platform"); // platform
	mineObject = addRect(1.5f*xres, -0.75f*yres, 150.0f, 150.0f, 0.7f, 0.9f, 3, (char *)"mine deadly"); // mine
	myDoor = addDoor(6*xres, yres-75);
}

void firstInit(void)
{
	Log("initializing world for first game\n");
	world=new b2World(b2Vec2(0.0,10.0f));
	world->SetContactListener(&contact_handler);
}

void restart(const int & a)
{
	Log("restart called, destroying and rebuilding world\n");
	delete world;
	world = NULL;
	for (int i = 0; i < 10; i++)
	{
		turrets[i].turret = NULL;
		doors[i].door = NULL;
		buttons[i].button = NULL;
		mines[i].mine = NULL;
		platforms[i].platform = NULL;
		lens[i].lens = NULL;
	}
	gunEnemy1 = NULL;
	gunEnemy2 = NULL;
	myPlayer = NULL;
	myPlayerFoot = NULL;
	myGun = NULL;
	p_dest = NULL;
	p_obj = NULL;
	gameFloor = NULL;
	platform = NULL;
	p1 = NULL;
	p2 = NULL;
	mineObject = NULL;
	myDoor = NULL;
	carry = NULL;
	player_direction = 1;
	resetDestroyVars();
	Log("vars resset, rebuilding...\n");
	world=new b2World(b2Vec2(0.0,10.0f));
	toDestroy = NULL;
	world->SetContactListener(&contact_handler);
	b2Contact* contacts = world->GetContactList();
		for(int i = 0; i < world->GetContactCount(); i++) {
			contacts->ResetFriction();
			contacts->GetNext();
		}

	makeArena(a);
}

void addStairs(void)
{
	addRect(1200.0f, onFloor + 10.0f, 80.0f, 30.0f, 0.7f, 0.2f, 2);// stairs
	addRect(1280.0f, onFloor, 80.0f, 60.0f, 0.7f, 0.2f, 2);
	addRect(1360.0f, onFloor-15.0f, 80.0f, 90.0f, 0.7f, 0.2f, 2);
	addRect(1440.0f, onFloor-30.0f, 80.0f, 120.0f, 0.7f, 0.2f, 2);
	addRect(1520.0f, onFloor-45.0f, 80.0f, 150.0f, 0.7f, 0.2f, 2);
}
