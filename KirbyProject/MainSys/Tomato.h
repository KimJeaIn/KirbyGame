#pragma once

#include "../GameDev/GameDev.h"
#include "Item.h"

class Tomato : public Item, public Object
{
public :
	Tomato(const Point& pt);
	~Tomato();

	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	BYTE ReturnEff();

	Rect GetRect();
	bool GetBack();

	void SetPoint(const Point&);

	bool ReturnDel();

	void SetDrain(const bool&, const Point&);
	void SetState(const bool& st, const BYTE& Wa);
	void SetDel(const bool& de);

	BoundaryBox* ReturnBBox() const;

	void SetPlayerPos(const LONG&);

private :
	Point TomatoPos;
	Rect TomatoRect;

	bool Del;

	LONG MoveEnemie;

	DWORD update_dt;
	DWORD update_delay;

	LONG MoveAcc;
	LONG Acc;

	BoundaryBox* BBox;
};