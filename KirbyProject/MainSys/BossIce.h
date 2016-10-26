#pragma once

#include "../GameDev/GameDev.h"

class IceShot : public Object
{
public :
	IceShot(const Point& pt, const bool& bk);
	virtual ~IceShot();
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);
	void SetHit(const bool& h);
	bool GetDel() const;

	bool GetBack() const;

	BoundaryBox* ReturnBBox() const;

	Rect GetIceRect() const;

private :
	DWORD update_dt;
	DWORD update_delay;

	int Size;

	int Setting;

	Point IcePos;
	Rect IceRect;
	Point KirbyPos;
	bool Hit;
	bool Del;
	bool Back;
	BoundaryBox* BBox;

	bool IceShotEnd;
};
class RageIceShot : public Object
{
public :
	RageIceShot(const Point& pt, const bool& bk);
	virtual ~RageIceShot();
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);
	void SetHit(const bool& h);
	bool GetDel() const;

	bool GetBack() const;

	BoundaryBox* ReturnBBox() const;

	Rect GetIceRect() const;

private :
	DWORD update_dt;
	DWORD update_delay;

	int Size;

	int Setting;

	Point IcePos;
	Rect IceRect;
	Point KirbyPos;
	bool Hit;
	bool Del;
	bool Back;
	BoundaryBox* BBox;

	bool IceShotEnd;
};