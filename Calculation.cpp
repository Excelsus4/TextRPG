#pragma once
#include "stdafx.h"
#include "Calculation.h"
#include <cmath>
#pragma warning(disable: 4244)

int Calculation::DamageFormula(int damage, int armor)
{
	return damage;
}

int Calculation::GetRequiredEXP(int level)
{
	return 10 * pow(1.5, level - 1);
}
