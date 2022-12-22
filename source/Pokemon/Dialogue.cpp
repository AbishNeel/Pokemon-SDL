#include "Dialogue.h"

using namespace Pokemon;

Dialogue::Dialogue(SDL_Renderer& renderer, int x, int y, int w, int h) : _renderer{renderer}
{
	TTF_Init();
	_textFont = TTF_OpenFont("content/pokemon_font.ttf", 50);
	_textColor = SDL_Color{ 0, 0, 0, 255 };

	_rect.x = x + 30;
	_rect.y = y + 30;
	_rect.w = w;
	_rect.h = h;
	
	_backgroundRect.x = x;
	_backgroundRect.y = y;
	_backgroundRect.w = 800;
	_backgroundRect.h = 600 - _backgroundRect.y;
}

void Dialogue::DisplayAttacks(std::vector<Attack>& attacks)
{
	SDL_Texture* background = IMG_LoadTexture(&_renderer, "content/attackdialogue.png");
	SDL_RenderCopy(&_renderer, background, nullptr, &_backgroundRect);
	for (int i = 0; i < 4; ++i)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(_textFont, attacks[i].Name().c_str(), _textColor);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(&_renderer, textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect rect;
		rect.x = 20 + _rect.x + ((i%2) * 250);
		rect.y = _rect.y + (i > 1 ? 50 : 0) - 5;
		rect.w = _rect.w;
		rect.h = _rect.h;

		SDL_RenderCopy(&_renderer, textTexture, nullptr, &rect);
	}
	SDL_RenderPresent(&_renderer);
}

void Dialogue::DisplayText(const std::string& message)
{
	SDL_Texture* background = IMG_LoadTexture(&_renderer, "content/dialogue.png");
	SDL_Surface* textSurface = TTF_RenderText_Solid(_textFont, message.c_str(), _textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(&_renderer, textSurface);
	SDL_FreeSurface(textSurface);

	SDL_RenderCopy(&_renderer, background, nullptr, &_backgroundRect);

	SDL_Rect rect = _rect;
	rect.x += 20;
	SDL_RenderCopy(&_renderer, textTexture, nullptr, &rect);

	SDL_Texture* prompter = IMG_LoadTexture(&_renderer, "content/prompter.png");
	rect.x = rect.w + 230;
	rect.y = rect.y + rect.h + 20;
	rect.w = 20;
	rect.h = 30;
	SDL_RenderCopyEx(&_renderer, prompter, nullptr, &rect, 90, nullptr, SDL_FLIP_NONE);
	SDL_RenderPresent(&_renderer);
}

void Dialogue::RenderSelectorUI(int attackIndex)
{
	SDL_Texture* prompter = IMG_LoadTexture(&_renderer, "content/prompter.png");

	SDL_Rect rect;
	rect.x = 10 + (_rect.x - _rect.x/2) + ((attackIndex%2) * 250);
	rect.y = _rect.y  + (attackIndex > 1 ? 60 : 10);
	rect.w = 20;
	rect.h = 30;

	SDL_RenderCopy(&_renderer, prompter, nullptr, &rect);
	SDL_RenderPresent(&_renderer);
}

void Dialogue::DisplayAttackStats(const Attack& selectedAttack)
{
	selectedAttack;
	SDL_Surface* typeSurface = TTF_RenderText_Solid(_textFont, selectedAttack.Type().c_str(), _textColor);
	SDL_Texture* typeText = SDL_CreateTextureFromSurface(&_renderer, typeSurface);
	SDL_FreeSurface(typeSurface);

	SDL_Surface* ppSurface = TTF_RenderText_Solid(_textFont, std::to_string(selectedAttack.PP()).c_str(), _textColor);
	SDL_Texture* ppText = SDL_CreateTextureFromSurface(&_renderer, ppSurface);
	SDL_FreeSurface(ppSurface);

	SDL_Surface* maxPPSurface = TTF_RenderText_Solid(_textFont, std::to_string(selectedAttack.MaxPP()).c_str(), _textColor);
	SDL_Texture* maxPPText = SDL_CreateTextureFromSurface(&_renderer, maxPPSurface);
	SDL_FreeSurface(maxPPSurface);

	SDL_Rect typeRect, ppRect;
	typeRect.x = _backgroundRect.w - 150;
	typeRect.y = _backgroundRect.y + _backgroundRect.h - 70;
	typeRect.w = 120;
	typeRect.h = 40;

	ppRect = typeRect;
	ppRect.x += 25;
	ppRect.y -= 60;
	ppRect.w = 35;
	ppRect.h = 50;

	SDL_RenderCopy(&_renderer, ppText, nullptr, &ppRect);
	ppRect.x += 60;
	SDL_RenderCopy(&_renderer, maxPPText, nullptr, &ppRect);
	SDL_RenderCopy(&_renderer, typeText, nullptr, &typeRect);
	SDL_RenderPresent(&_renderer);
}