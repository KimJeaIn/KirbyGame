#pragma once

#include "../GameDev/GameDev.h"
#include "CutterStar.h"
#include "BlockManager.h"
#include "Kirby.h"
#include "KirbyStar.h"
#include "NormalStar.h"
#include "Tomato.h"
#include "DanceStar.h"
#include <list>

class ItemManager : public singleton<ItemManager>
{
	friend class singleton<ItemManager>;

private :
	ItemManager();
	virtual ~ItemManager();

public :
	void StarPush(const Point& pt, const bool& bk);
	void DanceStarPush(const Point& pt);
	void NormalStarPush(const Point& pt, const bool& bk);
	void KirbyStarPush(const Point& pt);
	void TomatoPush(const Point& pt);
	void Update(DWORD);
	void Draw(HDC);

	void Reset();

	const std::list<Item*>& getList() const;

private :
	std::list<Item*> ItemList;

	int CountTest;
};

#define ItemDepot ItemManager::getReference()