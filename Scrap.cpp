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

Scrap & Scrap::operator+(int amount)
{
	StackedAmount += amount;
	return *this;
}

Scrap & Scrap::operator*(int amount)
{
	StackedAmount *= amount;
	return *this;
}

Scrap & Scrap::operator+=(int amount)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
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
