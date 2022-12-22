#pragma once
#include <SDL.h>

namespace Pokemon
{
	class HealthBar
	{

	public:
		HealthBar() = default;
		HealthBar(SDL_Renderer& renderer, int posX, int posY, int width, int height, const char* name);
		void RenderHealthBar(SDL_Renderer& renderer, float maxHealth, float health);

	private:
		SDL_Texture* _background;
		SDL_Texture* _fillBackground;
		SDL_Texture* _nameText;
		SDL_Rect _borderRect;
		SDL_Rect _fillBorder;
		SDL_Rect _nameRect;
	};
}