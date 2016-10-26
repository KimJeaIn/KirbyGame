#pragma once

#include "../GameDev/GameDev.h"
#include "Kirby.h"

class HpState
{
public :
	HpState();
	~HpState();

	void Update(DWORD tick);
	void Draw(HDC hdc);

	void SetHp(const char& hp);

private :
	Rect KirbyHpBar;
	int KirbyHp;
};

class BossHpState
{
public :
	BossHpState();
	~BossHpState();

	void Update(DWORD tick);
	void Draw(HDC hdc);

	void SetHp(const char& hp);

private :
	Rect BossHpBar;
	int BossHp;
};