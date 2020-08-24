#pragma once
#include "stdafx.h"
#include "GameEngine.h"
#include "Player.h"
#include "Item.h"
#include "Library.h"
class TextRPG
{
public:
	TextRPG();
	~TextRPG();
	void Run();
	void GainItem(Equipment* item);
	void GainItem(Scrap* item);
private:
	void PrintTitle();
	int MainMenu();
	bool Encounter(int Index);
	bool RandomEncounter();
	void InventoryInteract();
	void ShopInteract();
	void UseItem(Item* item);
	void TryToGetItem(GainChance c);

	Player* player;
	vector<Item*> inventory;
	int gold;
	Library library;
	unordered_map<string, vector<Item*>::iterator> stackItemHash;
};

