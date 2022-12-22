#include "Player.h"
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "Enemy.h"
#include <iostream>
#include <fstream>

using namespace Pokemon;

Player::Player(SDL_Renderer& renderer, int x, int y, int scaleX, int scaleY, const Json::Value pokeData) :
										 _attackDialogue {renderer, 0, 450, 150, 50}
{
	Entity::CreateEntity(renderer, pokeData["backimagepath"].asString(), x, y, scaleX, scaleY, pokeData);
	_healthBar = { renderer, x + 400, y, 300, 100, _name.c_str() };
}

void Player::RenderAttackDialogue()
{
	_attackDialogue.DisplayAttacks(_attacks);
	_attackDialogue.RenderSelectorUI(_selectedAttackNum);
	_attackDialogue.DisplayAttackStats(_attacks[_selectedAttackNum]);
}

void Player::ChangeAttackNum(int changeStep)
{
	if (_selectedAttackNum + changeStep > 3 || _selectedAttackNum + changeStep < 0)
		return;
	_selectedAttackNum += changeStep;
}