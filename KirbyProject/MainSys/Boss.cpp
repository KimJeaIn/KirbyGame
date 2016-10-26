#include "Boss.h"

Boss::Boss()
:BossPos(Point(700,400)), update_dt(0), PlayerPos(375,0)
, BackPosition(false), MoveAcc(0), MoveAccCount(0), StarHit(false)
, Wallcount(0), BossHp(56), update_dt_hit(0), update_dt2(0)
, MoveBoss(0), BBox(NULL), CutterHit(false), RageSet(false)
, Test(true), BossHitCount(0), TickUpdate(false)
{
	SquareBox* pBox = new SquareBox;

	BossRect.left = BossPos.x- BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossRect.left + BossWidth;
	BossRect.bottom = BossRect.top + BossHeight;

	pBox->SetRect(BossRect);

	BBox = pBox;
}
Boss::~Boss()
{
	if (BBox)
		delete BBox;
}
void Boss::Load()
{
	init();
}
void Boss::Input(DWORD tick)
{
	if (_current)
		_current->Input(tick);	
}
void Boss::Draw(HDC hdc)
{
	Rect tmprect;

	if(IntersectRect(&tmprect, &BossRect, &GameGlobal.rcClient))
	{
		if(BossHitCount == 0 || BossHitCount%2 == 1)
		{
			if (_current)
				_current->Draw(hdc);
			if (BBox)
				BBox->Draw(hdc);
		}
	}
}
void Boss::Update(DWORD tick)
{
	if(Test)
	{
		transition(_T("Idle"));
		Test = false;
	}

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossRect.left + BossWidth;
	BossRect.bottom = BossRect.top + BossHeight;

	if (_current)
	{
		if(_current->GetRect().bottom == 10000)
		{
			TickUpdate = true;
		}
	}

	if(TickUpdate)
	{
		tick += 15;
	}

	Point tmp;
	tmp = BossPos;
	tmp.x = tmp.x - BossWidth/2;
	tmp.y = tmp.y - BossHeight/2;

	int CollideCount = 0;

	BYTE Stand = 0;

	Rect tmprect;

	std::list<Block*> bList = BlockDepot.getList();
	std::list<Block*>::iterator it;
	for (it = bList.begin(); it != bList.end(); it++)
	{
		Rect tmp;

		if(IntersectRect(&tmp, &BossRect, &(*it)->GetBBoxRect()))
		{
			BYTE tmpstate = BBox->BoxIsCollide((*it)->getBBox(), !BackPosition);

			CollideCount++;
			if(tmpstate == 0)
			{
				Rect tmp = (*it)->GetBBoxRect();

				BossPos.y = tmp.top - (BossHeight/2) + 5;

				if(_current)
				{
					_current->GetStand(true, false);
					_current->GetState(0);
					_current->SetCharPoint(BossPos);
				}

				Stand = 1;
				BossState = tmpstate;
			}
			else if(tmpstate == 10)
			{
				Rect tmp = (*it)->GetBBoxRect();

				BossPos.y = tmp.top - (BossHeight/2) + 5;

				if(_current)
				{
					_current->GetStand(true, false);
					_current->GetState(2);
					_current->SetCharPoint(BossPos);
				}

				Stand = 1;
				BossState = tmpstate;
			}
			else if(tmpstate == 20)
			{
				Rect tmp = (*it)->GetBBoxRect();

				BossPos.y = tmp.top - (BossHeight/2) + 5;

				if(_current)
				{
					_current->GetStand(true, false);
					_current->GetState(1);
					_current->SetCharPoint(BossPos);
				}

				Stand = 1;
				BossState = tmpstate;
			}
			if(tmpstate == 1)
			{
				if(_current)
				{
					_current->GetState(1);
				}
				BossState = tmpstate;
			}
			else if(tmpstate == 2)
			{
				if(_current)
				{
					_current->GetState(2);
				}
				BossState = tmpstate;
			}
			else if(tmpstate == 3)
			{
				if(_current)
				{
					_current->GetState(3);
				}
				BossState = tmpstate;
			}

			if(CollideCount >= 3)
			{
				break;
			}
		}
	}

	if(CollideCount == 0)
	{
		if (_current)
		{
			_current->GetStand(false, false);
			_current->GetState(0);
		}
		BossState = 4;
	}

	if(BossHitCount != 0)
	{
		if(update_dt_hit > 100)
		{
			BossHitCount += 1;

			update_dt_hit %= 100;
		}
		update_dt_hit += tick;
	}
	if(BossHitCount > 10)
		BossHitCount = 0;

	Rect Tmp;
	if(StarHit)
	{
		SndDepot["HitEnd"]->Play();
		BossHp -= 10;

		BossHitCount++;

		StarHit = false;
	}
	if(CutterHit)
	{
		SndDepot["HitEnd"]->Play();
		BossHp -= 3;

		BossHitCount++;

		CutterHit = false;
	}
	if(BossHp < 30 && !RageSet)
	{
		transition(_T("Rage"));
		RageSet = true;
	}
	if(BossHp <= 0)
	{
		Rect rc(1000,1000,1000,1000);

		if (BBox)
			dynamic_cast<SquareBox*>(BBox)->SetRect(rc);

		transition(_T("Dead"));
	}
	if (_current)
	{
		_current->SetKirbyPoint(KirbyBase.RetrunKirbyPos());
	}

	if (_current)
		_current->Update(tick);

	if (BBox && BossHp > 0)
		dynamic_cast<SquareBox*>(BBox)->SetRect(BossRect);

	if(_current == NULL)
	{
		std::wostringstream oss;
		oss << _T("Current Error!!!!!!!!!!!!!!!!!!!")<< _T("\n");

		::OutputDebugString(oss.str().c_str());
	}
	if(BossHp < 0)
		BossHp = 0;
}

Point Boss::RetrunBossPos() const
{
	return PlayerPos;
}
void Boss::Setposition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;
	BossPos = kpt;
	BackPosition = back;

	StateDepotType::iterator it;
	for (it = StateDepot.begin();
		it != StateDepot.end(); it++)
	{
		it->second->SetPosition(PlayerPos, BossPos, BackPosition);
	}
}
void Boss::init()
{
	static BossIdle idle;
	static BossAttack attack;
	static BossDance dance;
	static BossShot shot;
	static BossRage rage;
	static BossDead dead;

	static RageBossAttack Rattack;
	static RageBossDance Rdance;
	static RageBossShot Rshot;

	idle.SetPosition(PlayerPos, BossPos, BackPosition);
	attack.SetPosition(PlayerPos, BossPos, BackPosition);
	dance.SetPosition(PlayerPos, BossPos, BackPosition);
	shot.SetPosition(PlayerPos, BossPos, BackPosition);
	rage.SetPosition(PlayerPos, BossPos, BackPosition);
	dead.SetPosition(PlayerPos, BossPos, BackPosition);
	Rattack.SetPosition(PlayerPos, BossPos, BackPosition);
	Rdance.SetPosition(PlayerPos, BossPos, BackPosition);
	Rshot.SetPosition(PlayerPos, BossPos, BackPosition);

	AddEntry(_T("Idle"), &idle);
	AddEntry(_T("Attack"), &attack);
	AddEntry(_T("Dance"), &dance);
	AddEntry(_T("Rage"), &rage);
	AddEntry(_T("Shot"), &shot);
	AddEntry(_T("Dead"), &dead);
	AddEntry(_T("RAttack"), &Rattack);
	AddEntry(_T("RDance"), &Rdance);
	AddEntry(_T("RShot"), &Rshot);

	transition(_T("Idle"));
}
Vector Boss::GetPosition() const
{
	Vector tmp(BossPos);
	return tmp;
}
Rect Boss::GetRect() const
{
	return BossRect;
}
void Boss::SetPlayerPos(const LONG& px)
{
}
Rect Boss::GetBBoxRect() const
{
	return dynamic_cast<SquareBox*>(BBox)->getBox();
}
void Boss::GetStarHit(const bool& hit)
{
	StarHit = hit;
}
BoundaryBox* Boss::getBBox()
{
	return BBox;
}
Rect Boss::DeadCon()
{
	if(_current)
	{
		return _current->GetRect();
	}

	return Rect(0,0,0,0);
}
void Boss::DeadSet(const BYTE& st)
{
	DeadType = st;
}
void Boss::SetCutterHit(const bool& hit)
{
	CutterHit = hit;
}
char Boss::ReturnHP() const
{
	return BossHp;
}
void Boss::Reset()
{
	BossHp = 56;

	RageSet = false;
}