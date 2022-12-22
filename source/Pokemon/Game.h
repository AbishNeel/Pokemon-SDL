#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include <string>
#include <json/json.h>

namespace Pokemon
{
	enum GameState
	{
		GameText,
		PlayerMove,
		PlayerDialogueActive,
		PlayerAttackFeedback,
		EnemyDialogueActive,
		EnemyAttackFeedback,

		SIZE
	};

	class Game
	{
	public:
		Game(SDL_Window& window, SDL_Renderer& renderer, const Json::Value& pokeData,
			const std::string& playerPokemonName, const std::string& enemyPokemonName);
		void Run();

	private:
		void Start();
		void GetInput();
		void SpaceBarInput();
		bool IsPlayerAttackFaster();

		SDL_Window& _window;
		SDL_Renderer& _renderer;
		SDL_Texture* _backgroundTexture;

		Player _playerPokemon;
		Enemy _enemyPokemon;
		Dialogue _dialogueBox;

		std::string _message;

		bool _isRunning;
		GameState _gameState;
	};
}

