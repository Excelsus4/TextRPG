#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Equipment.h"

class Player : public Character
{
public:
	Player(statistics stat);
	virtual ~Player() override;
	virtual void Update(IEngine* engine) override;
	virtual bool DealDamage(int damage, float accuracy, float criticalChance) override;
	void DisplayStat();
	void GainEXP(int amount);
	void Equip(Equipment* equipment);
	bool isEquiped(Equipment* equipment);
private:
	int* MainStat;
	int* SubStat;
	int Exp;
	int RequiredExp;
	map<EquipmentType::slot, Equipment*> Equipments;
	statistics CalculatedStats;

	int CalculateStatDamage();
	void PrintDualNumeric(int sum, int a);
	void PrintEquipment(string typeString, EquipmentType::slot typeSlot);
	void RecalculateStat();
	void LevelUp();
};

