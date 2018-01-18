#include "include/SDL.h"
#include "Block.h"


Block::Block(unsigned int x, unsigned int y)
{
	_posX = x;
	_posY = y;
}


Block::~Block()
{
}

Casual::Casual(unsigned int x, unsigned int y) : Block(x,y)
{	
}

Casual::~Casual()
{
}

void Casual::touchDown()
{
}

void Casual::touchUp()
{
}

void Casual::touchLeft()
{
}

void Casual::touchRight()
{
}

const char * Casual::whichType()
{
	return "Casual";
}

unsigned int Block::posX()
{
	return _posX;
}

unsigned int Block::posY()
{
	return _posY;
}
