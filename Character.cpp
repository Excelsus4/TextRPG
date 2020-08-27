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

void Character::Heal(int amount)
{
	cout << Statistics.Name << "�� ü���� " << Status.Hp << "���� ";
	Status.Hp += amount;
	if (Status.Hp > Statistics.Hp)
		Status.Hp = Statistics.Hp;
	cout << Status.Hp << "(��)�� ȸ���Ǿ���!" << endl;
}
