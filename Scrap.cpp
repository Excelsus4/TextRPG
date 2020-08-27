#include "stdafx.h"
#include "Scrap.h"

Scrap::Scrap(string Name, string Description, int Value) :
	Item(Value), Name(Name), Description(Description), StackedAmount(1)
{
}

Scrap::~Scrap()
{
}

Scrap::Scrap(const Scrap & src):
	Item(src),Name(src.GetName()), Description(src.GetDescription())
{
}

Scrap::Scrap(const Scrap & src, int amount):
	Item(src), Name(src.GetName()), Description(src.GetDescription()), StackedAmount(src.GetAmount() * amount)
{
}

string Scrap::GetName() const
{
	return Name;
}

string Scrap::GetDescription() const
{
	return Description;
}

int Scrap::GetAmount() const
{
	return StackedAmount;
}

void Scrap::StackItem(int amount)
{
	StackedAmount += amount;
}

int Scrap::Sell() const
{
	return GetValue() * GetAmount();
}
