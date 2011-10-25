#pragma once

#include "cMonster.h"

class cEnderman : public cMonster
{
public:
	cEnderman();
	~cEnderman();

	virtual bool IsA( const char* a_EntityType );
	virtual void GetMonsterConfig(const char* pm_name);

	virtual void Tick(float a_Dt);
	virtual void KilledBy( cEntity* a_Killer );
	virtual void InStateIdle(float a_Dt);
	virtual void InStateChasing(float a_Dt);
	virtual void InStateEscaping(float a_Dt);
	//float m_ChaseTime;
protected:
	float m_ChaseTime;
};
