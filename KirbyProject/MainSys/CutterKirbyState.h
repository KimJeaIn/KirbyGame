#pragma once

#include "../GameDev/GameDev.h"
#include "EffectManager.h"
#include "CutterKirby.h"
#include "MissileManager.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <list>

class CutterKirbyIdle : public state
{
public :
	CutterKirbyIdle();
	virtual ~CutterKirbyIdle();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	LONG MoveAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
};
class CutterKirbyMove : public state
{
public :
	CutterKirbyMove();
	virtual ~CutterKirbyMove();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&);

private :
	DWORD update_dt;
	DWORD update_delay;
	DWORD update_dt2;
	DWORD update_delay2;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	LONG MoveAcc;
	Rect Zone[ZoneMax];

	bool Boss;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	bool BackPosition;
	bool KeyPush;
	bool RightKey;
};
class CutterKirbyRun : public state
{
public :
	CutterKirbyRun();
	virtual ~CutterKirbyRun();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&);

private :
	DWORD update_dt;
	DWORD update_delay;
	DWORD update_dt2;
	DWORD update_delay2;

	bool Boss;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	bool Break;
	LONG MoveAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
	bool KeyPush;

	bool Run;
};
class CutterKirbyJump : public state
{
public :
	CutterKirbyJump();
	virtual ~CutterKirbyJump();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&);

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	bool Boss;

	bool Jump;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	bool Rolling;
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
	bool JumpEnd;
	bool KeyPush;
};
class CutterKirbyLanding : public state
{
public :
	CutterKirbyLanding();
	virtual ~CutterKirbyLanding();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&);

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	bool Boss;

	bool Land;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
	bool Landing;
	bool KeyPush;
};
class CutterKirbyFloat : public state
{
public :
	CutterKirbyFloat();
	virtual ~CutterKirbyFloat();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&);

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Boss;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
	bool Landing;
	bool Float;
	bool KirbyUp;
	bool KeyPush;

	bool FloatSound;
	bool FloatAirSound;
};
class CutterKirbyHit : public state
{
public :
	CutterKirbyHit();
	virtual ~CutterKirbyHit();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&);

private :
	DWORD update_dt;
	DWORD update_delay;
	DWORD update_dt2;
	DWORD update_delay2;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	bool Boss;

	bool Hit;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
};
class CutterKirbyShot : public state
{
public :
	CutterKirbyShot();
	virtual ~CutterKirbyShot();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;
	DWORD update_dt2;
	DWORD update_delay2;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;

	BYTE Shotcount;

	bool Sound;
};
class CutterKirbyDead : public state
{
public :
	CutterKirbyDead();
	virtual ~CutterKirbyDead();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&)
	{
	}

	void Reset();

private :
	DWORD update_dt;
	DWORD update_delay;
	DWORD update_dt2;
	DWORD update_delay2;
	DWORD update_dead;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;

	bool HitEnd;
	bool DieBGM;

	bool Dead;
	bool Start;
};
class CutterKirbyStarIn : public state
{
public :
	CutterKirbyStarIn();
	virtual ~CutterKirbyStarIn();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;
	DWORD update_dt2;
	DWORD update_delay2;

	bool Stand;
	bool Start;
	bool UpBlock;
	BYTE Wall;

	bool Sound;

	BYTE Phase;

	LONG Phase1_count;
	LONG Phase2_count;
	LONG Phase3_count;
	LONG TurnCount;
	bool Turn;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
};
class CutterKirbyDance : public state
{
public :
	CutterKirbyDance();
	virtual ~CutterKirbyDance();

	virtual void AniEnter(Animation* fr, Animation* bk);
	virtual void Enter();
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);
	virtual void Leave();
	void GetState(const BYTE& wl);
	void GetStand(const bool&, const bool&);
	void SetPosition(const Point& kpt, const Point& ppt, const bool& back);
	void SetCharPoint(const Point& kpt);
	Rect GetRect();
	void SetKirbyPoint(const Point&)
	{
	}
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;
	DWORD update_dt2;
	DWORD update_delay2;

	bool Stand;
	bool Start;
	bool UpBlock;
	BYTE Wall;

	bool Sound;

	BYTE Phase;

	LONG Phase1_count;
	LONG Phase2_count;
	LONG Phase3_count;
	LONG Phase4_count;
	LONG Phase5_count;
	LONG Phase6_count;
	LONG Phase7_count;
	LONG Phase8_count;

	LONG TurnCount;
	bool Turn1;

	int Turn1Count;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
};