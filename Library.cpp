#pragma once
#include "stdafx.h"
#include "Library.h"
#include "GainChance.h"

Library::Library()
{
	statistics stat;

	// ��� ������Ÿ�� ����
	stat.Name = "����� ���Ĵ�";
	stat.Hp = 0;
	stat.Attack = 5;
	stat.Level = 0;
	stat.Strength = 0;
	stat.Agility = 0;
	EquipmentBook.push_back(new Equipment(EquipmentType::Weapon, stat));

	stat.Name = "���� Ʃ��";
	stat.Hp = 25;
	stat.Attack = 0;
	stat.Level = 0;
	stat.Strength = 0;
	stat.Agility = 0;
	EquipmentBook.push_back(new Equipment(EquipmentType::BodyArmor, stat));

	// ��ũ�� ������Ÿ�� ����
	ScrapBook.push_back(new Scrap("����� ��", "�ż��ϰ� �߶� ��� ��", 4));
	ScrapBook.push_back(new Scrap("��ũ�� ��", "�ż��ϰ� �߶� ��ũ�� ��", 12));

	// ���� ������Ÿ�� ����
	stat.Name = "���";
	stat.Hp = 70;
	stat.Attack = 7;
	stat.Level = 1;
	stat.Strength = 0;
	stat.Agility = 0;
	MonsterBook.push_back(new Mob(stat, 7, { GainChance(ScrapBook[0], .6f, 1, 2) }));

	stat.Name = "��ũ";
	stat.Hp = 160;
	stat.Attack = 12;
	stat.Level = 3;
	stat.Strength = 0;
	stat.Agility = 0;
	MonsterBook.push_back(new Mob(stat, 21, {}));
}

Library::~Library()
{
	// ���� �޸� ����
	for (Mob* mob : MonsterBook) {
		delete mob;
	}

	// ��� �޸� ����
	for (Equipment* eq : EquipmentBook) {
		delete eq;
	}

	// ��ũ�� �޸� ����
	for (Scrap* eq : ScrapBook) {
		delete eq;
	}
}

Mob* Library::GetMobByIndex(int index)
{
	return MonsterBook[index];
}

Equipment * Library::GetEquipByIndex(int index)
{
	return EquipmentBook[index];
}

Scrap * Library::GetScrapByIndex(int index)
{
	return ScrapBook[index];
}
