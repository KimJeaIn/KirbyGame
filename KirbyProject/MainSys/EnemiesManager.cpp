#include "EnemiesManager.h"

EnemiesManager::EnemiesManager()
{
}
EnemiesManager::~EnemiesManager()
{
	std::list<Enemies*>::iterator it;
	for (it = depot.begin(); it != depot.end(); )
	{
		delete *it;
		it = depot.erase(it);
	}
}
void EnemiesManager::Input(DWORD tick)
{
	std::list<Enemies*>::iterator it;
	for (it = depot.begin(); it != depot.end(); it++)
	{
		(*it)->Input(tick);
	}
}
void EnemiesManager::Update(DWORD tick)
{
	std::list<Enemies*>::iterator it;
	for (it = depot.begin(); it != depot.end();)
	{
		(*it)->Update(tick);
		if((*it)->DeadCon().right > 0)
		{
			SafeDelete(*it);
			it = depot.erase(it);
		}
		else
			it++;
	}
}
void EnemiesManager::Draw(HDC hdc)
{
	int count = 0;

	std::list<Enemies*>::iterator it;
	for(it = depot.begin(); it != depot.end(); it++)
	{
		Rect tmp;
		if (::IntersectRect(&tmp, &GameGlobal.rcClient, &((*it)->GetRect())))
		{
			(*it)->Draw(hdc);
		}
		count++;
	}

	std::wostringstream oss;
	oss << _T("Enemies Count : ") << count << _T("\n");

	::OutputDebugString(oss.str().c_str());
}
void EnemiesManager::Push(Enemies* pObj)
{
	depot.push_back(pObj);
}
const std::list<Enemies*>& EnemiesManager::getList() const
{
	return depot;
}
void EnemiesManager::SetPlayerPos(const LONG& px)
{
	std::list<Enemies*>::iterator it;
	for (it = depot.begin(); it != depot.end(); it++)
	{
		(*it)->SetPlayerPos(px);
	}
}
void EnemiesManager::SetKirbyPos(const Point& pt)
{
	std::list<Enemies*>::iterator it;
	for (it = depot.begin(); it != depot.end(); it++)
	{
		(*it)->SetKirbyPos(pt);
	}
}
void EnemiesManager::SetDrainRect(const Rect& rc)
{
	std::list<Enemies*>::iterator it;
	for (it = depot.begin(); it != depot.end(); it++)
	{
		(*it)->SetDrainRect(rc);
	}
}
bool EnemiesManager::ReturnDrain()
{
	std::list<Enemies*>::iterator it;
	for (it = depot.begin(); it != depot.end(); it++)
	{
		if((*it)->DrainReturn())
			return true;
	}

	return false;
}
void EnemiesManager::Clear()
{
	std::list<Enemies*>::iterator it;
	for (it = depot.begin(); it != depot.end(); )
	{
		delete *it;
		it = depot.erase(it);
	}
}