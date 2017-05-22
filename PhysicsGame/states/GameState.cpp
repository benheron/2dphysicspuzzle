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
							if (dist < 90)
							{
								bodyPick = true;
								bodyPickIndex = i;

								squares[i]->setGravityOn(false);
								squares[i]->velocity = Vec2(0, 0);
								dtmng->getAudioManager()->getSFXByName("BodyPick")->playAudio(0);
							}
						}
					}
				}
				else {
					if (bodyPickIndex != -1)
					{
						letBodyGo(true);
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
				
					//stateManager->addState(dtmng->getPauseMenuState());
				stateManager->addState(new PauseMenuState(stateManager, platform, dtmng));
					
					//stateManager->changeState(new ChooseLevelState(stateManager, platform, dtmng));
					esc = true;
					return false;
				break;
			//temporary movement
			case SDLK_UP:
				dtmng->getKeyboardManager()->setKeyDown("up", true);
				kUp = true;
				break;
			case SDLK_DOWN:
				dtmng->getKeyboardManager()->setKeyDown("down", true);
				kDown = true;
				break;
			case SDLK_LEFT:
				dtmng->getKeyboardManager()->setKeyDown("left", true);
				kLeft = true;
				break;
			case SDLK_RIGHT:
				dtmng->getKeyboardManager()->setKeyDown("right", true);
				kRight = true;
				break;
			case SDLK_w:
				dtmng->getKeyboardManager()->setKeyDown("w", true);
				kUp = true;
				break;
			case SDLK_s:
				dtmng->getKeyboardManager()->setKeyDown("s", true);
				kDown = true;
				break;
			case SDLK_a:
				dtmng->getKeyboardManager()->setKeyDown("a", true);
				kLeft = true;
				break;
			case SDLK_d:
				dtmng->getKeyboardManager()->setKeyDown("d", true);
				kRight = true;
				break;
			case SDLK_l:
				dtmng->getKeyboardManager()->setKeyDown("l", true);
				if (!lDown && !debugInfo)
				{
					debugInfo = true;
				}
				else if (!lDown && debugInfo){
					debugInfo = false;
				}
				lDown = true;
				break;

			case SDLK_LSHIFT:
				dtmng->getKeyboardManager()->setKeyDown("shift", true);
				if (!dash)
				{
					if (canDash && canJump)
					{
						dash = true;
					}
					
				}
				break;

			case SDLK_SPACE:
				dtmng->getKeyboardManager()->setKeyDown("space", true);
				
				break;
			case SDLK_e:
				dtmng->getKeyboardManager()->setKeyDown("e", true);
				break;
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
		

			case SDLK_UP:
				dtmng->getKeyboardManager()->setKeyDown("up", false);
				kUp = false;
				break;
			case SDLK_DOWN:
				dtmng->getKeyboardManager()->setKeyDown("down", false);
				kDown = false;
				break;
			case SDLK_LEFT:
				dtmng->getKeyboardManager()->setKeyDown("left", false);
				kLeft = false;
				break;
			case SDLK_RIGHT:
				dtmng->getKeyboardManager()->setKeyDown("right", false);
				kRight = false;
				break;
			case SDLK_w:
				dtmng->getKeyboardManager()->setKeyDown("w", false);
				kUp = false;
				break;
			case SDLK_s:
				dtmng->getKeyboardManager()->setKeyDown("s", false);
				kDown = false;
				break;
			case SDLK_a:
				dtmng->getKeyboardManager()->setKeyDown("a", false);
				kLeft = false;
				break;
			case SDLK_d:
				dtmng->getKeyboardManager()->setKeyDown("d", false);
				kRight = false;
				break;

			case SDLK_l:
				dtmng->getKeyboardManager()->setKeyDown("l", false);
				lDown = false;
				lUp = true;
				break;

			case SDLK_SPACE:
				dtmng->getKeyboardManager()->setKeyDown("space", false);
				if (bodyPick)
				{
					throwBody();
				}
				break;
			case SDLK_e:
				dtmng->getKeyboardManager()->setKeyDown("e", false);
				break;
			
			default:
				//Utility::log(Utility::I, Utility::intToString(events.key.keysym.sym));
				break;
			}
			break;
		}
	}
	return false;
}

void GameState::update(float dt)
{
	currentMap->update(dt);


	levelTime->update(dt);
	
	//just some testing data for moving the player
	Vec2 curPos = player->getPosition();
	Vec2 movement = Vec2(0);

	
	if (player->getPosition().y < -30 || player->getPosition().y > 540
		|| player->getPosition().x < 30 ||  player->getPosition().x > 960)
	{
		player->setAlive(false);
	}
	

	//control
	if (player->getAlive())
	{
		if (kLeft)
		{
			player->setKeyMoveLeft();
			//player->velocity = Vec2(-1, 0);
			//power += 0.2 *dt;
		}


		if (kRight)
		{
			player->setKeyMoveRight();
			//player->velocity = Vec2(1, 0);
			//power += 0.2 *dt;
		}
		if (!player->getClimbing())
		{
			player->setGravityOn(true);
			if (kLeft)
			{
				movement.x = -1;
				player->moveLeft(dt);
				//player->velocity = Vec2(-1, 0);
				//power += 0.2 *dt;
			}

			if (kRight)
			{
				movement.x = 1;
				player->moveRight(dt);
				//player->velocity = Vec2(1, 0);
				//power += 0.2 *dt;
			}
			else {
				//player->velocity.x = 0;
			}

			if (kUp)
			{
				if (player->getCanJump() && player->getOnFloor())
				{
					player->jump(dtmng->getAudioManager()->getSFXByName("Jump"));
				}


				//player->velocity = Vec2(0, 1);
				//power += 0.2 *dt;
			}
			else {
				player->setCanJump(true);
			}

			if (kDown)
			{
				//movement.y = 1;
				//player->velocity = Vec2(0, -1);
				//power += 0.2 *dt;
			}

			if (dtmng->getKeyboardManager()->keyDown("e"))
			{
				if (player->getCanClimb())
				{
					player->setClimbing(true);
				}
			}




		}
		else {
			player->setGravityOn(false);
			if (kLeft)
			{
				movement.x = -1;
				player->setKeyMoveLeft();
				//player->velocity = Vec2(-1, 0);
				//power += 0.2 *dt;
			}


			if (kRight)
			{
				movement.x = 1;
				player->setKeyMoveRight();
				
			}
			else {
				//player->velocity.x = 0;
			}

			if (kUp)
			{

				movement.y = -1;

			;
			}

			if (kDown)
			{
				movement.y = 1;
			}



			//get normal of momentum
			Vec2 normCurPos = movement.normalize();
			float speed = 70;

			Vec2 dir = normCurPos * speed;

			Vec2 newCurPosX = curPos;
			Vec2 newCurPosY = curPos;

			//player->velocity += dir;

			player->velocity += dir;

			int maxSpeedX = 70;
			int maxSpeedY = 70;
			//if (!dash)
			{
				if (player->velocity.x > maxSpeedX)
				{
					player->velocity.x = maxSpeedX;
				}

				if (player->velocity.x < -maxSpeedX)
				{
					player->velocity.x = -maxSpeedX;
				}

				if (player->velocity.y > maxSpeedY)
				{
					player->velocity.y = maxSpeedY;
				}

				if (player->velocity.y < -maxSpeedY)
				{
					player->velocity.y = -maxSpeedY;
				}
			}
		}

	}
	
	





	if (bodyPick && dtmng->getKeyboardManager()->keyDown("space"))
	{
		if (throwStrength < 400)
		{
			throwStrength += 340 * dt;
		}
		else {
			throwStrength = 400;
		}
		
	}



	if (bodyPick)
	{
		if (player->isOnBody() && player->getBodyOnTopOf() == squares[bodyPickIndex])
		{
			letBodyGo(true);
		}
		else {
			player->setCarryingBody(true, squares[bodyPickIndex]);
			//move body with mouse
			Vec2 plPos = player->getCentre();
			Vec2 sqPos = squares[bodyPickIndex]->getCentre();
			Vec2 diffM = mousePos - sqPos;

			Vec2 d = mousePos - squares[bodyPickIndex]->getDimensions() / 2;

			float distps = Collision::distanceBetween(plPos, sqPos);

		

			Vec2 diffN = diffM.normalize();

			if (!currentMap->checkNonBoxMouseCollide(mousePos))
			{
				if (distps < 90)
				{

					float distsm = Collision::distanceBetween(sqPos, mousePos);
					//Utility::log(Utility::I, "Distance between mouse and body" + Utility::floatToString(distsm));


					float power = distsm * 30;
					squares[bodyPickIndex]->velocity = diffN * power;
			
				}
				else {
				
					letBodyGo(true);
				}
			}
			else {
				letBodyGo(true);
			}

			
		}
		
	}

	/*if (dash && canDash)
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


	}*/

	if (!player->getAlive())
	{
		playerDeadTime += dt;

		if (!playedDeathSound)
		{
			dtmng->getAudioManager()->getSFXByName("Death")->playAudio(0);
			playedDeathSound = true;
		}

		if (playerDeadTime > 1.5)
		{
			//boolCheat *retry = new boolCheat();
			stateManager->addState(new OnDeathState(stateManager, platform, dtmng, retry));

			
		}
		
	}


	if (!retry)
	{
		if (currentMap->getLevelComplete())
		{
			if (!playedLevelCompleteSound)
			{
				dtmng->getAudioManager()->getMusicByName("Ingame")->stopAudio();
				dtmng->getAudioManager()->getSFXByName("EndLevel")->playAudio(0);
				playedLevelCompleteSound = true;
			}
			levelTime->stop();
			playerFinishTime += dt;
			if (!writtenToFile)
			{
				unsigned int oldTime = level->getFastestTime();
				unsigned int newTime = levelTime->getTime();
				if (newTime < oldTime)
				{
					level->setFastestTime(levelTime->getTime());
				}
				level->setComplete(true);
				saveLevel();
				writtenToFile = true;
			}
			else {
				if (playerFinishTime > 1)
				{
					stateManager->addState(new OnWinState(stateManager, platform, dtmng, retry, levelTime, level));
				}
			}
			

			
			//stateManager->changeState(new ChooseLevelState(stateManager, platform, dtmng));
		}
	}
	if (retry)
	{
		stateManager->changeState(new GameState(stateManager, platform, dtmng, level));
		return;
	}
	

}

void GameState::resolveCollision(Square *a, Square *b)
{

}

void GameState::render()
{
	backgroundTexture->pushSpriteToScreen(platform->getRenderer(), Vec2(0, 0));

	currentMap->render(platform->getRenderer());
	levelTime->render(platform->getRenderer());

	/*if (debugInfo)
	{
		currentMap->renderDebug(platform->getRenderer(), red);
	}*/

	
	
}

void GameState::load()
{

	//red = new Texture(platform->getRenderer(), { 255, 0 ,0 });
	throwStrength = 0;

	currentMap = new MapRoom(dtmng->getMapManager(), dtmng->getTileTypeManager(), dtmng->getCreatureManager(), dtmng->getItemManager(), dtmng->getAssetManager(), level->getID());



	levelTime = new LevelStopwatch(40, Vec2(90, 40), dtmng->getTextImageManager());

	dtmng->getAudioManager()->getMusicByName("TitleScreen")->stopAudio();
	dtmng->getAudioManager()->getMusicByName("Ingame")->playAudio(-1);

	player = currentMap->getPlayer();
	squares = currentMap->getSquares();
	circles = currentMap->getCircles();
	
	backgroundTexture = new Texture("res/img/bg2.png", platform->getRenderer());

	int a = level->getLevelIndex() % 4;
	backgroundTexture = dtmng->getAssetManager()->getTexture("sky");
	if (level->getLevelIndex() < 5)
	{
		backgroundTexture = dtmng->getAssetManager()->getTexture("sky");
	} else
		if (level->getLevelIndex() < 10)
		{
			backgroundTexture = dtmng->getAssetManager()->getTexture("cityscape");
		}
		else if (level->getLevelIndex() < 12)
		{
			backgroundTexture = dtmng->getAssetManager()->getTexture("cityscapenight");
		}
	
}


void GameState::saveLevel()
{

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

void GameState::letBodyGo(bool drop)
{
	squares[bodyPickIndex]->setGravityOn(true);
	if (drop)
	{
		squares[bodyPickIndex]->velocity /= 10;
	}
	bodyPick = false;
	bodyPickIndex = -1;
	throwStrength = 0;
	player->setCarryingBody(false);
}

void GameState::throwBody()
{
	Vec2 plPos = player->getCentre();
	Vec2 sqPos = squares[bodyPickIndex]->getCentre();

	Vec2 diff = sqPos - plPos;

	float dist = Collision::distanceBetween(plPos, sqPos);

	float power = dist * 4;
	Vec2 diffN = diff.normalize();

	squares[bodyPickIndex]->velocity = diffN * throwStrength;
	throwStrength = 0;

	letBodyGo(false);
}


void GameState::unload()
{
	delete currentMap;
	//delete backgroundTexture;
}