#pragma once
class IDamager {
public:
	virtual bool DealDamage(int damage, float accuracy, float criticalChance) = 0;
};