#pragma once

#include "../Entity.h"
#include "CharacterType.h"
#include "../MovingPlatform.h"
#include "../../audio/AudioManager.h"

/**
@brief Creates all data for the character
*/
class Character : public Entity
{
public:
	/**
	@brief Create the character
	@param pos The position of the character.
	*/
	Character(Vec2 pos, CharacterType *characterType);

	/**
	@brief Create the character using the size of the Texture as the size of the character.
	@param texture A pointer to the Texture.
	@param pos The position of the character.
	*/
	Character(Texture* texture, Vec2 pos, CharacterType *characterType);

	/**
	@brief Create the character.
	@param texture A pointer to the Texture.
	@param pos The position of the character.
	@param dimensions The dimensions of the character.
	*/
	Character(Texture* texture, Vec2 pos, Vec2 dimensions, CharacterType *characterType);

	/**
	@brief Create the character with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the character.
	@param dimensions The dimensions of the character.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	
	Character(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spriteDimensions, CharacterType *characterType);

	~Character();

	/**
	@brief Update the Character.
	@param dt The delta time.
	*/
	virtual void update(float dt);


	/**
	@brief Render the Character.
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);

	/**
	@brief Set the character type
	@param charType The character type
	*/
	void setCharacterType(CharacterType* charType);


	/**
	@brief Get the character type
	@return The character type
	*/
	CharacterType* getCharacterType();

	/**
	@brief Set the character health
	@param h The health to set to
	*/
	void setHealth(int h);

	/**
	@brief Get the character health
	@return The character health
	*/
	int getHealth();

	/**
	@brief Set if the character has been hit
	@param b If the character has been hit
	*/
	void setHit(bool b);

	/**
	@brief Get if the character has been hit
	@return True if hit false if not
	*/
	bool isHit();

	/**
	@brief Set if the character can be damaged
	@param d If the character has been hit

	*/
	void setCanDamage(bool d);

	/**
	@brief Check if the character can be hit
	@return true if can hit false if not
	*/
	bool canDamage();


	void setClimbing(bool c);
	bool getClimbing();


	void setOnFloor(bool of);
	bool getOnFloor();

	void setKeyMove(bool km);
	bool getKeyMove();

	void setKeyMoveRight();
	//bool getKeyMoveRight();

	void setKeyMoveLeft();
	//bool getKeyMoveLeft();


	void setLocalVelocity(Vec2 lv);
	Vec2 getLocalVelocity();

	void jump(Audio *jp);

	void moveRight(float dt);
	void moveLeft(float dt);

	void setOnMovingPlatform(bool b);
	void setOnMovingPlatform(bool b, MovingPlatform* mp);
	bool getOnMovingPlatform();

	void setOnEntity(Entity *e);


	void setCanJump(bool cj);
	bool getCanJump();

	void setCanClimb(bool cc);
	bool getCanClimb();

	void setAlive(bool a);

	bool getAlive();

	void setCarryingBody(bool cb);
	void setCarryingBody(bool cb, Body* b);

	bool getCarryingBody();

	Body* getBodyCarrying();

	void setOnBody(bool ob);
	void setOnBody(bool ob, Body *b);

	bool isOnBody();

	Body* getBodyOnTopOf();



private:
	///Reference to CharacterType
	CharacterType *characterType;

	Vec2 lastPos = Vec2(0);

	Vec2 localVelocity;

	///The health of the character
	int health = 3;

	///timer value
	float timer;

	float jumpTimer;

	///if the character has been hit
	bool hit = false;

	///if the character can currently be damaged
	bool canDmg = true;

	//if the player is climbing or not
	bool climbing;



	bool onFloor;

	bool keyMove;
	bool keyMoveRight;
	bool keyMoveLeft;

	float frameTiming = 0;
	float frameSecond;

	enum PlayerState {
		idleState,
		movingState,
		jumpingState,
		climbingState,
		deadState
	};

	enum Direction {
		leftDir,
		rightDir
	};

	Direction playerDir;

	PlayerState pState;
	PlayerState lastState;

	bool addFrame = false;

	Vec2 spriteScale;


	Vec2 relVel;

	int localMaxSpeedX = 70;
	int localMaxSpeedY = 400;

	int speed;
	float airSpeed;
	
	int maxSpeedX = 400;
	int maxSpeedY = 400;



	bool onMovPlatform;
	MovingPlatform *platformOn;

	bool canJump;
	bool canClimb;

	Entity* entityOn = NULL;

	bool alive;

	bool carryingBody = false;


	bool onBody;
	Body* bodyOnTopOf;
	Body *bodyCarrying;

};