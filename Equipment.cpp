#include "stdafx.h"
#include "Equipment.h"

Equipment::Equipment(EquipmentType::slot sl, statistics stat, int value) :
	Item(value), Slot(sl), Statistics(stat)
{
}

Equipment::~Equipment()
{
}

Equipment::Equipment(const Equipment & src)
	: Item(src), Slot(src.GetSlot()), Statistics(src.GetStat())
{
}

string Equipment::GetName() const
{
	return Statistics.Name;
}

void Equipment::StackItem(int amount)
{
	// 같은 아이템을 제물삼아서 강화?
	cout << "Exception: 미구현된 함수 호출 @ Equipment::StackItem(int)" << endl;
	return;
}

int Equipment::Sell() const
{
	return GetValue();
}
