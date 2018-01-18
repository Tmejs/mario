#ifndef BLOCK_H
#define BLOCK_H

// Rodzaj kodawania w pliku tekstowym oraz adres do poszczegolnego blocku
#define CASUAL_CODE '#'

// Glowna klasa abstrakcyjna dla wszystkich klockow w grze ( platform ) 
class Block
{
public:
	Block(unsigned int,unsigned int);
	virtual ~Block();
	
	// Pure virtual methods
	virtual void touchDown() = 0;
	virtual void touchUp() = 0;
	virtual void touchLeft() = 0;
	virtual void touchRight()  = 0;

	virtual const char* whichType() = 0;
	// Getters
	unsigned int posX();
	unsigned int posY();
protected:
	// Block position
	unsigned int _posX;
	unsigned int _posY;

};

// Klasa zwyk³ego klocka
class Casual : public Block {
public:
	Casual(unsigned int x, unsigned int y);
	~Casual();

	void touchDown();
	void touchUp();
	void touchLeft();
	void touchRight();

	const char* whichType();

};

// poszczegolna klasa:
// info o znaku odpowiadajacym w pliku z poziomem
// rodzaj kolizji w zaleznosci od strony
// info z grafika
// wymiary takie same dla wszystkich klockow

#endif // !BLOCK_H



