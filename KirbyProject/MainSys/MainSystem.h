#pragma once

#pragma comment(lib, "../GameDev/GameDev.lib")

#include "../GameDev/GameDev.h"
#include "Stage1-1.h"
#include "MissileManager.h"
#include "State.h"
#include "ItemManager.h"
#include "Stage1-2.h"
#include "Boss.h"
#ifdef _DEBUG
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

class Mainsys : public MainWindow<Mainsys>
{
public :
	Mainsys();
	~Mainsys()
	{
		SafeDelete(Stage1);
	}
	void Input(DWORD);
	void Update(DWORD tick);
	void Draw(DWORD);

protected :
	void Enter();
	void Leave();

private :
	Point KirbyPos;
	Stage1_1* Stage1;
	Stage1_2* Stage2;
	HpState KirbyHpS;
	BossHpState BossHpS;

	BYTE KirbyType;

	bool CutterChange;
	bool ChangeSound;
	bool SoundOne;

	BYTE Stage;

	DWORD Stage1BGM_dt;
	DWORD GameEnd_dt;

	bool Title;
	bool GameOver;
	bool GameOverBGM;
	bool One;
	bool GameEnd;
	bool EndAni;
	bool BossDie;
};