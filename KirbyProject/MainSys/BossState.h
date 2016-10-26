#pragma once

#include "../GameDev/GameDev.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <list>

enum Boss_Size
{
	BossWidth = 144,
	BossHeight = 144,

};

class BossDead : public state
{
public :
	BossDead();
	virtual ~BossDead();

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
	Rect GetRect()
	{
		return Rect(0,0,0,0);
	}
	void SetKirbyPoint(const Point&);
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	BYTE Wall;

	bool HitEnd;

	Point BossPos;
	Point PlayerPos;
	Rect BossRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};

class BossIdle : public state
{
public :
	BossIdle();
	virtual ~BossIdle();

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
	Rect GetRect()
	{
		return Rect(0,0,0,0);
	}
	void SetKirbyPoint(const Point&);
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	LONG TransCount;

	LONG Phase;

	bool Stand;
	BYTE Wall;

	Point KirbyPos;
	Point BossPos;
	Point PlayerPos;
	Rect BossRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};
class BossAttack : public state
{
public :
	BossAttack();
	virtual ~BossAttack();

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
	Rect GetRect()
	{
		return Rect(0,0,0,0);
	}
	void SetKirbyPoint(const Point&);
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	BYTE Wall;

	BYTE AttackCount;

	Point KirbyPos;
	Point BossPos;
	Point PlayerPos;
	Rect BossRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};
class RageBossAttack : public state
{
public :
	RageBossAttack();
	virtual ~RageBossAttack();

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
	Rect GetRect()
	{
		return Rect(0,0,0,0);
	}
	void SetKirbyPoint(const Point&);
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	BYTE Wall;

	BYTE AttackCount;

	Point KirbyPos;
	Point BossPos;
	Point PlayerPos;
	Rect BossRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};
class BossRage : public state
{
public :
	BossRage();
	virtual ~BossRage();

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
	Rect GetRect()
	{
		return Rect(0,0,0,10000);
	}
	void SetKirbyPoint(const Point&);
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	BYTE Wall;

	BYTE Phase;

	BYTE AttackCount;

	Point KirbyPos;
	Point BossPos;
	Point PlayerPos;
	Rect BossRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};
class BossDance : public state
{
public :
	BossDance();
	virtual ~BossDance();

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
	Rect GetRect()
	{
		return Rect(0,0,0,0);
	}
	void SetKirbyPoint(const Point&);
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	BYTE Wall;

	BYTE AttackCount;

	bool Setting;

	Point KirbyPos;
	Point BossPos;
	Point PlayerPos;
	Rect BossRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};
class RageBossDance : public state
{
public :
	RageBossDance();
	virtual ~RageBossDance();

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
	Rect GetRect()
	{
		return Rect(0,0,0,0);
	}
	void SetKirbyPoint(const Point&);
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	BYTE Wall;

	BYTE AttackCount;

	bool Setting;

	Point KirbyPos;
	Point BossPos;
	Point PlayerPos;
	Rect BossRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};
class BossShot : public state
{
public :
	BossShot();
	virtual ~BossShot();

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
	Rect GetRect()
	{
		return Rect(0,0,0,0);
	}
	void SetKirbyPoint(const Point&);
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	BYTE Wall;

	BYTE AttackCount;

	Point KirbyPos;
	Point BossPos;
	Point PlayerPos;
	Rect BossRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};
class RageBossShot : public state
{
public :
	RageBossShot();
	virtual ~RageBossShot();

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
	Rect GetRect()
	{
		return Rect(0,0,0,0);
	}
	void SetKirbyPoint(const Point&);
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	BYTE Wall;

	BYTE AttackCount;

	Point KirbyPos;
	Point BossPos;
	Point PlayerPos;
	Rect BossRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};
