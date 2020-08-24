#pragma once

enum TargetType {
	PlayerSingle, MobSingle
};

class IEngine {
public:
	virtual void CallbackAttack(TargetType target, int damage, float accuracy, float critChance)=0;
};