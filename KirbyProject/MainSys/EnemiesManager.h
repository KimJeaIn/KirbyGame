#pragma once

#include <list>
#include "../GameDev/GameDev.h"
#include "Enemies.h"

class EnemiesManager : public singleton<EnemiesManager>
{
	friend class singleton<EnemiesManager>;

private :
	EnemiesManager();
	~EnemiesManager();
public :
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void SetPlayerPos(const LONG& px);
	void SetKirbyPos(const Point& pt);
	void SetDrainRect(const Rect& rc);

	bool ReturnDrain();

	void Push(Enemies* pObj);

	void Clear();

	const std::list<Enemies*>& getList() const;

private :
	std::list<Enemies*> depot;

};

#define EnemiesDepot EnemiesManager::getReference()