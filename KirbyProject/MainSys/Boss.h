#pragma once

#include "../GameDev/GameDev.h"
#include "BossState.h"
#include "BlockManager.h"
#include "Kirby.h"
#include <list>

class Boss : public singleton<Boss>, public statemachine, public Object
{
	friend class singleton<Boss>;
	friend class Object;
	friend class statemachine;

private :
	Boss();
	~Boss();

public :

	void Load();
	void Input(DWORD);
	void Draw(HDC hdc);
	void Update(DWORD);
	void Setposition(const Point& ppt, const Point& kpt, const bool& back);

	Vector GetPosition() const;

	Point RetrunBossPos() const;

	Rect GetRect() const;
	Rect GetBBoxRect() const;

	BYTE ReturnType() const;

	void SetPlayerPos(const LONG& px);
	void SetDrainRect(const Rect& rc);

	void DeadSet(const BYTE& st);

	void GetStarHit(const bool& hit);
	void SetCutterHit(const bool& hit);

	BoundaryBox* getBBox();

	Rect DeadCon();

	void Reset();

	char ReturnHP() const;

private :
	void init();

private :
	Point BossPos;
	Point PlayerPos;
	Point KirbyPos;
	Rect KirbyRect;

	DWORD update_dt;
	DWORD update_dt2;
	Rect BossRect;

	char BossHp;
	BYTE BossHitCount;

	BYTE BossState;
	BYTE Wallcount;
	DWORD update_dt_hit;

	bool TickUpdate;

	LONG MoveAcc;
	int MoveAccCount;

	LONG MoveBoss;

	bool RageSet;

	bool Test;

	bool BackPosition;

	bool StarHit;
	bool CutterHit;

	BYTE DeadType;

	BoundaryBox* BBox;

	Rect DrainRect;
};

#define BossBase Boss::getReference()