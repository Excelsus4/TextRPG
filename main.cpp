#pragma once
#include "stdafx.h"
#include "TextRPG.h"
#include "RandomEngine.h"

int main()
{
	random_device rd;
	Random::gen = new mt19937(rd());

	TextRPG game;
	game.Run();

	delete Random::gen;
}
