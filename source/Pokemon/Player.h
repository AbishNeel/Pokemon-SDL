#pragma once
#include "Entity.h"
#include "Dialogue.h"
#include <json/json.h>

namespace Pokemon
{
	class Player : public Entity
	{
	public:
		Player(SDL_Renderer& renderer, int x, int y, int scaleX, int scaleY, const Json::Value pokeData);
		void ChangeAttackNum(int changeStep);
		void RenderAttackDialogue();

	private:
		Dialogue _attackDialogue;
	};
}