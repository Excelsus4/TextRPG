#pragma once
#include "Consumable.h"
class HealthPotion :
	public Consumable
{
public:
	HealthPotion(string name, string des, int size, int value);
	HealthPotion(string name, string des, int size, int value, int stack);
	virtual ~HealthPotion();
	HealthPotion(const HealthPotion& src);
	HealthPotion(const HealthPotion& src, int mult);
	virtual void Apply(Character* chara) override;
private:
	int Amount;
};

