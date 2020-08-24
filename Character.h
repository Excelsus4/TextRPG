#pragma once
#include "stdafx.h"
#include "IEntity.h"
#include "IDamager.h"
#include "statistics.h"

struct status {
	int Hp;
};

class Character : public IEntity, IDamager
{
public:
	Character(statistics stat);
	virtual ~Character();
	Character(const Character& src);
	virtual bool isAlive();
protected:
	statistics Statistics;
	status Status;
};