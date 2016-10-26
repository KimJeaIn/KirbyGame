#include "CutterKirby.h"

CutterKirby::CutterKirby()
:KirbyPos(200, 0), PlayerPos(375, 0), update_dt(0),
BackPosition(false), MoveAcc(0), MoveAccCount(0)
, KirbyState(4), Wallcount(0), KirbyHp(2), KirbyHitCount(0)
,update_dt_hit(0), DrainC(false), KirbyRerease(false), update_drain(0)
, Dead(false), End(false), Reset(false), DrainIn(false)
,MissileHit(false), BBox(NULL)
{
	SquareBox* pBox = new SquareBox;

	KirbyRect.left = KirbyPos.x- KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyRect.left + KirbyWidth;
	KirbyRect.bottom = KirbyRect.top + KirbyHeight;

	pBox->SetRect(KirbyRect);

	BBox = pBox;
}
CutterKirby::~CutterKirby()
{
	if (BBox)
		delete BBox;
}
void CutterKirby::Load(const Rect& rc)
{
	init();
	transition(_T("Landing"));
	ClientRect = rc;
}
void CutterKirby::Input(DWORD tick)
{
	if (_current)
		_current->Input(tick);	
}
void CutterKirby::Draw(HDC hdc)
{
	DWORD timeF = ::GetTickCount();

	if(KirbyHitCount == 0 || KirbyHitCount%2 == 1)
	{
		if (_current)
			_current->Draw(hdc);
	}

	if (BBox)
		BBox->Draw(hdc);

	DWORD timeE = ::GetTickCount() - timeF;

	std::wostringstream oss;
	oss << _T("KirbyDrawTime : ") << timeE << _T("\n");

	::OutputDebugString(oss.str().c_str());
}
void CutterKirby::Update(DWORD tick)
{
	if(!Reset)
	{
		DWORD timeF = ::GetTickCount();

		KirbyRect.left = KirbyPos.x- KirbyWidth/2;
		KirbyRect.top = KirbyPos.y - KirbyHeight/2;
		KirbyRect.right = KirbyRect.left + KirbyWidth;
		KirbyRect.bottom = KirbyRect.top + KirbyHeight;

		Point tmp;
		tmp = KirbyPos;
		tmp.x = tmp.x - KirbyWidth/2;
		tmp.y = tmp.y - KirbyHeight/2;

		int CollideCount = 0;

		BYTE Stand = 0;

		if(Dead)
			KirbyHitCount = 0;

		Rect recttmp;
		if(KirbyRect.top > GameGlobal.rcClient.bottom)
			KirbyHp = 0;

		if(KirbyHp > 0)
		{
			std::list<Block*> bList = BlockDepot.getList();
			std::list<Block*>::iterator it;
			for (it = bList.begin(); it != bList.end(); it++)
			{
				Rect tmp;
				if(IntersectRect(&tmp, &KirbyRect, &(*it)->GetBBoxRect()))
				{
					BYTE tmpstate = BBox->BoxIsCollide((*it)->getBBox(), BackPosition);

					CollideCount++;
					if(tmpstate == 0 || tmpstate == 10 || tmpstate == 20)
					{
						Rect tmp = (*it)->GetBBoxRect();

						KirbyPos.y = tmp.top - (KirbyHeight/2) + 5;

						if(_current)
						{
							_current->GetStand(true, false);
							_current->GetState(0);
							_current->SetCharPoint(KirbyPos);
						}

						Stand = 1;
						KirbyState = tmpstate;
					}
					if(tmpstate == 1)
					{
						if(_current)
						{
							_current->GetState(1);
						}
						KirbyState = tmpstate;
					}
					else if(tmpstate == 2)
					{
						if(_current)
						{
							_current->GetState(2);
						}
						KirbyState = tmpstate;
					}
					else if(tmpstate == 3)
					{
						if(_current)
						{
							_current->GetStand(false, true);
						}
						KirbyState = tmpstate;
					}

					if(CollideCount >= 3)
					{
						break;
					}
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
			KirbyState = 4;
		}
		if(KirbyHitCount != 0)
		{
			if(update_dt_hit > 100)
			{
				KirbyHitCount += 1;

				update_dt_hit %= 100;
			}
			update_dt_hit += tick;
		}
		if(KirbyHitCount >= 20)
			KirbyHitCount = 0;

		if(_current)
		{
			if(_current->GetRect().bottom == 1900)
				Dead = true;

			if(_current->GetRect().bottom == 2000)
				End = true;

			if(_current->GetRect().bottom == 20000)
			{
				StateDepotType::iterator it;
				for (it = StateDepot.begin();
					it != StateDepot.end(); it++)
				{
					it->second->SetBossStage(true);
				}
			}
		}

		if(MissileHit && KirbyHitCount == 0)
		{
			BackPosition = Missilebk;
			Setposition(PlayerPos, KirbyPos, BackPosition);

			KirbyHp -= 1;
			transition(_T("Hit"));
			KirbyHitCount += 1;

			MissileHit = false;
		}
		else
			MissileHit = false;

		if(!Dead)
		{
			Rect tmprc;

			if(IntersectRect(&tmprc, &KirbyRect, &BossBase.GetBBoxRect()) && KirbyHitCount == 0)
			{
				KirbyHp -= 1;

				transition(_T("Hit"));

				KirbyHitCount += 1;
			}

			std::list<Enemies*> eList = EnemiesDepot.getList();
			std::list<Enemies*>::iterator jt;
			for (jt = eList.begin(); jt != eList.end(); jt++)
			{
				Rect tmp;
				if(IntersectRect(&tmp, &KirbyRect, &(*jt)->GetBBoxRect()) && KirbyHitCount == 0)
				{
					if(tmp.right < KirbyRect.right)
						BackPosition = true;
					else
						BackPosition = false;

					Setposition(PlayerPos, KirbyPos, BackPosition);

					KirbyHp -= 1;
					transition(_T("Hit"));
					KirbyHitCount += 1;
				}
			}
		}
		std::list<Item*> eList = ItemDepot.getList();
		std::list<Item*>::iterator jt;
		for (jt = eList.begin(); jt != eList.end(); jt++)
		{
			Rect tmp;
			if(IntersectRect(&tmp, &KirbyRect, &(*jt)->GetRect()))
			{
				if((*jt)->ReturnEff() == 100)
				{
					(*jt)->SetDel(true);
					transition(_T("Star"));
				}
			}
		}

		if(KirbyHp <= 0 && !KirbyRerease)
		{
			KirbyRerease = true;
			ItemDepot.StarPush(KirbyPos, BackPosition);
		}

		if (_current)
			_current->Update(tick);

		if (BBox)
			dynamic_cast<SquareBox*>(BBox)->SetRect(KirbyRect);

		DWORD timeE = ::GetTickCount() - timeF;

		std::wostringstream oss;
		oss << _T("CutterKirbyHp : ") << KirbyHp << _T("\n");

		::OutputDebugString(oss.str().c_str());
	}
}

Point CutterKirby::RetrunPlayerPos() const
{
	return PlayerPos;
}
Point CutterKirby::RetrunKirbyPos() const
{
	return KirbyPos;
}
void CutterKirby::Setposition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;
	KirbyPos = kpt;
	BackPosition = back;

	StateDepotType::iterator it;
	for (it = StateDepot.begin();
		it != StateDepot.end(); it++)
	{
		it->second->SetPosition(PlayerPos, KirbyPos, BackPosition);
	}
}
void CutterKirby::init()
{
	static CutterKirbyIdle idle;
	static CutterKirbyMove move;
	static CutterKirbyRun run;
	static CutterKirbyJump jump;
	static CutterKirbyLanding landing;
	static CutterKirbyFloat flo;
	static CutterKirbyHit hit;
	static CutterKirbyShot shot;
	static CutterKirbyDead dead;
	static CutterKirbyStarIn star;
	static CutterKirbyDance dance;

	idle.SetPosition(PlayerPos, KirbyPos, BackPosition);
	move.SetPosition(PlayerPos, KirbyPos, BackPosition);
	run.SetPosition(PlayerPos, KirbyPos, BackPosition);
	jump.SetPosition(PlayerPos, KirbyPos, BackPosition);
	landing.SetPosition(PlayerPos, KirbyPos, BackPosition);
	flo.SetPosition(PlayerPos, KirbyPos, BackPosition);
	hit.SetPosition(PlayerPos, KirbyPos, BackPosition);
	shot.SetPosition(PlayerPos, KirbyPos, BackPosition);
	dead.SetPosition(PlayerPos, KirbyPos, BackPosition);
	star.SetPosition(PlayerPos, KirbyPos, BackPosition);
	dance.SetPosition(PlayerPos, KirbyPos, BackPosition);

	AddEntry(_T("Idle"), &idle);
	AddEntry(_T("Move"), &move);
	AddEntry(_T("Run"), &run);
	AddEntry(_T("Jump"), &jump);
	AddEntry(_T("Landing"), &landing);
	AddEntry(_T("Float"), &flo);
	AddEntry(_T("Hit"), &hit);
	AddEntry(_T("Shot"), &shot);
	AddEntry(_T("Dead"), &dead);
	AddEntry(_T("Star"), &star);
	AddEntry(_T("Dance"), &dance);

	transition(_T("Landing"));
}
Vector CutterKirby::GetPosition() const
{
	Vector tmp(KirbyPos);
	return tmp;
}
Rect CutterKirby::ReturnDrainRect()
{
	if (_current)
	{
		return _current->GetRect();
	}
	return Rect(0,0,0,0);
}
bool CutterKirby::ReturnBack() const
{
	return BackPosition;
}
bool CutterKirby::ReturnDead() const
{
	return Dead;
}
bool CutterKirby::ReturnEnd() const
{
	return End;
}
void CutterKirby::KirbyReset()
{
	PlayerPos.x = 375;
	PlayerPos.y = 0;
	KirbyPos.x = 200;
	KirbyPos.y = 0;

	Setposition(PlayerPos, KirbyPos, false);

	KirbyHitCount = 0;

	KirbyHp = 2;
	KirbyState = 4;
	KirbyRerease = false;
	MoveAccCount = 0;

	RemoveEntry(_T("Dead"));

	static CutterKirbyDead dead;
	dead.SetPosition(PlayerPos, KirbyPos, BackPosition);
	dead.Reset();
	AddEntry(_T("Dead"), &dead);

	StateDepotType::iterator it;
	for (it = StateDepot.begin();
		it != StateDepot.end(); it++)
	{
		it->second->SetBossStage(false);
	}

	Dead = false;
	End = false;
	Reset = true;
	transition(_T("Landing"));
}
void CutterKirby::SetReset(const bool& re)
{
	Reset = re;
}
char CutterKirby::ReturnHP() const
{
	return KirbyHp;
}
bool CutterKirby::ReturnType() const
{
	return KirbyRerease;
}
void CutterKirby::SetMissileHit(const bool& bk)
{
	MissileHit = true;
	Missilebk = !bk;
}
BoundaryBox* CutterKirby::GetBBox() const
{
	return BBox;
}
void CutterKirby::CutterCho()
{
	KirbyHp = 2;
}
void CutterKirby::SetRerease()
{
	KirbyHp = 2;
	KirbyRerease = false;
}