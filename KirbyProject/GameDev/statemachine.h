﻿#pragma once

#include "../GameDev/GameDev.h"
#include "Animation.h"
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <map>

class statemachine;

class state
{
public :
   state();
   virtual ~state();

   virtual void AniEnter(Animation* fr, Animation* bk) = 0;
   virtual void Enter() = 0;
   virtual void Input(DWORD) = 0;
   virtual void Update(DWORD) = 0;
   virtual void Draw(HDC) = 0;
   virtual void Leave() = 0;
   virtual void GetState(const BYTE&) = 0;
   virtual void GetStand(const bool&, const bool&) = 0;

   virtual void SetPosition(const Point& , const Point& , const bool& ) = 0;
   virtual void SetCharPoint(const Point&) = 0;
   virtual Rect GetRect() = 0;
   virtual void SetKirbyPoint(const Point&) = 0;
   virtual void SetBossStage(const bool&) = 0;

   void SetMachine(statemachine* _pMachine);

private :

protected :
	statemachine* pMachine;
};

class statemachine
{
public :
	typedef std::wstring key_type;
	typedef std::map<key_type, state*> StateDepotType;

	statemachine();
	virtual ~statemachine();

	state* transition(const key_type& key);

	bool AddEntry(const key_type& key, state* s);
	bool RemoveEntry(const key_type& key);

	state* current();

protected :
	state* _current;

	StateDepotType StateDepot;
};

