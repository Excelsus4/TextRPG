#pragma once
#include "stdafx.h"
#include "Item.h"
#include "statistics.h"

namespace EquipmentType {
	enum slot {
		Weapon, BodyArmor
	};
}

class Equipment :
	public Item
{
public:
	Equipment(EquipmentType::slot sl, statistics stat, int value);
	virtual ~Equipment();
	Equipment(const Equipment& src);
	EquipmentType::slot GetSlot() const { return Slot; };
	statistics GetStat() const { return Statistics; };
	virtual string GetName() const override;
	virtual bool isStackable() const override { return false; };
	virtual void StackItem(int amount) override;
	virtual int Sell() const override;
	virtual int GetAmount() const override { return 1; };
private:
	EquipmentType::slot Slot;
	statistics Statistics;
};

