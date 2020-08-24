#pragma once
#include "stdafx.h"
#include "Mob.h"
#include "IEntity.h"
#include "Calculation.h"

Mob::Mob(statistics stat, int exp, vector<GainChance> item):
	Character(stat), expReward(exp), itemReward(item)
{
}

Mob::~Mob()
{
}

Mob::Mob(const Mob& src)
	:Character(src), expReward(src.getExpReward()), itemReward(src.getItemReward()) {
}

void Mob::Update(IEngine* engine)
{
	if (!isAlive())
		return;
	cout << endl<<Statistics.Name << "이(가) 공격을 한다." << endl;
	engine->CallbackAttack(PlayerSingle, Statistics.Attack, 1.f, .3f);
}

bool Mob::DealDamage(int damage, float accuracy, float criticalChance)
{
	if (!isAlive())
		return true;
	int deal = Calculation::DamageFormula(damage, 0);
	cout << Statistics.Name << "이(가) " << deal << "의 피해를 입었다!" << endl;
	Status.Hp -= deal;
	cout << Statistics.Name << "의 HP가 " << (int)(((float)Status.Hp / (float)Statistics.Hp)*100) << "퍼센트 남았다!" << endl;
	if (Status.Hp <= 0) {
		cout << Statistics.Name << "이(가) 쓰러졌다!" << endl;
		return true;
	}
	return false;
}

void Mob::Scout(int scoutLevel)
{
	cout << Statistics.Name << "이(가) 보인다." << endl;
	if (scoutLevel > 0) {
		cout << Statistics.Level << "레벨 인 것 같다." << endl;
	}
	if (scoutLevel > 1) {
		cout << Status.Hp << "만큼의 HP가 남아있는 것 같다." << endl;
	}
}
