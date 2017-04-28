#include "GameState.h"
#include "../Utility.h"

GameState::GameState(StateManager* manager, Platform *platform, DataManager *d, Level *level)
	: State(manager, platform)
{
	stateName = "GameState";
	this->mode = mode;

	dtmng = d;
	this->level = level;
	
}

GameState::~GameState()
{

}

bool GameState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	mousePos = Vec2(mouseX, mouseY);
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
		case SDL_QUIT:
			return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				if (!bodyPick)
				{
					for (int i = 0; i < squares.size(); i++)
					{
						if (Collision::pointBoxCollision(mousePos, squares[i]))
						{
							Vec2 pv = player->getCentre();
							Vec2 sv = squares[i]->getCentre();

							//Vec2 spv = pv - sv;
							float dist = Collision::distanceBetween(pv, sv);
							if (dist < 80)
							{
								bodyPick = true;
								bodyPickIndex = i;

								squares[i]->setGravityOn(false);
								squares[i]->velocity = Vec2(0, 0);
							}
						}
					}
				}
				else {
					if (bodyPickIndex != -1)
					{
						letBodyGo();
					}
					

				}
				
				
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				//do same as quit
				
					//stateManager->addState(pms);
					
					stateManager->changeState(new ChooseLevelState(stateManager, platform, dtmng));
					esc = true;
					return false;
				break;
			//temporary movement
			case SDLK_UP:
				kUp = true;
				break;
			case SDLK_DOWN:
				kDown = true;
				break;
			case SDLK_LEFT:
				kLeft = true;
				break;
			case SDLK_RIGHT:
				kRight = true;
				break;
			case SDLK_w:
				kUp = true;
				break;
			case SDLK_s:
				kDown = true;
				break;
			case SDLK_a:
				kLeft = true;
				break;
			case SDLK_d:
				kRight = true;
				break;

			case SDLK_LSHIFT:
				if (!dash)
				{
					if (canDash && canJump)
					{
						dash = true;
					}
					
				}
				break;
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
		

			case SDLK_UP:
				kUp = false;
				break;
			case SDLK_DOWN:
				kDown = false;
				break;
			case SDLK_LEFT:
				kLeft = false;
				break;
			case SDLK_RIGHT:
				kRight = false;
				break;
			case SDLK_w:
				kUp = false;
				break;
			case SDLK_s:
				kDown = false;
				break;
			case SDLK_a:
				kLeft = false;
				break;
			case SDLK_d:
				kRight = false;
				break;

			case SDLK_SPACE:
				if (bodyPick)
				{
					throwBody();
				}
				break;
			default:
				Utility::log(Utility::I, Utility::intToString(events.key.keysym.sym));
				break;
			}
			break;
		}
	}
	return false;
}

void GameState::update(float dt)
{
	player->update(dt);
	currentMap->update(dt);
	Vec2 ppos = player->getPosition();
	Vec2 pdim = player->getDimensions();

	jumphitbox->setPosition(Vec2(ppos.x, ppos.y + pdim.y));
	canJump = false;
	levelTime->update(dt);
	//squares
	for (int i = 0; i < squares.size(); i++)
	{
		squares[i]->update(dt);

		
		m->A = squares[i];

		Vec2 normal = 0;
		float penetration;

		for (int j = 0; j < squares.size(); j++)
		{
			
			m->B = squares[j];
			//Vec2 normal = 0;
			//float penetration;

			//check not comparing to self
			if (squares[i] != squares[j])
			{
				if (Collision::boxBoxCollisionM(m))
				{
			//		Utility::log(Utility::I, "Collide with another square");
					Collision::resolve(m);
					Collision::correctPositions(m);
				}
			}
		}

		currentMap->checkCollideM2(m);


		for (int j = 0; j < circles.size(); j++)
		{

			m->B = circles[j];
			//Vec2 normal = 0;
			//float penetration;

			//check not comparing to self
			if (Collision::circleCircleCollisionM(m))
			{
			//	Utility::log(Utility::I, "Collide with another circle");
				Collision::resolve(m);
				Collision::correctPositions(m);
			}
		}


		m->B = player;

		if (Collision::boxBoxCollisionM(m))
		{
			Collision::resolve(m);
			Collision::correctPositions(m);
			Utility::log(Utility::I, "Collide with player");
		}


		//pressure pad
		/*m->B = pp1;
		if (Collision::boxBoxCollisionM(m))
		{
			Collision::resolve(m);
			Collision::correctPositions(m);
			pp1->setActivate(true);
			//m->A->velocity = 0;
			
		}
		else {
			//pp1->setActivate(false);
		}*/

		m->B = jumphitbox;
		if (Collision::boxBoxCollisionM(m))
		{
			if (m->normal == Vec2(0, -1))
			{
				canJump = true;

			}
			
		}
		

		if (squares[i]->getPosition().y > 540)
		{
			squares[i]->setPosition(Vec2(80, 170));
			squares[i]->velocity = Vec2(0, 0);
		}

	}


	//////
	//circles
	//////
	for (int i = 0; i < circles.size(); i++)
	{
		circles[i]->update(dt);

		Manifold *m = new Manifold();
		m->A = circles[i];

		Vec2 normal = 0;
		float penetration;

		for (int j = 0; j < circles.size(); j++)
		{

			m->B = circles[j];
			//Vec2 normal = 0;
			//float penetration;

			//check not comparing to self
			if (circles[i] != circles[j])
			{
				if (Collision::circleCircleCollisionM(m))
				{
				//	Utility::log(Utility::I, "Collide with another circle");
					Collision::resolve(m);
					Collision::correctPositions(m);
				}
			}
		}

		if (currentMap->checkCollideM2(m))
		{
		//	Utility::log(Utility::I, "Collide with tiles. Normal: X: " + Utility::floatToString(m->normal.x) + " Y: " + Utility::floatToString(m->normal.y) + " Penetration: " + Utility::floatToString(m->penetration) + " Velocity: X  " + Utility::floatToString(m->A->velocity.x) + " Velocity: Y  " + Utility::floatToString(m->A->velocity.y));
			Collision::resolve(m);
			Collision::correctPositions(m);


			//m->A->velocity *= m->normal;


		}

		for (int j = 0; j < squares.size(); j++)
		{

			m->B = squares[j];
			//Vec2 normal = 0;
			//float penetration;

			//check not comparing to self
			if (Collision::boxBoxCollisionM(m))
			{
				//Utility::log(Utility::I, "Collide with another square");
				Collision::resolve(m);
				Collision::correctPositions(m);
			}
		}


		
		m->B = player;

		

		

	}

	m->B = player;

	if (currentMap->checkCollideM2(m))
	{

		//Collision::resolve(m);
		//Collision::correctPositions(m);
		Utility::log(Utility::I, "Collide with tiles. Normal: X: " + Utility::floatToString(m->normal.x) + " Y: " + Utility::floatToString(m->normal.y) + " Penetration: " + Utility::floatToString(m->penetration) + " Velocity: X  " + Utility::floatToString(m->A->velocity.x) + " Velocity: Y  " + Utility::floatToString(m->A->velocity.y));
	}


	//Manifold *m = new Manifold();

	m->A = jumphitbox;

	if (currentMap->checkCollideM(m))
	{
		if (m->normal == Vec2(0, 1))
		{
			canJump = true;
			Utility::log(Utility::I, "Can Jump");
		}
	}
	m->A = player;

	if (currentMap->checkCollideM2(m))
	{

		//Collision::resolve(m);
		//Collision::correctPositions(m);
		Utility::log(Utility::I, "Collide with tiles. Normal: X: " + Utility::floatToString(m->normal.x) + " Y: " + Utility::floatToString(m->normal.y) + " Penetration: " + Utility::floatToString(m->penetration) + " Velocity: X  " + Utility::floatToString(m->A->velocity.x) + " Velocity: Y  " + Utility::floatToString(m->A->velocity.y));
	}

	if (currentMap->lineOfSight(player))
	{
		//Utility::log(Utility::I, "Enemy can see us");
	}
	else {
		Utility::log(Utility::I, "Player is hidden");
	}




	
	//just some testing data for moving the player
	Vec2 curPos = player->getPosition();
	Vec2 movement = Vec2(0);

	

	if (kLeft)
	{
		movement.x = -1;
		//player->velocity = Vec2(-1, 0);
		//power += 0.2 *dt;
	} else
	if (kRight)
	{
		movement.x = 1;
		//player->velocity = Vec2(1, 0);
		//power += 0.2 *dt;
	}
	else {
		//player->velocity.x = 0;
	}

	if (kUp)
	{
		if (canJump)
		{
			player->velocity.y = -180;
		}
		

		//player->velocity = Vec2(0, 1);
		//power += 0.2 *dt;
	}

	if (kDown)
	{
		//movement.y = 1;
		//player->velocity = Vec2(0, -1);
		//power += 0.2 *dt;
	}

	

	//get normal of momentum
	Vec2 normCurPos = movement.normalize();
	float speed = 20;

	Vec2 dir = normCurPos * speed;

	Vec2 newCurPosX = curPos;
	Vec2 newCurPosY = curPos;

	//player->velocity += dir;

	player->velocity += dir;

	int maxSpeed = 240;
	//if (!dash)
	{
		if (player->velocity.x > maxSpeed)
		{
			player->velocity.x = maxSpeed;
		}

		if (player->velocity.x < -maxSpeed)
		{
			player->velocity.x = -maxSpeed;
		}

		if (player->velocity.y > maxSpeed)
		{
			player->velocity.y = maxSpeed;
		}

		if (player->velocity.y < -maxSpeed)
		{
			player->velocity.y = -maxSpeed;
		}

	}
	
	//curPos.x += dir.x;

	//curPos += normCurPos * speed;

	Vec2 diff = normCurPos * speed;

	//Manifold *m = new Manifold();



	//player->setPosition(curPos);




	/*m->B = pp1;
	if (Collision::boxBoxCollisionM(m))
	{
		Collision::resolve(m);
		Collision::correctPositions(m);
		Utility::log(Utility::I, "Collide with player");
		pp1->setActivate(true);
		
	}
	else {
		//pp1->setActivate(false);
	}*/

/*
	if (exitm->getOpen())
	{
		m->B = exitm;
		if (Collision::boxBoxCollisionM(m))
		{
			levelComplete = true;
		}

	}
*/





	
	
	/*if (pp1->getActivate())
	{
		currentMap->changeTileType("O", Vec2(21, 3), "XX", dtmng->getTileTypeManager());
		currentMap->changeTileType("O", Vec2(21, 4), "XX", dtmng->getTileTypeManager());
		currentMap->changeTileType("O", Vec2(21, 5), "XX", dtmng->getTileTypeManager());

		exitm->setOpen(true);
	}
	else {
		currentMap->changeTileType("O", Vec2(21, 3), "VE", dtmng->getTileTypeManager());
		currentMap->changeTileType("O", Vec2(21, 4), "VE", dtmng->getTileTypeManager());
		currentMap->changeTileType("O", Vec2(21, 5), "VE", dtmng->getTileTypeManager());
	}*/



	if (bodyPick)
	{
		//move body with mouse
		Vec2 plPos = player->getCentre();
		Vec2 sqPos = squares[bodyPickIndex]->getCentre();
		Vec2 diffM = mousePos - sqPos;

		float distps = Collision::distanceBetween(plPos, sqPos);

		if (distps < 80)
		{
			Vec2 diffN = diffM.normalize();
			float distsm = Collision::distanceBetween(sqPos, mousePos);
			Utility::log(Utility::I, "Distance between mouse and body" + Utility::floatToString(distsm));

			if (distsm < 115)
			{
				float power = distsm * 2;
				squares[bodyPickIndex]->velocity = diffN * power;
			}
			else {
				letBodyGo();
			}
		}
		else {
			letBodyGo();
		}
	}

	if (dash && canDash)
	{
		dash = false;
		canDash = false;
		//dashTimer = 
		if (kRight)
		{
			player->velocity.x = 250;
		} 
		if (kLeft)
		{
			player->velocity.x = -250;
		}
	}

	if (!canDash)
	{
		if (player->velocity.x <0.3 && player->velocity.x > -0.3)
		{
			canDash = true;
			dash = false;
		} 


	}


	if (currentMap->getLevelComplete() && !writtenToFile)
	{
		level->setFastestTime(levelTime->getTime());
		level->setComplete(true);
		saveLevel();
		writtenToFile = true;
		stateManager->changeState(new ChooseLevelState(stateManager, platform, dtmng));
	}

	

}

void GameState::resolveCollision(Square *a, Square *b)
{

}

void GameState::render()
{
	//pp1->render(platform->getRenderer());
	//exitm->render(platform->getRenderer());
	currentMap->render(platform->getRenderer());

	for (int i = 0; i < squares.size(); i++)
	{
		squares[i]->render(platform->getRenderer());
	}


	//circleTexture->pushSpriteToScreen(platform->getRenderer(), Vec2(40, 40), 0, Vec2(32, 32));

	for (int i = 0; i < circles.size(); i++)
	{
		circles[i]->render(platform->getRenderer());
	}



	player->render(platform->getRenderer());

	levelTime->render(platform->getRenderer());


	
	
}

void GameState::load()
{

	m = new Manifold();

	if (level->getID() == "M01")
	{
		mode = 1;
	}
	if (level->getID() == "M02")
	{
		mode = 2;
	}
	if (level->getID() == "M03")
	{
		mode = 3;
	}
	
	white = new Texture(platform->getRenderer(), 255, 255, 255);

	circleTexture = new Texture("res/img/circle.png", platform->getRenderer());
	squareTexture = new Texture("res/img/square.png", platform->getRenderer());

	pressPadB = new Texture("res/img/pressPadBottom.png", platform->getRenderer());
	pressPadT = new Texture("res/img/pressPadTop.png", platform->getRenderer());

	pressPad = new Texture("res/img/presspad.png", platform->getRenderer());

	//currentMap = new MapRoom(dtmng->getMapManager(), 0, 0);
	//currentMap->createRoom(dtmng->getMapManager(), dtmng->getTileTypeManager(), dtmng->getCreatureManager(), 0, 0, false, 0);

	currentMap = new MapRoom(dtmng->getMapManager(), dtmng->getTileTypeManager(), dtmng->getCreatureManager(), dtmng->getItemManager(), level->getID());

	player = new Character(Vec2(40, 170), dtmng->getCreatureManager()->getCharacterType("P0"));

	player->mass = 1;
	player->setGravityOn(true);




	if (mode == 0)
	{
		//player = new Square(squareTexture, Vec2(40, 40), Vec2(20, 20));
		//player->mass = 0.2;
		//player->mass = 0;

		box = new Square(squareTexture, Vec2(80, 80), Vec2(20, 20));

		box->velocity = Vec2(20, 4);
		box2 = new Square(squareTexture, Vec2(140, 80), Vec2(20, 20));

		box3 = new Square(squareTexture, Vec2(70, 140), Vec2(20, 20));
		box4 = new Square(squareTexture, Vec2(120, 120), Vec2(20, 20));
		box4->velocity = Vec2(-60, 5);
		box5 = new Square(squareTexture, Vec2(90, 210), Vec2(20, 20));

		box6 = new Square(squareTexture, Vec2(145, 210), Vec2(20, 20));

		squares.push_back(box);
		squares.push_back(box2);
		squares.push_back(box3);
		squares.push_back(box4);
		squares.push_back(box5);
		squares.push_back(box6);


		circ = new Circle(circleTexture, Vec2(400, 300), Vec2(32, 32));
		circ2 = new Circle(circleTexture, Vec2(370, 350), Vec2(32, 32));
		circ3 = new Circle(circleTexture, Vec2(425, 400), Vec2(32, 32));
		circ4 = new Circle(circleTexture, Vec2(410, 450), Vec2(32, 32));
		
		circles.push_back(circ);
		circles.push_back(circ2);
		circles.push_back(circ3);
		circles.push_back(circ4);
	}
	else if (mode == 1) {
		//player = new Square(squareTexture, Vec2(40, 170), Vec2(20, 20));


		//CharacterType *ct = dtmng->getCreatureManager()->getCharacterType("P0");
		
		//player->mass = 4;

		box = new Square(squareTexture, Vec2(80, 170), Vec2(20, 20));
		squares.push_back(box);

		

		//496 for full pad
		//pp1 = new PressurePad(pressPad, Vec2(570, 504), Vec2(40, 17));
		//pp1->mass = 0;

		//exitm = new MapExit(white, Vec2(20, 170), Vec2(25, 25));
	}
	else if (mode == 2)
	{

		//player = new Square(squareTexture, Vec2(40, 450), Vec2(20, 20));
		//player->mass = 4;

		box = new Square(squareTexture, Vec2(120, 450), Vec2(20, 20));
		box->setGravityOn(false);
		box2 = new Square(squareTexture, Vec2(480, 170), Vec2(20, 20));
		squares.push_back(box);
		//squares.push_back(box2);

		
	}
	else if (mode == 3)
	{

		//player = new Square(squareTexture, Vec2(40, 450), Vec2(20, 20));
		//player->mass = 4;

		box = new Square(squareTexture, Vec2(80, 450), Vec2(20, 20));
		
		squares.push_back(box);
	}

	Vec2 ppos = player->getPosition();
	Vec2 pdim = player->getDimensions();

	jumphitbox = new Square(Vec2(ppos.x, ppos.y + pdim.y), Vec2(pdim.x, 0.01));
	jumphitbox->setGravityOn(false);


	//currentMap = new MapRoom(dtmng->getMapManager(), 0, 0);
	//currentMap->createRoom(dtmng->getMapManager(), dtmng->getTileTypeManager(), dtmng->getCreatureManager(), 0, 0, false, 0);


	levelTime = new LevelStopwatch(40, Vec2(90, 40), dtmng->getTextImageManager());

	dtmng->getAudioManager()->getMusicByName("TitleScreen")->stopAudio();
	dtmng->getAudioManager()->getMusicByName("Ingame")->playAudio(-1);

	
}

void GameState::unload()
{
	
}

void GameState::saveLevel()
{

//	Utility::log(Utility::I, "Loading save data : " + "res/txt/savedata.txt");
	remove("res/txt/newsavedata.txt");
	std::ifstream dataFile("res/txt/savedata.txt");
	std::ofstream newdataFile("res/txt/newsavedata.txt");

	std::string str;

	if (dataFile.is_open())
	{
		while (dataFile >> str)
		{
			if (str == level->getID())
			{
				str += "\n";
				newdataFile << str;
				newdataFile << level->getFastestTime();
				newdataFile << "\n";
				newdataFile << level->getNumSecrets();
				newdataFile << "\n";
				newdataFile << level->hasComplete();
				newdataFile << "\n";

				dataFile >> str;
				dataFile >> str;
				dataFile >> str;
				

			}
			else {
				str += "\n";
				newdataFile << str;
			}
			
		}
	}
	else {
		//saving failed
	}
	dataFile.close();
	newdataFile.close();

	remove("res/txt/savedata.txt");
	rename("res/txt/newsavedata.txt", "res/txt/savedata.txt");
}

void GameState::letBodyGo()
{
	squares[bodyPickIndex]->setGravityOn(true);
	bodyPick = false;
	bodyPickIndex = -1;
}

void GameState::throwBody()
{
	Vec2 plPos = player->getCentre();
	Vec2 sqPos = squares[bodyPickIndex]->getCentre();

	Vec2 diff = sqPos - plPos;

	float dist = Collision::distanceBetween(plPos, sqPos);

	float power = dist * 4;
	Vec2 diffN = diff.normalize();

	squares[bodyPickIndex]->velocity = diffN * power;

	letBodyGo();
}