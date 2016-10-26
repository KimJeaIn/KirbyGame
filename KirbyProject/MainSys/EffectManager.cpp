#include "EffectManager.h"

EffectManager::EffectManager()
{
}
EffectManager::~EffectManager()
{
	std::list<Effect*>::iterator it;
	for (it = depot.begin(); it != depot.end(); )
	{
		delete *it;
		it = depot.erase(it);
	}
}
void EffectManager::Update(DWORD tick, const Point& pt)
{
	std::list<Effect*>::iterator it;
	for (it = depot.begin(); it != depot.end(); it++)
	{
		(*it)->Update(tick, pt);
	}
}
void EffectManager::Draw(HDC hdc)
{
	std::list<Effect*>::iterator it;
	for(it = depot.begin(); it != depot.end(); it++)
	{
		(*it)->Draw(hdc);
	}
}

void EffectManager::Push(Effect* pObj)
{
	depot.push_back(pObj);
}
const std::list<Effect*>& EffectManager::getList() const
{
	return depot;
}
void EffectManager::SetPosition(const Rect& rc, const bool& bk)
{
	std::list<Effect*>::iterator it;
	for(it = depot.begin(); it != depot.end(); it++)
	{
		(*it)->SetPosition(rc, bk);
	}
}
void EffectManager::Rerease()
{
	std::list<Effect*>::iterator it;
	for (it = depot.begin(); it != depot.end(); )
	{
		delete *it;
		it = depot.erase(it);
	}
}