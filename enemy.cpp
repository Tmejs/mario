#include "include/SDL.h"
#include "State.h"
#include "Constants.h"
#include "Texture.h"
#include "Level.h"
#include "Collision.h"
#include "Game.h"
#include "Mario.h"
#include "Enemy.h"



Enemy::Enemy(int x, int y)
{
	_currentFrame = 0;
	_posX = x;
	_posY = y;
	_velX = -X_AXIS_VELOCITY;
	_velY = 0;
	_animationCount = 0;
	_isAlive = true;
	_lastDirection = LEFT;
	initFrames();
}


Enemy::~Enemy()
{
}

void Enemy::initFrames()
{
	frames[0].x = 187;
	frames[0].y = 894;
	frames[0].w = 16;
	frames[0].h = 16;

	frames[1].x = 208;
	frames[1].y = 894;
	frames[1].w = 16;
	frames[1].h = 16;

	frames[2].x = 228;
	frames[2].y = 894;
	frames[2].w = 16;
	frames[2].h = 16;
}

void Enemy::render()
{
	if (_lastDirection == LEFT)
	{
		G::spriteSheet.render(posX() - S::offsetX, posY() + SKY, SDL_FLIP_HORIZONTAL, &currentFrame());
	}
	else if (_lastDirection == RIGHT)
	{
		G::spriteSheet.render(posX() - S::offsetX, posY() + SKY, SDL_FLIP_NONE, &currentFrame());
	}
}

void Enemy::update()
{
	jump();
	walk();
}

Collision Enemy::collisionCheck()
{
	SDL_Rect second = getRect();
	Collision collision;

	if (SDL_HasIntersection(&S::mario.getRect(), &second))
	{
		collision.x = second.x;
		collision.y = second.y;
		collision.c = true;
	}

	return collision;
}

SDL_Rect Enemy::currentFrame()
{
	return frames[_currentFrame];
}

void Enemy::walk()
{
		// Move Enemy on X Axis
		_posX += _velX;

		// Update X Axis collision
		_collisionInfo = S::level->isLevelCollided(getRect());

		// Window exceeding and collision check
		if (_collisionInfo.c || (_posX < 0) || _posX > S::offsetX + SCREEN_WIDTH - BLOCK_WIDTH)
		{
			// Move back
			_posX -= _velX;
			_velX *= -1;
		}

		animateWalk();

		// Set Enemy direction flag
		_lastDirection = (_velX < 0) ? LEFT : RIGHT;
}

void Enemy::animateWalk()
{
	// Used to smooth out the animation
	_animationCount++;

	// Manage animation 
	_currentFrame = (_animationCount / WALK_ANIMATION_SPEED);

	// Exceeding walking frames check
	if (_currentFrame >= WALK_ANIMATION_FRAMES)
	{
		// Restarts to first frame and starts new animation
		_animationCount = 0;
		_currentFrame = 0;
	}
}

void Enemy::jump()
{
	_velY += GRAVITY;

	// Start animation for jumping
	if (RELATIVE_ENEMY_VELOCITY_Y_AXIS != 0)
	{
		animateJump();
	}


	// Move Mario on Y Axis
	_posY += RELATIVE_ENEMY_VELOCITY_Y_AXIS;

	// Update collision check
	_collisionInfo = S::level->isLevelCollided(getRect());

	if (_collisionInfo.c)
	{
		// Move back
		_posY = _collisionInfo.y - BLOCK_HEIGHT;
		_velY = 0;
	}
}

void Enemy::animateJump()
{
	// Sets frame to jumping Mario
	_currentFrame = WALK_ANIMATION_FRAMES;
}

void Enemy::kill()
{
	_isAlive = false;
	S::mario.beginJump();
}

int Enemy::posX()
{
	return _posX;
}

int Enemy::posY()
{
	return _posY;
}

SDL_Rect Enemy::getRect()
{
	SDL_Rect enemyRect;
	enemyRect.x = _posX;
	enemyRect.y = _posY;
	enemyRect.w = BLOCK_WIDTH;
	enemyRect.h = BLOCK_HEIGHT;
	return enemyRect;
}

bool Enemy::isAlive()
{
	return _isAlive;
}

void Enemy::posX(int x)
{
	_posX = x;
}

void Enemy::posY(int y)
{
	_posY = y;
}
