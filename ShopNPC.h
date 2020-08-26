#pragma once
#include "stdafx.h"
#include "Item.h"
class ShopNPC
{
public:
	ShopNPC(vector<pair<Item*, int>> salesList);
	virtual ~ShopNPC();
	void GetShoppingList() const;
	bool BuyItem(int index, int money);
private:
	vector<pair<Item*, int>> itemStand;
};

