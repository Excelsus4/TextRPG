#pragma once
#include "stdafx.h"
#include "Item.h"

struct GainChance {
	GainChance(Item* target, float chance, int min, int max) :
		item(target), chance(chance), minAmount(min), maxAmount(max) {}
	Item* item;
	float chance;
	int minAmount;
	int maxAmount;
};