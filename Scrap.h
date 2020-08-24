#pragma once
#include "Item.h"
class Scrap :
	public Item
{
public:
	Scrap(string Name, string Description, int Value);
	virtual ~Scrap();
	Scrap(const Scrap& src);
	Scrap(const Scrap& src, int amount);
	Scrap& operator+(int amount);
	Scrap& operator*(int amount);
	Scrap& operator+=(int amount);
	virtual string GetName() const override;
	virtual int GetValue() const override;
	string GetDescription() const;
	int GetAmount() const;
private:
	string Name;
	string Description;
	int Value;
	int StackedAmount;
};

