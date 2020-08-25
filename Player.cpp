#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Calculation.h"

Player::Player(statistics stat):
	Character(stat), CalculatedStats(stat)
{
	MainStat = &CalculatedStats.Strength;
	SubStat = &CalculatedStats.Agility;
	Exp = 0;
	RequiredExp = Calculation::GetRequiredEXP(Statistics.Level);
	Equipments[EquipmentType::Weapon] = nullptr;
	Equipments[EquipmentType::BodyArmor] = nullptr;
}

Player::~Player()
{
}

void Player::Update(IEngine* engine)
{
	if (!isAlive())
		return;
	int input;
	cout <<endl<< Statistics.Name << "은(는) 무엇을 할까?" << endl;
	cout << "1. 공격" << endl;
	cout << "입력> ";
	cin >> input;
	switch (input) {
	case 1:
		cout << endl << Statistics.Name << "은(는) ";
		{
			auto weaponIterator = Equipments.find(EquipmentType::Weapon);
			if (weaponIterator == Equipments.end())
				cout << "주먹";
			else
				cout << weaponIterator->second->GetName();
		}
		cout<<"을(를) 휘둘렀다!" << endl;
		engine->CallbackAttack(MobSingle, CalculateStatDamage(), 1.f, .3f);
		break;
	default:
		cout << "아무 일도 일어나지 않았다!" << endl;
	}
}

bool Player::DealDamage(int damage, float accuracy, float criticalChance)
{
	if (!isAlive())
		return true;
	int deal = Calculation::DamageFormula(damage, 0);
	cout << Statistics.Name << "이(가) " << deal << "의 피해를 입었다!" << endl;
	cout << "HP가 " << Status.Hp << "에서 ";
	Status.Hp -= deal;
	cout << Status.Hp << "(으)로 떨어졌다!" << endl;
	if (Status.Hp <= 0){
		cout << "윽, 이건 좀 아프다." << endl;
		cout << "You die..." << endl;
		return true;
	}
	return false;
}

void Player::DisplayStat()
{
	cout << endl << "이름\t: " << CalculatedStats.Name << endl;
	cout << "레벨\t: " << CalculatedStats.Level << endl;
	cout << "경험치\t: " << Exp << "/" << RequiredExp << endl;
	cout << "HP\t: " << Status.Hp << "/"; PrintDualNumeric(CalculatedStats.Hp, Statistics.Hp); cout << endl;
	cout << "공격력\t: "; PrintDualNumeric(CalculatedStats.Attack, Statistics.Attack); cout << endl;
	cout << "힘\t: "; PrintDualNumeric(CalculatedStats.Strength, Statistics.Strength); cout << endl;
	cout << "민첩\t: "; PrintDualNumeric(CalculatedStats.Agility, Statistics.Agility); cout << endl;
	cout << "대미지\t: " << CalculateStatDamage() << endl;
	PrintEquipment("무기", EquipmentType::Weapon);
	PrintEquipment("갑옷", EquipmentType::BodyArmor);
}

void Player::GainEXP(int amount)
{
	cout << "경험치를 " << amount << " 획득했다!" << endl;
	Exp += amount;
	if (Exp >= RequiredExp) {
		Exp -= RequiredExp;
		LevelUp();
	}
}

void Player::Equip(Equipment* equipment)
{
	if (Equipments[equipment->GetSlot()] == equipment) {
		// 장착되어있는 것이랑 같은것
		cout << equipment->GetName() << "을(를) 해제했다!" << endl;
		Equipments[equipment->GetSlot()] = nullptr;
	}
	else {
		cout << equipment->GetName() << "을(를) 장착했다!" << endl;
		Equipments[equipment->GetSlot()] = equipment;
	}
	RecalculateStat();
}

bool Player::isEquiped(Equipment * equipment)
{
	if (Equipments[equipment->GetSlot()] == equipment)
		return true;
	else
		return false;
}

int Player::CalculateStatDamage()
{
	return CalculatedStats.Attack*(*MainStat)+(*SubStat);
}

void Player::PrintDualNumeric(int sum, int a)
{
	cout << sum;
	if (sum > a)
		cout << "(" << a << "+" << sum - a << ")";
}

void Player::PrintEquipment(string typeString, EquipmentType::slot typeSlot)
{
	cout << typeString<<"\t: ";
	if (Equipments[typeSlot] != nullptr)
		cout << Equipments[typeSlot]->GetName();
	cout << endl;
}

void Player::RecalculateStat()
{
	CalculatedStats = Statistics;
	for (auto equipPair : Equipments) {
		if(equipPair.second != nullptr)
			CalculatedStats = CalculatedStats + equipPair.second->GetStat();
	}
}

void Player::LevelUp()
{
	++Statistics.Level;
	Statistics.Strength += 3;
	++Statistics.Agility;
	Statistics.Hp += 35;
	Status.Hp = Statistics.Hp;
	RequiredExp = Calculation::GetRequiredEXP(Statistics.Level);
	cout << "레벨이 " << Statistics.Level << "(으)로 올랐다!" << endl;
	RecalculateStat();
}
