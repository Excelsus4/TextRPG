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
	Equipment(EquipmentType::slot sl, statistics stat);
	virtual ~Equipment();
	Equipment(const Equipment& src);
	EquipmentType::slot GetSlot() const { return Slot; };
	statistics GetStat() const { return Statistics; };
	virtual string GetName() const override;
	virtual int GetValue() const override;
private:
	EquipmentType::slot Slot;
	statistics Statistics;
};

