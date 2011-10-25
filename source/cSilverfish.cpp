#include "cSilverfish.h"

#include "Vector3f.h"
#include "Vector3d.h"

#include "Defines.h"

#include "cRoot.h"
#include "cWorld.h"
#include "cPickup.h"
#include "cItem.h"
#include "cMonsterConfig.h"

#include "cMCLogger.h"

#ifndef _WIN32
#include <stdlib.h> // rand()
#include <cstring>
#endif

cSilverfish::cSilverfish() : m_ChaseTime(999999) {
	m_bBurnable = true;
	m_EMPersonality = AGGRESSIVE;
	m_bPassiveAggressive = true;
	//m_AttackRate = 1;
	m_MobType = 60;
	GetMonsterConfig("Silverfish");
}

cSilverfish::~cSilverfish()
{
}

bool cSilverfish::IsA( const char* a_EntityType )
{
    //LOG("IsA( cSilverfish ) : %s", a_EntityType);
	if( strcmp( a_EntityType, "cSilverfish" ) == 0 ) return true;
	return cMonster::IsA( a_EntityType );
}

void cSilverfish::Tick(float a_Dt)
{
	cMonster::Tick(a_Dt);
}

void cSilverfish::KilledBy( cEntity* a_Killer )
{
	if( (rand() % 5) == 0 )
	{
		cPickup* Pickup = new cPickup( (int)(m_Pos->x*32), (int)(m_Pos->y*32), (int)(m_Pos->z*32), cItem( E_ITEM_EGG, 1 ) );
		Pickup->Initialize();
	}
	if( (rand() % 1) == 0 )
	{
		cPickup* Pickup = new cPickup( (int)(m_Pos->x*32), (int)(m_Pos->y*32), (int)(m_Pos->z*32), cItem( E_ITEM_FEATHER, 1 ) );
		Pickup->Initialize();
	}
	cMonster::KilledBy( a_Killer );
}

//What to do if in Idle State
void cSilverfish::InStateIdle(float a_Dt) {
	cMonster::InStateIdle(a_Dt);	
}

//What to do if in Chasing State
void cSilverfish::InStateChasing(float a_Dt) {
	cMonster::InStateChasing(a_Dt);
	m_ChaseTime += a_Dt;
	if( m_Target )
	{
		Vector3f Pos = Vector3f( m_Pos );
		Vector3f Their = Vector3f( m_Target->GetPosition() );
		if( (Their - Pos).Length() <= m_AttackRange) {
			cMonster::Attack(a_Dt);
		}
		MoveToPosition( Their + Vector3f(0, 0.65f, 0) );
	} else if( m_ChaseTime > 5.f ) {
		m_ChaseTime = 0;
		m_EMState = IDLE;
	}	
} 

void cSilverfish::InStateEscaping(float a_Dt) {
	cMonster::InStateEscaping(a_Dt);
}

void cSilverfish::GetMonsterConfig(const char* pm_name) {
	LOG("I am gettin my attributes: %s", pm_name);
	cRoot::Get()->GetMonsterConfig()->Get()->AssignAttributes(this,pm_name);
}
