#pragma once

#include "../GameDev/GameDev.h"
#include <stdlib.h>
#include <time.h>

class Effect
{
public :
	Effect();
	~Effect();

	void Update(DWORD, const Point& pt);
	void Draw(HDC);
	void Enter();

	void SetPosition(const Rect& rc, const bool& bk);
	void SetTargetPosition(const Vector& pt);

private :
	Rect DrainRect;

	Vector dir;
	Vector origin;
	Vector pos;

	BYTE count;

	DWORD update_dt;
	DWORD update_delay;

	Image Air;

	bool Back;
};