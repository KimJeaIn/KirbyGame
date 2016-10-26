#pragma once

#include "../GameDev/GameDev.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <fstream>
#include <list>

enum Enemies_Size
{
	EnemieWidth = 60,
	EnemieHeight = 58,

};
enum Enemie_Type_id
{
	Waddle_Dee = 0,
};

class EnemieMove : public state
{
public :
	EnemieMove();
	virtual ~EnemieMove();

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
	DWORD update_dt2;
	DWORD update_delay2;

	Point EnemiePos;
	Point PlayerPos;
	Rect EnemieRect;
	LONG MoveAcc;

	LONG MoveInput;

	bool Stand;
	BYTE Wall;

	bool BackPosition;
	bool KeyPush;
	bool RightKey;

	Animation* MoveAni;
	Animation* MoveAniBack;
};

class EnemieHit : public state
{
public :
	EnemieHit();
	virtual ~EnemieHit();

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
	DWORD update_dt2;
	DWORD update_delay2;

	bool Stand;
	BYTE Wall;

	Point EnemiePos;
	Point PlayerPos;
	Rect EnemieRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;

	Animation* HitAni;
	Animation* HitAniBack;
};

class EnemieDrainHit : public state
{
public :
	EnemieDrainHit();
	virtual ~EnemieDrainHit();

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
	DWORD update_dt2;
	DWORD update_delay2;

	bool Stand;
	BYTE Wall;

	Vector dir;
	Vector origin;
	Vector pos;

	LONG Acc;

	Point KirbyPos;
	Point EnemiePos;
	Point PlayerPos;
	Rect EnemieRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;

	Animation* HitAni;
	Animation* HitAniBack;
};

class EnemieDead : public state
{
public :
	EnemieDead();
	virtual ~EnemieDead();

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

	Point EnemiePos;
	Point PlayerPos;
	Rect EnemieRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;

	Animation* DeadAni;
	Animation* DeadAniBack;
};
class EnemieEnd : public state
{
public :
	EnemieEnd();
	virtual ~EnemieEnd();

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
		return Rect(100,100,100,4000);
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

	Point EnemiePos;
	Point PlayerPos;
	Rect EnemieRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;
};
class EnemieIdle : public state
{
public :
	EnemieIdle();
	virtual ~EnemieIdle();

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

	Point KirbyPos;
	Point EnemiePos;
	Point PlayerPos;
	Rect EnemieRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;

	Animation* IdleAni;
	Animation* IdleAniBack;
};
class EnemieAttack : public state
{
public :
	EnemieAttack();
	virtual ~EnemieAttack();

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
	Point EnemiePos;
	Point PlayerPos;
	Rect EnemieRect;
	LONG MoveAcc;
	LONG JumpAcc;
	bool BackPosition;

	Animation* AttackAni;
	Animation* AttackAniBack;
};

class EnemieFly : public state
{
public :
	EnemieFly();
	virtual ~EnemieFly();

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
	DWORD update_dt2;
	DWORD update_delay2;

	Point EnemiePos;
	Point PlayerPos;
	Rect EnemieRect;
	LONG MoveAcc;

	LONG MoveInput;

	LONG FlyInput;

	bool FlySet;

	bool Stand;
	BYTE Wall;

	bool BackPosition;
	bool KeyPush;
	bool RightKey;

	Animation* FlyAni;
	Animation* FlyAniBack;
};