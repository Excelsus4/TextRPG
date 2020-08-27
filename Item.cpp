#pragma once
#include "stdafx.h"
#include "Item.h"

Item::Item(int value):
	value(value)
{
}

Item::~Item()
{
}

Item::Item(const Item & src):
	value(src.GetValue())
{
}

int Item::GetValue() const
{
	return value;
}
