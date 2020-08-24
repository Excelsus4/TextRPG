#pragma once
#include "stdafx.h"
#include "Mob.h"
#include "Player.h"
#include "IEngine.h"
#include "IDamager.h"
#include "GainChance.h"

class GameEngine:
	public IEngine
{
public:
	GameEngine();
	virtual ~GameEngine();
	void AddEntity(class Mob* entity);
	void AddEntity(class Player* entity);
	bool Run();
	vector<GainChance> Award(class Player* entity);
	virtual void CallbackAttack(TargetType target, int damage, float accuracy, float critChance) override;
private:
	void CycleUpdate();
	std::vector<class Mob*> MobCollection;
	std::vector<class Player*> PlayerCollection;
};

