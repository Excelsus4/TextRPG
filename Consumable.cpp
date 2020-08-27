#include "stdafx.h"
#include "Consumable.h"

Consumable::Consumable(string name, string des, int value, int stack) :
	Item(value), Name(name), Description(des), StackedAmount(stack)
{
}

Consumable::~Consumable()
{
}

Consumable::Consumable(const Consumable & src):
	Item(src), Name(src.GetName()), Description(src.GetDescription()), StackedAmount(src.StackedAmount)
{
}

void Consumable::StackItem(int amount)
{
	StackedAmount += amount;
}

int Consumable::Sell() const
{
	return GetValue() * StackedAmount;
}

string Consumable::GetName() const
{
	return Name;
}

string Consumable::GetDescription() const
{
	return Description;
}
