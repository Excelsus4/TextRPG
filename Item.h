#pragma once
#include "stdafx.h"
class Item
{
public:
	Item();
	virtual ~Item();
	Item(const Item& src);
	virtual string GetName() const = 0;
	virtual int GetValue() const = 0;
	virtual void StackItem(int amount) = 0;
	virtual int Sell() const = 0;
};

