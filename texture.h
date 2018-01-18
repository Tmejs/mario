#ifndef TEXTURE_H
#define TEXTURE_H
#define NULL 0

struct SDL_Texture;
struct SDL_Rect;

class Texture
{
public:
	Texture();
	~Texture();

	bool load(const char*);
	void free();
	void render();
	void render(int x, int y, SDL_RendererFlip flip, SDL_Rect* clip);
	void renderOnTexture();
	void newTexture(int, int);

	// Getters
	int width();
	int height();
	bool isLoaded();

	// Setters
	void width(int);
	void height(int);
	void texture(SDL_Texture*);
private:
	SDL_Texture* _texture;

	int _width;
	int _height;
};

#endif // !TEXTURE_H