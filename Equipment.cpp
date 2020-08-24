#include "stdafx.h"
#include "Equipment.h"

Equipment::Equipment(EquipmentType::slot sl, statistics stat) :
	Slot(sl), Statistics(stat)
{
}

Equipment::~Equipment()
{
}

Equipment::Equipment(const Equipment & src)
	: Slot(src.GetSlot()), Statistics(src.GetStat())
{
}

string Equipment::GetName() const
{
	return Statistics.Name;
}

int Equipment::GetValue() const
{
	return 0;
}
