#ifndef LEVEL_H
#define LEVEL_H

class Block;
struct Collision;
class Level
{
public:
	Level(Uint32, unsigned int, Block**, unsigned int);
	~Level();

	// Returns -1 on no colission or int representing collision height
	Collision isLevelCollided(SDL_Rect);


	// Getters
	Uint32 time();
	unsigned int width();
	unsigned int blockCount();;
	Block** blockMap();
	void render();

private:
	// Creates texture with all blocks
	void createLevelFloor();

	// Variables
	unsigned int _width;
	unsigned int _blockCount;
	Block** _blockMap;
	Uint32 _time;
	Texture _floor;
};

#endif // !LEVEL_H



