#pragma once
#include "stdafx.h"
#include "Character.h"

Character::Character(statistics stat)
	:Statistics(stat)
{
	Status.Hp = Statistics.Hp;
}

Character::~Character()
{
}

Character::Character(const Character & src)
	:Statistics(src.Statistics), Status(src.Status)
{
}

bool Character::isAlive()
{
	return Status.Hp > 0;
}
