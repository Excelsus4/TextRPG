#pragma once
#include "stdafx.h"
#include "GameEngine.h"
#include "IEntity.h"
#include "Mob.h"
#include "Player.h"

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::AddEntity(Mob * entity)
{
	MobCollection.push_back(entity);
}

void GameEngine::AddEntity(Player * entity)
{
	PlayerCollection.push_back(entity);
}

bool GameEngine::Run()
{
	// return true if player wins, else return false
	bool result = false;

	cout << endl;
	for (Mob* e : MobCollection) {
		e->Scout(0);
	}

	while (true) {
		CycleUpdate();

		int AliveCounter = 0;

		for (Player* e : PlayerCollection) {
			if (e->isAlive())
				++AliveCounter;
		}
		if (AliveCounter <= 0)
			return false;

		AliveCounter = 0;

		for (Mob* e : MobCollection) {
			if (e->isAlive())
				++AliveCounter;
		}
		if (AliveCounter <= 0)
			return true;
	}
}

vector<GainChance> GameEngine::Award(Player* entity)
{
	vector<GainChance> result;
	int exp = 0;
	for (Mob* e : MobCollection) {
		exp += e->getExpReward();
		vector<GainChance> itemV = e->getItemReward();
		result.insert(result.end(), itemV.begin(), itemV.end());
	}
	entity->GainEXP(exp);
	return result;
}

void GameEngine::CallbackAttack(TargetType target, int damage, float accuracy, float critChance)
{
	// 순차적으로 하나씩 때리기
	bool temp = true;
	if (target == MobSingle) {
		for (size_t i = 0; temp&&i<MobCollection.size(); i++) {
			temp = MobCollection[i]->DealDamage(damage, accuracy, critChance);
		}
	}
	else if (target == PlayerSingle) {
		for (size_t i = 0; temp&&i<PlayerCollection.size(); i++) {
			temp = PlayerCollection[i]->DealDamage(damage, accuracy, critChance);
		}
	}
}

void GameEngine::CycleUpdate()
{
	for (Player* e : PlayerCollection) {
		e->Update(this);
	}
	for (Mob* e : MobCollection) {
		e->Update(this);
	}
}
