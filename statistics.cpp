#include "stdafx.h"
#include "statistics.h"

statistics statistics::operator+(statistics rhs)
{
	statistics result;
	result.Name = Name;
	result.Hp = Hp + rhs.Hp;
	result.Attack = Attack + rhs.Attack;
	result.Level = Level;
	result.Strength = Strength + rhs.Strength;
	result.Agility = Agility + rhs.Agility;
	return result;
}
