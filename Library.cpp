#pragma once
#include "stdafx.h"
#include "Library.h"
#include "GainChance.h"

Library::Library()
{
	statistics stat;

	// 장비 프로토타입 생성
	stat.Name = "평범한 스파다";
	stat.Hp = 0;
	stat.Attack = 5;
	stat.Level = 0;
	stat.Strength = 0;
	stat.Agility = 0;
	EquipmentBook.push_back(new Equipment(EquipmentType::Weapon, stat));

	stat.Name = "가죽 튜닉";
	stat.Hp = 25;
	stat.Attack = 0;
	stat.Level = 0;
	stat.Strength = 0;
	stat.Agility = 0;
	EquipmentBook.push_back(new Equipment(EquipmentType::BodyArmor, stat));

	// 스크랩 프로토타입 생성
	ScrapBook.push_back(new Scrap("고블린의 귀", "신선하게 잘라낸 녹색 귀", 4));
	ScrapBook.push_back(new Scrap("오크의 코", "신선하게 잘라낸 오크의 코", 12));

	// 몬스터 프로토타입 생성
	stat.Name = "고블린";
	stat.Hp = 70;
	stat.Attack = 7;
	stat.Level = 1;
	stat.Strength = 0;
	stat.Agility = 0;
	MonsterBook.push_back(new Mob(stat, 7, { GainChance(ScrapBook[0], .6f, 1, 2) }));

	stat.Name = "오크";
	stat.Hp = 160;
	stat.Attack = 12;
	stat.Level = 3;
	stat.Strength = 0;
	stat.Agility = 0;
	MonsterBook.push_back(new Mob(stat, 21, {}));
}

Library::~Library()
{
	// 몬스터 메모리 해제
	for (Mob* mob : MonsterBook) {
		delete mob;
	}

	// 장비 메모리 해제
	for (Equipment* eq : EquipmentBook) {
		delete eq;
	}

	// 스크랩 메모리 해제
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
