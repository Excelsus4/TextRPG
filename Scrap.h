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
	virtual string GetName() const override;
	string GetDescription() const;
	virtual int GetAmount() const override;
	virtual bool isStackable() const override { return true; };
	virtual void StackItem(int amount) override;
	virtual int Sell() const override;
private:
	string Name;
	string Description;
	int StackedAmount;
};

