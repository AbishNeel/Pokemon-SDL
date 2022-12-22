#pragma once
#include <string>

namespace Pokemon
{
	class Attack
	{
	public:
		Attack(std::string name, int damage, int accuracy, int speed, int pp, std::string type);

		void operator--() { --_pp; }

		inline const std::string& Name() const { return _name; }
		inline const std::string& Type() const { return _type; }
		inline const int Damage() const { return _damage; }
		inline const int Accuracy() const { return _accuracy; }
		inline const int Speed() const { return _speed; }
		inline const int PP() const { return _pp; }
		inline const int MaxPP() const { return _maxPP; }
		inline const bool& Missed() const { return _missed; }
		inline void SetMissed(bool value) { _missed = value; }

	private:
		std::string _name;
		int _damage;
		int _accuracy;
		std::string _type;
		int _speed;
		int _pp;
		int _maxPP;
		bool _missed;
	};
}