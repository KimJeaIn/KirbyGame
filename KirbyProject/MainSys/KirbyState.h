#pragma once

#include "../GameDev/GameDev.h"
#include "EffectManager.h"
#include "Kirby.h"
#include "MissileManager.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <list>

enum Zone_id
{
	LeftZone = 0,
	RightZone,
	ZoneMax,
};
enum Kirby_Size
{
	KirbyWidth = 60,
	KirbyHeight = 58,

};
enum Kirby_state
{
	StdState = 0,
	LeftWall,
	RightWall,
	TopWall,
};

class KirbyIdle : public state
{
public :
	KirbyIdle();
	virtual ~KirbyIdle();

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
class KirbyFatIdle : public state
{
public :
	KirbyFatIdle();
	virtual ~KirbyFatIdle();

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
	DWORD update_shot;

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
class KirbyMove : public state
{
public :
	KirbyMove();
	virtual ~KirbyMove();

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

	bool MapEnd;
	bool Boss;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	bool BackPosition;
	bool KeyPush;
	bool RightKey;
};
class KirbyFatMove : public state
{
public :
	KirbyFatMove();
	virtual ~KirbyFatMove();

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
	DWORD update_shot;

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
class KirbyRun : public state
{
public :
	KirbyRun();
	virtual ~KirbyRun();

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
class KirbyFatRun : public state
{
public :
	KirbyFatRun();
	virtual ~KirbyFatRun();

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
	DWORD update_shot;

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
class KirbyJump : public state
{
public :
	KirbyJump();
	virtual ~KirbyJump();

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
class KirbyFatJump : public state
{
public :
	KirbyFatJump();
	virtual ~KirbyFatJump();

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
	DWORD update_shot;

	bool Boss;
	bool Stand;
	bool UpBlock;
	BYTE Wall;

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
class KirbyLanding : public state
{
public :
	KirbyLanding();
	virtual ~KirbyLanding();

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
class KirbyFatLanding : public state
{
public :
	KirbyFatLanding();
	virtual ~KirbyFatLanding();

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
	DWORD update_shot;

	bool Boss;
	bool Stand;
	bool UpBlock;
	BYTE Wall;

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
class KirbyFloat : public state
{
public :
	KirbyFloat();
	virtual ~KirbyFloat();

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
class KirbyDrain : public state
{
public :
	KirbyDrain();
	virtual ~KirbyDrain();

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
	void Reset();
	void SetBossStage(const bool&)
	{
	}

private :
	DWORD update_dt;
	DWORD update_delay;

	bool Stand;
	bool UpBlock;
	BYTE Wall;

	bool Drain;
	bool DrainR;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	Rect DrainRect;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
	bool KeyPush;
	bool DrainStart;
	bool test;
	BoundaryBox* DrainBox;
};
class KirbyHit : public state
{
public :
	KirbyHit();
	virtual ~KirbyHit();

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

	bool Hit;

	Point KirbyPos;
	Point PlayerPos;
	Rect KirbyRect;
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;
};
class KirbyFatHit : public state
{
public :
	KirbyFatHit();
	virtual ~KirbyFatHit();

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
	LONG MoveAcc;
	LONG JumpAcc;
	Rect Zone[ZoneMax];
	bool BackPosition;

	bool Hit;
};
class KirbyShot : public state
{
public :
	KirbyShot();
	virtual ~KirbyShot();

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
	bool Shot;

	bool StarShot;

	int Shotcount;
};
class KirbyDead : public state
{
public :
	KirbyDead();
	virtual ~KirbyDead();

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
class KirbyEat : public state
{
public :
	KirbyEat();
	virtual ~KirbyEat();

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

	bool Sound;
};
class KirbyStarIn : public state
{
public :
	KirbyStarIn();
	virtual ~KirbyStarIn();

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
class KirbyDance : public state
{
public :
	KirbyDance();
	virtual ~KirbyDance();

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