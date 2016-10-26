#pragma once

#include "../GameDev/GameDev.h"
#include "Kirby.h"
#include "EnemiesManager.h"
#include "BlockManager.h"
#include "StarShot.h"
#include "AirShot.h"
#include "EnemiesCutter.h"
#include "Cutter.h"
#include "Boss.h"
#include "BossIce.h"

class MissileManager : public singleton<MissileManager>
{
	friend class singleton<MissileManager>;
private :
	MissileManager();
	virtual ~MissileManager();

public :
	void StarPush(const Point& pt, const bool& bk);
	void AirPush(const Point& pt, const bool& bk);
	void ECutterPush(const Point& pt, const bool& bk);
	void CutterPush(const Point& pt, const bool& bk);
	void IceShotPush(const Point& pt, const bool& bk);
	void RageIceShotPush(const Point& pt, const bool& bk);

	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void SetStage(const BYTE& s);

private:
	std::list<StarShot*> StarDepot;
	std::list<AirShot*> AirDepot;
	std::list<EnemiesCutter*> ECutterDepot;
	std::list<Cutter*> CutterDepot;
	std::list<IceShot*> IceDepot;
	std::list<RageIceShot*> RageIceDepot;

	bool HitSound;

	BYTE Stage;

};

#define MissileDepot MissileManager::getReference()