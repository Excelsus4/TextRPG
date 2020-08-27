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
	EquipmentBook.push_back(new Equipment(EquipmentType::Weapon, stat, 25));

	stat.Name = "���� Ʃ��";
	stat.Hp = 25;
	stat.Attack = 0;
	stat.Level = 0;
	stat.Strength = 0;
	stat.Agility = 0;
	EquipmentBook.push_back(new Equipment(EquipmentType::BodyArmor, stat, 10));

	stat.Name = "������ ����Į����";
	stat.Hp = 80;
	stat.Attack = 145;
	stat.Level = 0;
	stat.Strength = 30;
	stat.Agility = 15;
	EquipmentBook.push_back(new Equipment(EquipmentType::Weapon, stat, 1500));

	stat.Name = "�䵵 ���󸶻�";
	stat.Hp = -10;
	stat.Attack = 75;
	stat.Level = 0;
	stat.Strength = 0;
	stat.Agility = 20;
	EquipmentBook.push_back(new Equipment(EquipmentType::Weapon, stat, 300));

	// ��ũ�� ������Ÿ�� ����
	ScrapBook.push_back(new Scrap("����� ��", "�ż��ϰ� �߶� ��� ��", 4));
	ScrapBook.push_back(new Scrap("��ũ�� ��", "�ż��ϰ� �߶� ��ũ�� ��", 12));
	ScrapBook.push_back(new Scrap("����", "���� ��ü���� �����ϰ� ������ ����", 3000));
	ScrapBook.push_back(new Scrap("������� ��", "����ſ� ���� ����־�?", 60));

	// ���� ������Ÿ�� ����
	stat.Name = "���";
	stat.Hp = 70;
	stat.Attack = 7;
	stat.Level = 1;
	stat.Strength = 0;
	stat.Agility = 0;
	MonsterBook.push_back(new Mob(stat, 7, { 
		GainChance(ScrapBook[0], .6f, 1, 2),
		GainChance(ScrapBook[2], .01f, 1, 1) }));

	stat.Name = "��ũ";
	stat.Hp = 320;
	stat.Attack = 20;
	stat.Level = 3;
	stat.Strength = 0;
	stat.Agility = 0;
	MonsterBook.push_back(new Mob(stat, 21, { 
		GainChance(ScrapBook[1], .8f, 1, 1),
		GainChance(ScrapBook[2], .03f, 1, 1) }));

	stat.Name = "�����";
	stat.Hp = 1600;
	stat.Attack = 75;
	stat.Level = 15;
	stat.Strength = 0;
	stat.Agility = 0;
	MonsterBook.push_back(new Mob(stat, 21, {
		GainChance(ScrapBook[3], .3f, 1, 15),
		GainChance(ScrapBook[2], .15f, 1, 1) }));
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
