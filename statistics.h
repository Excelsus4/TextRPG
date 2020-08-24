#pragma once
#include "stdafx.h"

struct statistics {
	string Name;
	int Hp;
	int Attack;
	int Level;
	int Strength;
	int Agility;

	statistics operator+(statistics rhs);
};