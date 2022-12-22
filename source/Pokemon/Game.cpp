#include "Game.h"
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_image.h>
#include "Player.h"

using namespace Pokemon;

Game::Game(SDL_Window& window, SDL_Renderer& renderer, const Json::Value& pokeData,
	       const std::string& playerPokemonName, const std::string& enemyPokemonName) : 
			_isRunning{ true }, _window { window }, _renderer { renderer },
			_playerPokemon { renderer, 80, 300, 3, 3, pokeData[playerPokemonName]},
			_enemyPokemon { renderer, 480, 60, 3, 3, pokeData[enemyPokemonName]}, 
			_dialogueBox { renderer, 0, 450, 500, 50 }, _gameState{GameState::GameText}
{
	_backgroundTexture = IMG_LoadTexture(&_renderer, "content/grassbg.png");
	_message = "A wild " + _enemyPokemon.Name() + " appeared!";
}

void Game::Start()
{
	SDL_Rect bgRect;
	bgRect.w = 800;
	bgRect.h = 600;
	bgRect.x = 0;
	bgRect.y = -150;
	SDL_RenderCopy(&_renderer, _backgroundTexture, nullptr, &bgRect);
	SDL_RenderPresent(&_renderer);

	_playerPokemon.RenderEntity(_renderer);
	_enemyPokemon.RenderEntity(_renderer);

	_dialogueBox.DisplayText(_message);
}

void Game::Run()
{
	Start();

	while (_isRunning)
	{
		GetInput();
	}
}

void Game::GetInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	SDL_KeyCode dKey = SDL_KeyCode::SDLK_d;
	SDL_KeyCode rightKey = SDL_KeyCode::SDLK_RIGHT;
	SDL_KeyCode aKey = SDL_KeyCode::SDLK_a;
	SDL_KeyCode leftKey = SDL_KeyCode::SDLK_LEFT;
	SDL_KeyCode wKey = SDL_KeyCode::SDLK_w;
	SDL_KeyCode upKey = SDL_KeyCode::SDLK_UP;
	SDL_KeyCode sKey = SDL_KeyCode::SDLK_s;
	SDL_KeyCode downKey = SDL_KeyCode::SDLK_DOWN;
	SDL_KeyCode spaceKey = SDL_KeyCode::SDLK_SPACE;
	SDL_KeyCode enterKey = SDL_KeyCode::SDLK_RETURN;

	switch (event.type)
	{
	case SDL_QUIT:
		_isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == spaceKey || event.key.keysym.sym == enterKey)
			SpaceBarInput();

		if (_gameState != GameState::PlayerMove)
			return;

		if (event.key.keysym.sym == dKey || event.key.keysym.sym == rightKey)
			_playerPokemon.ChangeAttackNum(1);
		else if (event.key.keysym.sym == aKey || event.key.keysym.sym == leftKey)
			_playerPokemon.ChangeAttackNum(-1);
		else if (event.key.keysym.sym == wKey || event.key.keysym.sym == upKey)
			_playerPokemon.ChangeAttackNum(-2);
		else if (event.key.keysym.sym == sKey || event.key.keysym.sym == downKey)
			_playerPokemon.ChangeAttackNum(2);

		_playerPokemon.RenderAttackDialogue();
		break;
	}
}

void Game::SpaceBarInput()
{
	if (_playerPokemon.Health() <= 0)
	{
		_gameState = GameState::GameText;
		_message = _playerPokemon.Name() + " fainted!";
		_dialogueBox.DisplayText(_message);
		return;
	}

	if (_enemyPokemon.Health() <= 0)
	{
		_gameState = GameState::GameText;
		_message = _enemyPokemon.Name() + " fainted!";
		_dialogueBox.DisplayText(_message);
		return;
	}

	_message.clear();
	switch (_gameState)
	{
	case GameState::GameText:
		_playerPokemon.RenderAttackDialogue();
		_message.clear();
		_gameState = GameState::PlayerMove;
		break;

	case GameState::PlayerMove:
		_playerPokemon.SelectAttack();
		if (_playerPokemon.SelectedAttack().PP() <= 0)
		{
			_message = "Out of PP!";
			_dialogueBox.DisplayText(_message);
			_gameState = GameState::GameText;
			return;
		}
		_enemyPokemon.SelectAttack();
		if (IsPlayerAttackFaster())
			_gameState = GameState::PlayerDialogueActive;
		else
			_gameState = GameState::EnemyDialogueActive;
		SpaceBarInput();
		break;

	case GameState::PlayerDialogueActive:
		_message = _playerPokemon.GetNextMessage();
		if (_message.empty())
		{
			_playerPokemon.DoAttack(_enemyPokemon);
			_gameState = GameState::PlayerAttackFeedback;
			SpaceBarInput();
		}
		break;

	case GameState::PlayerAttackFeedback:
		_message = _playerPokemon.GetNextMessage();
		if (_message.empty())
		{
			if (IsPlayerAttackFaster())
			{
				_gameState = GameState::EnemyDialogueActive;
				SpaceBarInput();
			}
			else
				_gameState = GameState::PlayerMove;
		}
		break;

	case GameState::EnemyDialogueActive:
		_message = _enemyPokemon.GetNextMessage();
		if (_message.empty())
		{
			_enemyPokemon.DoAttack(_playerPokemon);
			_gameState = GameState::EnemyAttackFeedback;
			SpaceBarInput();
		}
		break;

	case GameState::EnemyAttackFeedback:
		_message = _enemyPokemon.GetNextMessage();
		if (_message.empty())
		{
			if (IsPlayerAttackFaster())
				_gameState = GameState::PlayerMove;
			else
			{
				_gameState = GameState::PlayerDialogueActive;
				SpaceBarInput();
			}
		}
		break;
	}

	if (!_message.empty())
		_dialogueBox.DisplayText(_message);
	_playerPokemon.RenderHealthBar(_renderer);
	_enemyPokemon.RenderHealthBar(_renderer);
}

bool Game::IsPlayerAttackFaster()
{
	return _playerPokemon.Speed() + _playerPokemon.SelectedAttack().Speed() >= _enemyPokemon.Speed() + _enemyPokemon.SelectedAttack().Speed();
}