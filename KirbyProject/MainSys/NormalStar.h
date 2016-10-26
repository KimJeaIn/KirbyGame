#pragma once

#include "../GameDev/GameDev.h"
#include "Item.h"

class NormalStar : public Item, public Object
{
public :
	NormalStar(const Point& pt, const bool& bk);
	~NormalStar();

	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	BYTE ReturnEff();
	Rect GetRect();
	bool GetBack();
	bool ReturnDel();

	void SetPoint(const Point&);
	void SetState(const bool& st, const BYTE& Wa);
	void SetDrain(const bool&, const Point&);
	void SetPlayerPos(const LONG& px);
	void SetDel(const bool& de);

	BoundaryBox* ReturnBBox() const;

private :
	Point StarPos;
	Rect StarRect;

	int JumpAcc;

	DWORD update_dt;
	DWORD update_delay;

	int DelCount;

	LONG MoveAcc;
	LONG Acc;
	LONG MoveEnemie;

	Vector dir;
	Vector origin;
	Vector pos;

	bool Stand;
	bool Back;
	bool Del;
	bool End;
	bool Sound;
	bool Drain;

	Point KirbyPos;

	BYTE Wall;

	BYTE Efficacy;

	BoundaryBox* BBox;
};