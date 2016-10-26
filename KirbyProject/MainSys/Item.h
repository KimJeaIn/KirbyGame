#pragma once

#include "../GameDev/GameDev.h"

class Item
{
public :
	Item()
	{
	}
	virtual ~Item()
	{
	}

	virtual void Input(DWORD) = 0;
	virtual void Update(DWORD) = 0;
	virtual void Draw(HDC) = 0;

	virtual BYTE ReturnEff() = 0;

	virtual Rect GetRect() = 0;
	virtual bool GetBack() = 0;

	virtual void SetPoint(const Point&) = 0;

	virtual bool ReturnDel() = 0;

	virtual void SetDrain(const bool&, const Point&) = 0;
	virtual void SetState(const bool& st, const BYTE& Wa) = 0;
	virtual void SetDel(const bool& de) = 0;

	virtual BoundaryBox* ReturnBBox() const = 0;

	virtual void SetPlayerPos(const LONG&) = 0;

private :

};