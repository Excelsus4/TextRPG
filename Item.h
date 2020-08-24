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
};

