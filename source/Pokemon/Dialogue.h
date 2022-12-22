#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>
#include "Attack.h"
#include <string>

namespace Pokemon
{
	class Dialogue
	{
	public:
		Dialogue(SDL_Renderer& renderer, int x, int y, int w, int h);

		void DisplayAttacks(std::vector<Attack>& attacks);
		void RenderSelectorUI(int attackIndex);
		void DisplayText(const std::string& message);
		void DisplayAttackStats(const Attack& selectedAttack);

	private:
		SDL_Renderer& _renderer;
		TTF_Font* _textFont;
		SDL_Color _textColor;
		SDL_Rect _rect;
		SDL_Rect _backgroundRect;
	};
}