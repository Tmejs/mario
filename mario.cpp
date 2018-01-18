#include "include\SDL.h"
#include "State.h"
#include "Constants.h"
#include "Texture.h"
#include "Level.h"
#include "Collision.h"
#include "Game.h"
#include <cstdio>
#include "Mario.h"

// TODO 
// flip mario on standing position when was moving left

void Mario::initFrames()
{
	// Set specific frames to specific animation clips
	frames[0].x = 23;
	frames[0].y = 507;
	frames[0].w = 16;
	frames[0].h = 16;

	frames[1].x = 85;
	frames[1].y = 507;
	frames[1].w = 15;
	frames[1].h = 16;

	frames[2].x = 100;
	frames[2].y = 507;
	frames[2].w = 16;
	frames[2].h = 16;

	frames[3].x = 117;
	frames[3].y = 507;
	frames[3].w = 16;
	frames[3].h = 16;

	frames[4] = frames[2];
	
	frames[5].x = 139;
	frames[5].y = 507;
	frames[5].w = 16;
	frames[5].h = 16;
}

void Mario::render()
{
	if (_lastDirection == LEFT)
	{
		G::spriteSheet.render(S::mario.posX() - S::offsetX, S::mario.posY() + SKY, SDL_FLIP_HORIZONTAL, &S::mario.currentFrame());
	}
	else if (_lastDirection == RIGHT)
	{
		G::spriteSheet.render(S::mario.posX() - S::offsetX, S::mario.posY() + SKY, SDL_FLIP_NONE, &S::mario.currentFrame());
	}
}

void Mario::update()
{
	jump();
	walk();

	// Check if Mario is not in motion
	if (RELATIVE_VELOCITY_Y_AXIS == 0 && _velX == 0 && !_isJumping)
	{
		stand();
	}

	// Falling into gap check
	if (_posY > SCREEN_HEIGHT) 
	{
		resetSpeed();
		S::loseLife();
	}

}

void Mario::resetSpeed()
{
	_velY = 0;
}

SDL_Rect Mario::currentFrame()
{
	return frames[_currentFrame];
}

void Mario::walk()
{
	// Walking check
	if (_velX != 0)
	{

		// Move Mario on X Axis
		_posX += _velX;

		// Update X Axis collision
		_collisionInfo = S::level->isLevelCollided(getRect());

		// Window exceeding and level collision check
		if (_collisionInfo.c || (_posX < S::offsetX))
		{
			// Move back
			_posX -= _velX;
		}


		// Start animation for walking only on ground
		if (RELATIVE_VELOCITY_Y_AXIS == 0 && !_isJumping)
		{
			animateWalk();
		}

		// Set Mario direction flag
		_lastDirection = (_velX < 0) ? LEFT : RIGHT;
	}
	
	// Enemy collision check
	if (S::isEnemyCollided().c) S::loseLife();
}

void Mario::animateWalk()
{
	// Used to smooth out the animation
	_animationCount++;

	// Manage animation 
	_currentFrame = (_animationCount / WALK_ANIMATION_SPEED);

	// Exceeding walking frames check
	if (_currentFrame >= WALK_ANIMATION_FRAMES)
	{
		// Restarts to first frame and starts new animation
		_currentFrame = STAND_ANIMATION_FRAMES;
		_animationCount = 0;
	}
	else
	{
		// Avoid standing animation frame
		_currentFrame += STAND_ANIMATION_FRAMES;
	}
}

void Mario::beginJump()
{
	_velY = -Y_AXIS_VELOCITY;
	_isJumping = true;
}

void Mario::jump()
{
	_velY += GRAVITY;
	// Start animation for jumping
	if (RELATIVE_VELOCITY_Y_AXIS != 0)
	{
		animateJump();
	}
	
	// Move Mario on Y Axis
	_posY += RELATIVE_VELOCITY_Y_AXIS;

	// Update collision check
	_collisionInfo = S::level->isLevelCollided(getRect());

	if(_collisionInfo.c)
	{

		// Down collision
		if (RELATIVE_VELOCITY_Y_AXIS >= 0)
		{
			// Move back
			_posY = _collisionInfo.y - BLOCK_HEIGHT;
			_velY = 0;
			_isJumping = false;

		}

		// Up collision
		else if (RELATIVE_VELOCITY_Y_AXIS < 0)
		{
			_posY = _collisionInfo.y + BLOCK_HEIGHT;
			_velY = 1;
			_isJumping = true;
		}
	}

	if (RELATIVE_VELOCITY_Y_AXIS > 0)
	{
		// Enemy collision check
		if (S::isEnemyCollided().c) S::killEnemy();
	}
}

void Mario::animateJump()
{
	// Sets frame to jumping Mario
	_currentFrame = STAND_ANIMATION_FRAMES + WALK_ANIMATION_FRAMES;
}

void Mario::stand()
{
	// Sets frame to standing Mario
	_currentFrame = 0;
	
}

void Mario::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN )
	{
		// Change velocity only once
		if (e.key.repeat == 0)
		{
			// Change velocity depending on key pressed
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				_velX -= X_AXIS_VELOCITY;
				break;
			case SDLK_RIGHT:
				_velX += X_AXIS_VELOCITY;
				break;
			case SDLK_UP:
				if (RELATIVE_VELOCITY_Y_AXIS == 0 && !_isJumping)
				{
					beginJump();
				}
				break;
			}
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		// Change velocity depending on key pressed
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: 
			_velX += X_AXIS_VELOCITY; 
			break;
		case SDLK_RIGHT: 
			_velX -= X_AXIS_VELOCITY; 
			break;
		}
	}
}

int Mario::posX()
{
	return _posX;
}

int Mario::posY()
{
	return _posY;
}

SDL_Rect Mario::getRect()
{
	SDL_Rect marioRect;
	marioRect.x = _posX;
	marioRect.y = _posY;
	marioRect.w = BLOCK_WIDTH;
	marioRect.h = BLOCK_HEIGHT;
	return marioRect;
}

void Mario::posX(int x)
{
	_posX = x;
}

void Mario::posY(int y)
{
	_posY = y;
}

Mario::Mario()
{
	_currentFrame = 0;
	_posX = 0;
	_posY = 0;
	_velX = 0;
	_velY = 0;
	_animationCount = 0;
	_isJumping = false;
	_lastDirection = RIGHT;
	initFrames();
}

Mario::~Mario()
{
	//TODO
}
