#include "stdafx.h"
#include "Scrap.h"

Scrap::Scrap(string Name, string Description, int Value) :
	Name(Name), Description(Description), Value(Value), StackedAmount(1)
{
}

Scrap::~Scrap()
{
}

Scrap::Scrap(const Scrap & src):
	Name(src.GetName()), Description(src.GetDescription()), Value(src.GetValue())
{
}

Scrap::Scrap(const Scrap & src, int amount):
Name(src.GetName()), Description(src.GetDescription()), Value(src.GetValue()), StackedAmount(src.GetAmount() * amount)
{
}

string Scrap::GetName() const
{
	return Name;
}

int Scrap::GetValue() const
{
	return Value;
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
