#include "stdafx.h"
#include "HealthPotion.h"

HealthPotion::HealthPotion(string name, string des, int size, int value):
	Consumable(name, des, value, 1), Amount(size)
{
}

HealthPotion::HealthPotion(string name, string des, int size, int value, int stack):
	Consumable(name, des, value, stack), Amount(size)
{
}

HealthPotion::~HealthPotion()
{
}

HealthPotion::HealthPotion(const HealthPotion & src):
	Consumable(src), Amount(src.Amount)
{
}

void HealthPotion::Apply(Character * chara)
{
	chara->Heal(Amount);
}
