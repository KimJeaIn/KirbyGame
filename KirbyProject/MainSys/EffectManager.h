#pragma once

#include "../GameDev/GameDev.h"
#include <list>
#include "Effect.h"

class EffectManager : public singleton<EffectManager>
{
	friend class singleton<EffectManager>;

private :
	EffectManager();
	~EffectManager();
public :
	void Update(DWORD, const Point& pt);
	void Draw(HDC);
	void SetPosition(const Rect& rc, const bool& bk);

	void Push(Effect* pObj);

	void Rerease();

	const std::list<Effect*>& getList() const;

private :
	std::list<Effect*> depot;

};

#define EffectDepot EffectManager::getReference()