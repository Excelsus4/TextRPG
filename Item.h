#pragma once
#include "stdafx.h"
class Item
{
public:
	Item(int value);
	virtual ~Item();
	Item(const Item& src);
	virtual string GetName() const = 0;
	virtual int GetValue() const final;
	virtual void StackItem(int amount) = 0;
	virtual int Sell() const = 0;
private:
	int value;
};

