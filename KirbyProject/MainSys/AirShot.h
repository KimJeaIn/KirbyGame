#pragma once

#include "../GameDev/GameDev.h"

class AirShot : public Object
{
public :
	AirShot(const Point& pt, const bool& bk);
	virtual ~AirShot();
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);
	void SetHit(const bool& h);
	bool GetDel() const;

	BoundaryBox* ReturnBBox() const;

	Rect GetAirRect() const;

	void SetPlayerPos(const LONG& px);

private :
	DWORD update_dt;
	DWORD update_delay;

	LONG MoveEnemie;

	Point AirPos;
	Rect AirRect;
	Point KirbyPos;
	bool Hit;
	bool Del;
	bool Back;
	BoundaryBox* BBox;

	bool AirShotEnd;
};