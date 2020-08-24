#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Item.h"
#include "GainChance.h"

class Mob :
	public Character
{
public:
	Mob(statistics stat, int exp, vector<GainChance> item);
	virtual ~Mob() override;
	Mob(const Mob& src);
	virtual void Update(IEngine* engine) override;
	virtual bool DealDamage(int damage, float accuracy, float criticalChance) override;
	virtual void Scout(int scoutLevel);
	int getExpReward() const { return expReward; }
	vector<GainChance> getItemReward() const { return itemReward; }
private:
	int expReward;
	vector<GainChance> itemReward;
};

