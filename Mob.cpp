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
	cout << endl<<Statistics.Name << "��(��) ������ �Ѵ�." << endl;
	engine->CallbackAttack(PlayerSingle, Statistics.Attack, 1.f, .3f);
}

bool Mob::DealDamage(int damage, float accuracy, float criticalChance)
{
	if (!isAlive())
		return true;
	int deal = Calculation::DamageFormula(damage, 0);
	cout << Statistics.Name << "��(��) " << deal << "�� ���ظ� �Ծ���!" << endl;
	Status.Hp -= deal;
	cout << Statistics.Name << "�� HP�� " << (int)(((float)Status.Hp / (float)Statistics.Hp)*100) << "�ۼ�Ʈ ���Ҵ�!" << endl;
	if (Status.Hp <= 0) {
		cout << Statistics.Name << "��(��) ��������!" << endl;
		return true;
	}
	return false;
}

void Mob::Scout(int scoutLevel)
{
	cout << Statistics.Name << "��(��) ���δ�." << endl;
	if (scoutLevel > 0) {
		cout << Statistics.Level << "���� �� �� ����." << endl;
	}
	if (scoutLevel > 1) {
		cout << Status.Hp << "��ŭ�� HP�� �����ִ� �� ����." << endl;
	}
}
