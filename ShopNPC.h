#pragma once
#include "stdafx.h"
#include "Item.h"

class ShopNPC
{
public:
	ShopNPC(vector<pair<Item*, int>> salesList);
	virtual ~ShopNPC();
	void GetShoppingList() const;
	Item* BuyItem(size_t index, int& money);
private:
	vector<pair<Item*, int>> itemStand;
};

