#include "ItemManager.h"

ItemManager::ItemManager()
: CountTest(0)
{
}
ItemManager::~ItemManager()
{
	std::list<Item*>::iterator it;
	for (it = ItemList.begin(); it != ItemList.end(); )
	{
		delete *it;
		it = ItemList.erase(it);
	}
}

void ItemManager::StarPush(const Point& pt, const bool& bk)
{
	Item* tmp = new CutterStar(pt, bk);

	ItemList.push_back(tmp);
}
void ItemManager::DanceStarPush(const Point& pt)
{
	Item* tmp = new DanceStar(pt);

	ItemList.push_back(tmp);
}
void ItemManager::NormalStarPush(const Point& pt, const bool& bk)
{
	Item* tmp = new NormalStar(pt, bk);

	ItemList.push_back(tmp);
}
void ItemManager::KirbyStarPush(const Point& pt)
{
	Item* tmp = new KirbyStar(pt);

	ItemList.push_back(tmp);
}
void ItemManager::TomatoPush(const Point& pt)
{
	Item* tmp = new Tomato(pt);

	ItemList.push_back(tmp);
}
void ItemManager::Update(DWORD tick)
{
	std::list<Item*>::iterator et;
	for (et = ItemList.begin(); et != ItemList.end();)
	{
		(*et)->SetPlayerPos(KirbyBase.RetrunPlayerPos().x);
		(*et)->Update(tick);
		Rect tmp;
		if(IntersectRect(&tmp, &KirbyBase.ReturnDrainRect(), &(*et)->GetRect()))
		{
			(*et)->SetDrain(true, KirbyBase.RetrunKirbyPos());
		}
		if((*et)->ReturnDel())
		{
			delete *et;
			et = ItemList.erase(et);
		}
		else
			et++;
	}

	std::list<Block*> bList = BlockDepot.getList();
	std::list<Block*>::iterator it;

	int IsCollideCount = 0;

	for (it = bList.begin(); it != bList.end(); it++)
	{
		std::list<Item*>::iterator jt;
		for (jt = ItemList.begin(); jt != ItemList.end(); jt++)
		{
			if((*jt)->ReturnBBox())
			{
				BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide((*it)->getBBox(), (*jt)->GetBack());
				if(tmp == 0 || tmp == 10 || tmp == 20)
				{
					Rect tmprc = (*it)->GetBBoxRect();

					(*jt)->SetState(true, 0);
					IsCollideCount++;
				}
				if(tmp == 1)
				{
					(*jt)->SetState(false, 1);
					IsCollideCount++;
				}
				else if(tmp == 2)
				{
					(*jt)->SetState(false, 2);
					IsCollideCount++;
				}
			}

			if(IsCollideCount == 0)
			{
				(*jt)->SetState(false, 0);
			}
		}
	}
}
void ItemManager::Draw(HDC hdc)
{
	std::list<Item*>::iterator it;
	for (it = ItemList.begin(); it != ItemList.end(); it++)
	{
		Rect tmp;
		if (::IntersectRect(&tmp, &GameGlobal.rcClient, &((*it)->GetRect())))
		{
			(*it)->Draw(hdc);
			CountTest++;
		}
	}
	std::wostringstream oss;
	oss << _T("StarCount : ") << CountTest << _T("\n");

	::OutputDebugString(oss.str().c_str());
}
const std::list<Item*>& ItemManager::getList() const
{
	return ItemList;
}
void ItemManager::Reset()
{
	std::list<Item*>::iterator it;
	for (it = ItemList.begin(); it != ItemList.end(); )
	{
		delete *it;
		it = ItemList.erase(it);
	}
}