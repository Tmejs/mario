#include <cstdio>
#include "include\SDL.h"
#include "State.h"
#include "Constants.h"
#include "Game.h"
#include "Texture.h"

// Empty initialization
Texture::Texture()
{
	 _texture = NULL;
	_width = 0;
	_height = 0;
}

Texture::~Texture()
{
	free();
}

// Loads surface from file and generates a texture from it
bool Texture::load(const char* path)
{
	// Destroying previous texture
	free();

	// SDL_Texture which will be created from surface
	SDL_Texture* newTexture = NULL;

	// Loading from local file
	SDL_Surface* surface = SDL_LoadBMP(path);

	// Creation check
	if (surface == NULL)
	{
		printf("Load Texture : %s", SDL_GetError());
	}
	else
	{
		// Pinkish is background color in sprite sheet ( 0xff, 0, 0xff )
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xff, 0, 0xff));

		newTexture = SDL_CreateTextureFromSurface(G::wRenderer, surface);

		// Creation check
		if (newTexture != NULL)
		{
			_width = surface->w;
			_height = surface->h;
		}

		// No longer necessary
		SDL_FreeSurface(surface);
	}

	// Assignment to obcject
	_texture = newTexture;
	
	// Return true if created sucessfully
	return isLoaded();
}

// Standalone function in order to free memory within the same object
void Texture::free()
{
	if (_texture != NULL)
	{
		_width = 0;
		_height = 0;
		SDL_DestroyTexture(_texture);
		_texture = NULL;
	}
}

void Texture::render()
{
	render(0, 0, SDL_FLIP_NONE, NULL);
}

// renders SDL_Rect at given x,y
void Texture::render(int x, int y, SDL_RendererFlip flip, SDL_Rect* clip)
{
	// SDL_Rect with given parameters
	SDL_Rect renderQuad = { x, y, this->_width, this->_height };

	// If SDL_Rect given as parameter
	if (clip != NULL)
	{
		// Change size to given
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// If clip exsists render only part it points to
	SDL_RenderCopyEx(G::wRenderer, _texture, clip, &renderQuad, 0, NULL, flip);
}

void Texture::renderOnTexture()
{
	SDL_SetRenderTarget(G::wRenderer, _texture);
}

void Texture::newTexture(int w, int h)
{	
	free();
	_width = w;
	_height = h;
	SDL_Texture *t = SDL_CreateTexture(G::wRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	_texture = t;
}

int Texture::width()
{
	return _width;
}

int Texture::height()
{
	return _height;
}

bool Texture::isLoaded()
{
	return _texture != NULL;
}

void Texture::width(int w)
{
	_width = w;
}

void Texture::height(int h)
{
	_height = h;
}

void Texture::texture(SDL_Texture * t)
{
	_texture = t;
}
