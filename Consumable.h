#pragma once
#include "stdafx.h"
#include "Item.h"
#include "Player.h"
class Consumable :
	public Item
{
public:
	Consumable(string name, string des, int value, int stack);
	virtual ~Consumable();
	Consumable(const Consumable& src);
	Consumable(const Consumable& src, int mult);
	virtual bool isStackable() const override { return true; };
	virtual void StackItem(int amount) override;
	virtual int Sell() const override;
	virtual void Apply(Character* chara) = 0;
	virtual string GetName() const;
	virtual int GetAmount() const;
	string GetDescription() const;
protected:
	string Name;
	string Description;
	int StackedAmount;
};

