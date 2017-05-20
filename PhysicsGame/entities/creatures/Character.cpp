#include "Character.h"
#include "../../Utility.h"


Character::Character(Vec2 pos, CharacterType *characterType) :Entity(pos), characterType(characterType)
{
	texture = characterType->getTexture();
	dimensions = characterType->getSpriteDimensions();
	spriteDimensions = texture->getDimensions();
	bounciness = 0;
	climbing = false;
	staticFriction = 0.5;
	dynamicFriction = 0.4;

	spriteScale = Vec2(1, 1);
	playerDir = rightDir;

	onMovPlatform = false;

	localVelocity = 0;
	speed = 30;
	
	airSpeed = 300;

	canJump = true;

	mass = 1;

	alive = true;

	velocity = 0;

	pState = idleState;
}

Character::Character(Texture* texture, Vec2 pos, CharacterType *characterType) :Entity(texture, pos), characterType(characterType)
{

}

Character::Character(Texture* texture, Vec2 pos, Vec2 dimensions, CharacterType *characterType) : Entity(texture, pos, dimensions), characterType(characterType)
{

}

Character::Character(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spriteDimensions, CharacterType *characterType) : Entity(texture, pos, dimensions, Vec2(0, 0), spriteDimensions), characterType(characterType)
{

}
Character::~Character()
{
}

void Character::update(float dt)
{
	
	frameTiming += dt;

	if (frameTiming > 0.033)
	{
		if (!climbing)
		{
			addFrame = true;
			frameTiming = 0;
		}
		else {
			if (velocity.getLength() > 0)
			{
				addFrame = true;
				frameTiming = 0;
			}
		}
		
	}
	else {
		addFrame = false;
	}

	if (gravityOn)
	{
		float accY = 0;
		accY += 400;


		velocity.y += accY *dt;
	}

	

	

	if (!canDmg)
	{

		timer -= dt;
		if (timer < 0)
		{
			canDmg = true;
			
		}
	}

	/*if (jumpTimer > 0)
	{
		jumpTimer -= dt;
	}
	else {
		canJump = true;
		jumpTimer = -1;
	}*/

	if (alive)
	{
		if (climbing)
		{
			pState = climbingState;
		}
		else if (onFloor) {
			if (abs(velocity.x) > 0.01 && keyMove)
			{
				pState = movingState;
			}
			else {
				pState = idleState;
			}
			//velocity *= 0.98f;
		}
		else {
			pState = jumpingState;
		}
	}
	else {
		pState = deadState;
	}
	

	//velocity += localVelocity;

	pos += velocity * dt;

	if (onMovPlatform)
	{
		
		//pos += platformOn->velocity *dt;

		pos.x += platformOn->velocity.x *dt;
	//	velocity = 0;
		//Utility::log(Utility::I, "On moving platform");
	}

	//Utility::log(Utility::I, Utility::floatToString(velocity.x));
	switch (pState)
	{
	case Character::idleState:
		if (onMovPlatform)
		{
			//applyFriction = false;
			velocity.x = 0;
		}
		
		//Utility::log(Utility::I, "Idle");
		break;
	case Character::movingState:
		applyFriction = true;
		//Utility::log(Utility::I, "Moving");
		break;
	case Character::jumpingState:
		applyFriction = true;
		//Utility::log(Utility::I, "Jumping");
		break;
	default:

		break;
	}


	if (playerDir == rightDir)
	{
		spriteScale = Vec2(1, 1);
	}
	else if (playerDir == leftDir) {
		spriteScale = Vec2(-1, 1);
	}

	keyMove = false;
	//onMovPlatform = false;


	if (velocity.x > maxSpeedX)
	{
		velocity.x = maxSpeedX;
	}

	if (velocity.x < -maxSpeedX)
	{
		velocity.x = -maxSpeedX;
	}

	if (velocity.y > maxSpeedY)
	{
		velocity.y = maxSpeedY;
	}

	if (velocity.y < -maxSpeedY)
	{
		velocity.y = -maxSpeedY;
	}

	if (climbing)
	{
		velocity = 0;
	}

}

void Character::render(SDL_Renderer* renderer)
{
	//times by 1000 so can use mod
	int timerCheck = timer * 1000;

	//creates flashing effect on hit
	if (timerCheck % 10 < 5)
	{
		switch (pState)
		{
		case Character::idleState:
			characterType->render(renderer, pos, dimensions, "I", addFrame, spriteScale);
			break;
		case Character::movingState:
			characterType->render(renderer, pos, dimensions, "M", addFrame, spriteScale);
			break;
		case Character::jumpingState:
			characterType->render(renderer, pos, dimensions, "J", addFrame, spriteScale);
			break;
		case climbingState:
			characterType->render(renderer, pos, dimensions, "C", addFrame, spriteScale);
			
			break;
		case deadState:
			characterType->render(renderer, pos, dimensions, "D", addFrame, spriteScale);
			dimensions = characterType->getSpriteStateDimensions("D");
			break;
		default:

			break;
		}
	}


	

	//characterType->render(renderer, pos, dimensions, )
	
	
}

void Character::setHealth(int h)
{
	health = h;
}

int Character::getHealth()
{
	return health;
}

void Character::setHit(bool b)
{
	hit = b;
	health -= 1;
	timer = 1.2f;
}

bool Character::isHit()
{
	return hit;
}

void Character::setCanDamage(bool d)
{
	canDmg = d;
}

bool Character::canDamage()
{
	return canDmg;
}

void Character::setClimbing(bool c)
{
	climbing = c;
	if (climbing)
	{
		gravityOn = false;
		pState = climbingState;
	}

	
}

bool Character::getClimbing()
{
	return climbing;
}

void Character::setOnFloor(bool of)
{
	onFloor = of;
}

bool Character::getOnFloor()
{
	return onFloor;

}

void Character::setKeyMove(bool km)
{
	keyMove = km;
}

bool Character::getKeyMove()
{
	return keyMove;
}


void Character::setKeyMoveRight()
{
	playerDir = rightDir;
	keyMove = true;
}



void Character::setKeyMoveLeft()
{
	playerDir = leftDir;
	keyMove = true;
}

void Character::setLocalVelocity(Vec2 lv)
{
	localVelocity = lv;
}

Vec2 Character::getLocalVelocity()
{
	return localVelocity;
}
 
void Character::jump()
{
	if (canJump && onFloor)
	{
		if (pState == idleState || pState == movingState)
		{
			jumpTimer = 0.2;
			canJump = false;
			Utility::log(Utility::I, "JUMP");
			velocity.y = -205;
			if (onMovPlatform)
			{
				onMovPlatform = false;

				float v = velocity.x + platformOn->velocity.x;

				float relVelX = platformOn->velocity.x - velocity.x;

				/*if (v < (localMaxSpeedX + abs(platformOn->velocity.x)) && v >(-localMaxSpeedX - abs(platformOn->velocity.x)))
				{

					velocity += platformOn->velocity;
				}*/

				if (abs(relVelX) < localMaxSpeedX)
				{
					float localVelX = velocity.x;
					velocity.x += platformOn->velocity.x;

					/*if (velocity.x > localVelX + abs(platformOn->velaocity.x))
					{
						velocity.x = localVelX + abs(platformOn->velocity.x);
					}

					if (velocity.x < -localVelX - abs(platformOn->velocity.x))
					{
						velocity.x = -localVelX - abs(platformOn->velocity.x);
					}*/
				}

				velocity.y += platformOn->velocity.y;

			}
		}
	}
	
}

void Character::moveRight(float dt)
{
	if (velocity.x < localMaxSpeedX)
	{
		if (onFloor)
		{
			velocity.x += speed;
		}
		else {
			velocity.x += airSpeed * dt;
		}
		
		if (velocity.x > localMaxSpeedX)
		{
			velocity.x = localMaxSpeedX;
		}
	}

}

void Character::moveLeft(float dt)
{
	if (velocity.x > -localMaxSpeedX)
	{
		if (onFloor)
		{
			velocity.x -= speed;
		}
		else {
			velocity.x -= airSpeed * dt;
		}
		if (velocity.x < -localMaxSpeedX)
		{
			velocity.x = -localMaxSpeedX;
		}
	}


}

void Character::setOnMovingPlatform(bool b)
{
	onMovPlatform = b;
}

void Character::setOnMovingPlatform(bool b, MovingPlatform *mp)
{
	onMovPlatform = b;
	platformOn = mp;

	

	if (pState == idleState)
	{
		//velocity = 0;
	}
}

bool Character::getOnMovingPlatform()
{
	return onMovPlatform;
}

void Character::setOnEntity(Entity *e)
{
	entityOn = e;
}

void Character::setCanJump(bool cj)
{
	canJump = cj;
}

bool Character::getCanJump()
{
	return canJump;
}

void Character::setCanClimb(bool cc)
{
	canClimb = cc;
}

bool Character::getCanClimb()
{
	return canClimb;
}

void Character::setAlive(bool a)
{
	alive = a;
}

bool Character::getAlive()
{
	return alive;
}