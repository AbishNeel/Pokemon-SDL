#include "Game.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <string>
#undef main

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

using namespace Pokemon;

int main()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	std::string playerPokemonName, enemyPokemonName;
	std::cout << "Welcome to Pokemon!" << std::endl << "Choose your pokemon!" << std::endl << ">";
	std::cin >> playerPokemonName;
	while (playerPokemonName != "charmander" && playerPokemonName != "squirtle" && playerPokemonName != "bulbasaur")
	{
		std::cout << "Uh.... just pick one of the gen 1 starters dummy!!!" << std::endl << ">";
		std::cin >> playerPokemonName;
	}

	if (playerPokemonName == "charmander")
		enemyPokemonName = "squirtle";
	else if (playerPokemonName == "squirtle")
		enemyPokemonName = "bulbasaur";
	else
		enemyPokemonName = "charmander";

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 255, 160, 255);

	std::string jsonPath = "content/pokemon.json";
	Json::Value pokeData;

	std::ifstream jsonStream(jsonPath, std::ifstream::binary);
	jsonStream >> pokeData;

	Game game{ *window, *renderer, pokeData, playerPokemonName, enemyPokemonName};
	game.Run();

	SDL_Quit();

	return EXIT_SUCCESS;
}