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
	virtual void StackItem(int amount) override;
	virtual int Sell() const override;
	virtual void Apply(Character* chara) = 0;
	virtual string GetName() const;
	string GetDescription() const;
protected:
	string Name;
	string Description;
	int StackedAmount;
};

