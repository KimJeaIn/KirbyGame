#pragma once

#include "../GameDev/GameDev.h"
#include "CutterKirbyState.h"
#include "BlockManager.h"
#include "EnemiesManager.h"
#include "ItemManager.h"
#include "Boss.h"
#include <list>

class CutterKirby : public singleton<CutterKirby>, public Object, public statemachine
{
	friend class singleton<CutterKirby>;
	friend class Object;
	friend class statemachine;

private :
	CutterKirby();
	~CutterKirby();
public :
	void Load(const Rect& rc);
	void Input(DWORD);
	void Draw(HDC hdc);
	void Update(DWORD);
	void Setposition(const Point& ppt, const Point& kpt, const bool& back);

	Vector GetPosition() const;

	Point RetrunKirbyPos() const;
	Point RetrunPlayerPos() const;

	Rect ReturnDrainRect();

	bool ReturnBack() const;

	bool ReturnDead() const;
	bool ReturnEnd() const;

	void SetReset(const bool&);

	void KirbyReset();

	void CutterCho();

	bool ReturnType() const;

	void SetRerease();

	char ReturnHP() const;
	void SetMissileHit(const bool& bk);
	BoundaryBox* GetBBox() const;

private :
	void init();

private :
	Point KirbyPos;
	Point PlayerPos;
	DWORD update_dt;
	DWORD update_dt_hit;
	DWORD update_drain;
	Rect KirbyRect;

	BYTE KirbyState;
	int KirbyHp;
	BYTE KirbyHitCount;
	BYTE Wallcount;

	LONG MoveAcc;
	int MoveAccCount;

	bool BackPosition;
	bool DrainC;
	bool DrainIn;
	bool KirbyRerease;

	bool MissileHit;
	bool Missilebk;

	Rect ClientRect;

	BoundaryBox* BBox;

	int Shotcount;

	bool Dead;
	bool End;

	bool Reset;
};

#define CutterKirbyBase CutterKirby::getReference()