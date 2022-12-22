#include "Attack.h"

using namespace Pokemon;

Attack::Attack(std::string name, int damage, int accuracy, int speed, int pp, std::string type) : _name{name}, _damage{damage},
					_accuracy{accuracy}, _type{type}, _missed { false }, _speed{speed}, _pp{pp}, _maxPP{pp}
{

}