#pragma once

#include "../GameDev/GameDev.h"
#include "KirbyState.h"
#include "BlockManager.h"
#include "EnemiesManager.h"
#include "ItemManager.h"
#include "Boss.h"
#include <list>

class Kirby : public singleton<Kirby>, public Object, public statemachine
{
	friend class singleton<Kirby>;
	friend class Object;
	friend class statemachine;

private :
	Kirby();
	~Kirby();
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

	BYTE ReturnType() const;

	void TypeReset();
	
	bool ReturnStageChange() const;

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
	char KirbyHp;
	BYTE KirbyHitCount;
	BYTE Wallcount;

	LONG MoveAcc;
	int MoveAccCount;

	bool Sound;
	bool BackPosition;
	bool DrainC;
	bool DrainIn;
	BYTE KirbyFat;

	bool StageChange;

	bool MissileHit;
	bool Missilebk;

	Rect ClientRect;

	BoundaryBox* BBox;

	int Shotcount;

	bool Dead;
	bool End;

	bool Reset;
};

#define KirbyBase Kirby::getReference()