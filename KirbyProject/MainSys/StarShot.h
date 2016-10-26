#pragma once

#include "../GameDev/GameDev.h"

class StarShot : public Object
{
public :
	StarShot(const Point& pt, const bool& bk);
	virtual ~StarShot();
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);
	void SetHit(const bool& h);
	bool GetDel() const;

	BoundaryBox* ReturnBBox() const;

	Rect GetStarRect() const;

private :
	DWORD update_dt;
	DWORD update_delay;

	Point StarPos;
	Rect StarRect;
	Point KirbyPos;
	bool Hit;
	bool Del;
	bool Back;
	BoundaryBox* BBox;

	bool StarShotEnd;
};