#pragma once
#include "stdafx.h"
#include "Item.h"

struct Sales {
	Sales(Item* it, int pr, int st) :item(it), price(pr), stack(st) {}
	Item* item;
	int price;
	int stack;
};

class ShopNPC
{
public:
	ShopNPC(vector<Sales> salesList);
	virtual ~ShopNPC();
	void GetShoppingList() const;
	Item* BuyItem(size_t index, int& money);
private:
	vector<Sales> itemStand;
};

