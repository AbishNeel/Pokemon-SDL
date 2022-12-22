#pragma once

namespace Pokemon
{
	class Timer
	{
	public:
		Timer();
		void StartTimer(int seconds);
		void Update();
		void StopTimer();

		inline const bool& IsActive() const { return _isActive; }

	private:
		int _startSeconds;
		int _timerLimit;
		bool _isActive;
	};
}