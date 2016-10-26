#pragma once

#include "../GameDev/GameDev.h"
#include "EnemiesState.h"
#include "BlockManager.h"
#include <list>

class Enemies : public Object, public statemachine
{
public :

	Enemies(const Point&);
	~Enemies();

	void Load(const BYTE& type);
	void Input(DWORD);
	void Draw(HDC hdc);
	void Update(DWORD);
	void Setposition(const Point& ppt, const Point& kpt, const bool& back);

	Vector GetPosition() const;

	Point RetrunEnemiePos() const;

	Rect GetRect() const;
	Rect GetBBoxRect() const;

	BYTE ReturnType() const;

	bool DrainReturn() const;

	void SetPlayerPos(const LONG& px);
	void SetKirbyPos(const Point& kt);
	void SetDrainRect(const Rect& rc);

	void DeadSet(const BYTE& st);

	void GetStarHit(const bool& hit, const bool& bk);
	void GetAirHit(const bool& hit, const bool& bk);

	BoundaryBox* getBBox();

	Rect DeadCon();

private :
	void init(const BYTE& type);

private :
	EnemieMove move;
	EnemieHit hit;
	EnemieDead dead;
	EnemieDrainHit drain;
	EnemieEnd end;
	EnemieIdle idle;
	EnemieAttack attack;
	EnemieFly fly;

private :
	Point EnemiePos;
	Point PlayerPos;
	Point KirbyPos;
	Rect KirbyRect;

	DWORD update_dt;
	DWORD update_dt2;
	Rect EnemieRect;

	char EnemieHp;
	BYTE EnemieHitCount;

	BYTE EnemieState;
	BYTE Wallcount;
	DWORD update_dt_hit;

	LONG MoveAcc;
	int MoveAccCount;

	LONG MoveEnemie;

	bool BackPosition;
	bool DrainEnemie;

	bool StarHit;
	bool AirHit;

	BYTE EnemieType;

	BYTE DeadType;

	BoundaryBox* BBox;

	Rect DrainRect;
};