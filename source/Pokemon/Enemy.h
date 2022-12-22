#pragma once
#include "Entity.h"
#include <string>
#include <json/json.h>

namespace Pokemon
{
	class Enemy : public Entity
	{
	public:
		Enemy(SDL_Renderer& renderer, int x, int y, int scaleX, int scaleY, const Json::Value& pokeData);
		void SelectAttack() override;
	};
}