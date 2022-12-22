#include "Entity.h"
#include <SDL_image.h>
#include <fstream>

using namespace Pokemon;

Entity::Entity() : _selectedAttackNum {0}, _health{0}, _maxHealth{0}, _imageWidth{0}, _imageHeight{0},
					_image{nullptr}, _healthBar{}, _renderRect{}, _speed{0}
{
	
}

void Entity::CreateEntity(SDL_Renderer& renderer, const std::string imgName, int x, int y, int scaleX, int scaleY, const Json::Value pokeData)
{
	_image = IMG_LoadTexture(&renderer, imgName.c_str());
	SDL_QueryTexture(_image, nullptr, nullptr, &_imageWidth, &_imageHeight);

	_renderRect.x = x;
	_renderRect.y = y;
	_renderRect.w = _imageWidth * scaleX;
	_renderRect.h = _imageHeight * scaleY;

	std::string jsonPath = "content/attacks.json";
	Json::Value attackData;

	std::ifstream jsonStream(jsonPath, std::ifstream::binary);
	jsonStream >> attackData;

	for (Json::Value attack : pokeData["attacks"])
	{
		Json::Value attackToInsert = attackData[attack.asString()];
		_attacks.emplace_back(attack.asString(), attackToInsert["damage"].asInt(), 
			attackToInsert["accuracy"].asInt(), attackToInsert["speed"].asInt(), 
			attackToInsert["PP"].asInt(), attackToInsert["type"].asString());
	}

	_name = pokeData["name"].asString();
	_maxHealth = pokeData["HP"].asInt();
	_type = pokeData["type"].asString();
	_speed = pokeData["speed"].asInt();
	_health = _maxHealth;
}

void Entity::RenderEntity(SDL_Renderer& renderer)
{
	RenderHealthBar(renderer);
	SDL_RenderCopy(&renderer, _image, nullptr, &_renderRect);
	SDL_RenderPresent(&renderer);
}

void Entity::RenderHealthBar(SDL_Renderer& renderer)
{
	_healthBar.RenderHealthBar(renderer, (float)_maxHealth, (float)_health);
}

void Entity::DoAttack(Entity& target)
{
	--_attacks[_selectedAttackNum];
	_attacks[_selectedAttackNum].SetMissed((rand() % 100) > _attacks[_selectedAttackNum].Accuracy());
	if (_attacks[_selectedAttackNum].Missed())
	{
		_messages.emplace_back("But it missed!");
		return;
	}
	target.TakeDamage( *this, _attacks[_selectedAttackNum]);
}

void Entity::TakeDamage(Entity& attacker, const Attack& attack)
{
	float healthMultiplier = 1.f;
	if (!attack.Missed())
	{
		int critical = rand() % 100;
		if (critical > 90)
		{
			attacker._messages.emplace_back("Critical Hit!");
			healthMultiplier *= 1.2f;
		}
		if ((attack.Type() == "Water" && _type == "Fire") || (attack.Type() == "Grass" && _type == "Water") || (attack.Type() == "Fire" && _type == "Grass"))
		{
			attacker._messages.emplace_back("It's super effective!");
			healthMultiplier *= 1.4f;
		}
		if ((attack.Type() == "Fire" && _type == "Water") || (attack.Type() == "Water" && _type == "Grass") || (attack.Type() == "Grass" && _type == "Fire"))
		{
			attacker._messages.emplace_back("It's not very effective...");
			healthMultiplier *= 0.8f;
		}
	}
	else
		healthMultiplier = 0.f;
	_health -= static_cast<int>(healthMultiplier * attack.Damage());
}

const std::string Entity::GetNextMessage()
{
	if (!_messages.empty())
	{
		std::string message = _messages.front();
		_messages.pop_front();
		return message;
	}

	return {};
}

void Entity::SelectAttack()
{
	if (_health <= 0)
		return;

	_messages.clear();
	_messages.emplace_back(_name + " used " + _attacks[_selectedAttackNum].Name());
}