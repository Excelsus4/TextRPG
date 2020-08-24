#pragma once
#include "stdafx.h"
#include "Mob.h"
#include "Equipment.h"
#include "Scrap.h"
class Library
{
public:
	Library();
	~Library();
	Mob* GetMobByIndex(int index);
	size_t GetMobBookSize() { return MonsterBook.size(); };
	Equipment* GetEquipByIndex(int index);
	Scrap* GetScrapByIndex(int index);
private:
	vector<class Mob*> MonsterBook;
	vector<class Equipment*> EquipmentBook;
	vector<class Scrap*> ScrapBook;
};

