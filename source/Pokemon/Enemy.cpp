#include "Enemy.h"
#include <SDL_image.h>
#include <iostream>

using namespace Pokemon;

Enemy::Enemy(SDL_Renderer& renderer, int x, int y, int scaleX, int scaleY, const Json::Value& pokeData)
{
	Entity::CreateEntity(renderer, pokeData["frontimagepath"].asString(), x, y, scaleX, scaleY, pokeData);
	_healthBar = { renderer,  x - 430, y, 300, 100, _name.c_str()};
}

void Enemy::SelectAttack()
{
	_selectedAttackNum = (rand() * rand()) % _attacks.size();
	//std::cout << _selectedAttackNum << std::endl;
	while(_attacks[_selectedAttackNum].PP() <= 0)
		_selectedAttackNum = rand() % _attacks.size();
	Entity::SelectAttack();
}