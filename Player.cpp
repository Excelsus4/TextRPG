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
}

Player::~Player()
{
}

void Player::Update(IEngine* engine)
{
	if (!isAlive())
		return;
	int input;
	cout <<endl<< Statistics.Name << "��(��) ������ �ұ�?" << endl;
	cout << "1. ����" << endl;
	cout << "�Է�> ";
	cin >> input;
	switch (input) {
	case 1:
		cout << endl << Statistics.Name << "��(��) ";
		{
			auto weaponIterator = Equipments.find(EquipmentType::Weapon);
			if (weaponIterator == Equipments.end())
				cout << "�ָ�";
			else
				cout << weaponIterator->second->GetName();
		}
		cout<<"��(��) �ֵѷ���!" << endl;
		engine->CallbackAttack(MobSingle, CalculateStatDamage(), 1.f, .3f);
		break;
	default:
		cout << "�ƹ� �ϵ� �Ͼ�� �ʾҴ�!" << endl;
	}
}

bool Player::DealDamage(int damage, float accuracy, float criticalChance)
{
	if (!isAlive())
		return true;
	int deal = Calculation::DamageFormula(damage, 0);
	cout << Statistics.Name << "��(��) " << deal << "�� ���ظ� �Ծ���!" << endl;
	cout << "HP�� " << Status.Hp << "���� ";
	Status.Hp -= deal;
	cout << Status.Hp << "(��)�� ��������!" << endl;
	if (Status.Hp <= 0){
		cout << "��, �̰� �� ������." << endl;
		cout << "You die..." << endl;
		return true;
	}
	return false;
}

void Player::DisplayStat()
{
	cout << endl << "�̸�\t: " << CalculatedStats.Name << endl;
	cout << "����\t: " << CalculatedStats.Level << endl;
	cout << "����ġ\t: " << Exp << "/" << RequiredExp << endl;
	cout << "HP\t: " << Status.Hp << "/"; PrintDualNumeric(CalculatedStats.Hp, Statistics.Hp); cout << endl;
	cout << "���ݷ�\t: "; PrintDualNumeric(CalculatedStats.Attack, Statistics.Attack); cout << endl;
	cout << "��\t: "; PrintDualNumeric(CalculatedStats.Strength, Statistics.Strength); cout << endl;
	cout << "��ø\t: "; PrintDualNumeric(CalculatedStats.Agility, Statistics.Agility); cout << endl;
	cout << "�����\t: " << CalculateStatDamage() << endl;
	PrintEquipment("����", EquipmentType::Weapon);
	PrintEquipment("����", EquipmentType::BodyArmor);
}

void Player::GainEXP(int amount)
{
	cout << "����ġ�� " << amount << " ȹ���ߴ�!" << endl;
	Exp += amount;
	if (Exp >= RequiredExp) {
		Exp -= RequiredExp;
		LevelUp();
	}
}

Equipment* Player::Equip(Equipment* equipment)
{
	Equipment* ret = nullptr;
	cout << equipment->GetName() << "��(��) �����ߴ�!" << endl;
	auto it = Equipments.find(equipment->GetSlot());
	if (it == Equipments.end()) {
		Equipments[equipment->GetSlot()] = equipment;
	}
	else {
		ret = it->second;
		it->second = equipment;
	}
	RecalculateStat();
	return ret;
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
	auto it = Equipments.find(typeSlot);
	if (it != Equipments.end())
		cout << it->second->GetName();
	cout << endl;
}

void Player::RecalculateStat()
{
	CalculatedStats = Statistics;
	for (auto equipPair : Equipments) {
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
	cout << "������ " << Statistics.Level << "(��)�� �ö���!" << endl;
	RecalculateStat();
}
