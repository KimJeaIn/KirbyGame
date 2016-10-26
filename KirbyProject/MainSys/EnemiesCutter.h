#pragma once

#include "../GameDev/GameDev.h"

class EnemiesCutter : public Object
{
public :
	EnemiesCutter(const Point& pt, const bool& bk);
	virtual ~EnemiesCutter();
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);
	void SetHit(const bool& h);
	bool GetDel() const;
	
	bool GetBack() const;

	BoundaryBox* ReturnBBox() const;

	Rect GetCutterRect() const;

	LONG GetTurn() const;

	void SetPlayerPos(const LONG& px);

private :
	DWORD update_dt;
	DWORD update_delay;

	Point CutterPos;
	Rect CutterRect;
	Point KirbyPos;
	bool Hit;
	bool Del;
	bool Back;

	LONG Turn;

	LONG MoveEnemie;

	bool Return;

	bool Sound;
	
	BoundaryBox* BBox;

	bool CutterShotEnd;
};