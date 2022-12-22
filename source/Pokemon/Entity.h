#pragma once
#include <SDL.h>
#include <string>
#include "Dialogue.h"
#include "Attack.h"
#include <vector>
#include "HealthBar.h"
#include "Timer.h"
#include <deque>
#include <json/json.h>

namespace Pokemon
{
	class Entity
	{
	public:
		Entity();
		void CreateEntity(SDL_Renderer& renderer, const std::string imgName, int x, int y, int scaleX, int scaleY, const Json::Value pokeData);
		void TakeDamage(Entity& attacker,const Attack& attack);
		void RenderEntity(SDL_Renderer& renderer);
		void RenderHealthBar(SDL_Renderer& renderer);
		void DoAttack(Entity& target);
		const std::string GetNextMessage();
		virtual void SelectAttack();

		inline const std::string& Name() const { return _name; }
		inline const int& Health() const { return _health; }
		inline const int& Speed() const { return _speed; }
		inline const Attack& SelectedAttack() const { return _attacks[_selectedAttackNum]; }

	protected:
		SDL_Texture* _image;
		SDL_Rect _renderRect;
		HealthBar _healthBar;

		std::vector<Attack> _attacks;
		std::deque<std::string> _messages;

		std::string _name;
		std::string _type;
		int _imageWidth;
		int _imageHeight;
		int _health;
		int _maxHealth;
		int _speed;
		int _selectedAttackNum;
	};
}