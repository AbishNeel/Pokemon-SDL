#include "HealthBar.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace Pokemon;

HealthBar::HealthBar(SDL_Renderer& renderer, int posX, int posY, int width, int height, const char* name)
{
	_borderRect.x = posX;
	_borderRect.y = posY;
	_borderRect.w = width;
	_borderRect.h = height;

	_fillBorder.x = static_cast<int>(_borderRect.x + _borderRect.w / 2.5 + 9);
	_fillBorder.y = static_cast<int>(_borderRect.y + _borderRect.h / 2.2 + 8);
	_fillBorder.w = static_cast<int>(_borderRect.w / 1.9 + 1);
	_fillBorder.h = static_cast<int>(_borderRect.h / 11);

	_background = IMG_LoadTexture(&renderer, "content/panel.png");
	_fillBackground = IMG_LoadTexture(&renderer, "content/health_grey.png");

	TTF_Init();
	TTF_Font* nameFont = TTF_OpenFont("content/pokemon_font.ttf", 20);
	SDL_Surface* nameSurface = TTF_RenderText_Solid(nameFont, name, SDL_Color{ 0, 0, 0, 255 });
	_nameText = SDL_CreateTextureFromSurface(&renderer, nameSurface);
	SDL_QueryTexture(_nameText, nullptr, nullptr, &_nameRect.w, &_nameRect.h);
	_nameRect.x = _borderRect.x + 20;
	_nameRect.y = _borderRect.y + 5;
}

void HealthBar::RenderHealthBar(SDL_Renderer& renderer, float maxHealth, float health)
{
	SDL_Texture* healthFill;
	if (health / maxHealth >= 0.6f)
		healthFill = IMG_LoadTexture(&renderer, "content/health_green.png");
	else if (health / maxHealth >= 0.25f)
		healthFill = IMG_LoadTexture(&renderer, "content/health_yellow.png");
	else
		healthFill = IMG_LoadTexture(&renderer, "content/health_red.png");

	SDL_RenderCopy(&renderer, _background, nullptr, &_borderRect);
	SDL_RenderCopy(&renderer, _fillBackground, nullptr, &_fillBorder);
	

	SDL_Rect fillRect;
	float diff = maxHealth / _fillBorder.w;

	fillRect.x = _fillBorder.x;
	fillRect.y = _fillBorder.y;
	fillRect.w = static_cast<int>(_fillBorder.w - (maxHealth - health) / diff);
	fillRect.h = _fillBorder.h;
	
	SDL_RenderCopy(&renderer, healthFill, nullptr, &fillRect);
	SDL_RenderCopy(&renderer, _nameText, nullptr, &_nameRect);

	SDL_RenderPresent(&renderer);
}