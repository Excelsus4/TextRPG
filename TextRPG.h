#pragma once
#include "stdafx.h"
#include "GameEngine.h"
#include "Player.h"
#include "Item.h"
#include "Library.h"
#include "ShopNPC.h"

class TextRPG
{
public:
	TextRPG();
	virtual ~TextRPG();
	void Run();
	void GainItem(Item* item);
	void GainGold(int gold);
private:
	void PrintTitle();
	int MainMenu();
	bool Encounter(int Index);
	bool RandomEncounter();
	void InventoryInteract();
	void ShopInteract();
	void UseItem(Item* item);
	void TryToGetItem(GainChance c);
	int PrintInventory();
	int GetInput();
	bool RemoveItemSafely(vector<Item*>::iterator item);

	Player* player;
	vector<Item*> inventory;
	int gold;
	Library library;
	unordered_map<string, Item*> stackItemHash;
	ShopNPC* villageShop;
};

