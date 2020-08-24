#pragma once
#include "stdafx.h"
#include "IEngine.h"
class IEntity {
public:
	virtual void Update(IEngine* engine) = 0;
};