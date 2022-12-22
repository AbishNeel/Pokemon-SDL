#include "Timer.h"
#include <SDL.h>

using namespace Pokemon;

Timer::Timer() : _startSeconds { (int)SDL_GetTicks()}, _timerLimit{0}, _isActive{false}
{
}

void Timer::StartTimer(int seconds)
{
	_isActive = true;
	_startSeconds = SDL_GetTicks();
	_timerLimit = seconds;
}

void Timer::Update()
{
	if ((SDL_GetTicks() - _startSeconds) / Uint32(1000 > _timerLimit))
		StopTimer();
}

void Timer::StopTimer()
{
	_startSeconds = 0;
	_timerLimit = 0;
	_isActive = false;
}