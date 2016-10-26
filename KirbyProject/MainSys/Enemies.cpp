#include "Enemies.h"

Enemies::Enemies(const Point& pt)
:EnemiePos(pt), update_dt(0), PlayerPos(375,0), DrainEnemie(false)
, BackPosition(false), MoveAcc(0), MoveAccCount(0), EnemieType(0), StarHit(false)
, EnemieState(4), Wallcount(0), EnemieHp(10), update_dt_hit(0), update_dt2(0)
, AirHit(false), MoveEnemie(0), BBox(NULL)
{
	SquareBox* pBox = new SquareBox;

	EnemieRect.left = EnemiePos.x- EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieRect.left + EnemieWidth;
	EnemieRect.bottom = EnemieRect.top + EnemieHeight;

	pBox->SetRect(EnemieRect);

	BBox = pBox;
}
Enemies::~Enemies()
{
	if (BBox)
		delete BBox;
}
void Enemies::Load(const BYTE& type)
{
	init(type);
	if(EnemieType == 3)
		EnemieHp = 5;
}
void Enemies::Input(DWORD tick)
{
	if (_current)
		_current->Input(tick);	
}
void Enemies::Draw(HDC hdc)
{
	Rect tmprect;

	if(IntersectRect(&tmprect, &EnemieRect, &GameGlobal.rcClient))
	{
		if (_current)
			_current->Draw(hdc);
		if (BBox)
			BBox->Draw(hdc);
	}
}
void Enemies::Update(DWORD tick)
{
	EnemieRect.left = EnemiePos.x- EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieRect.left + EnemieWidth;
	EnemieRect.bottom = EnemieRect.top + EnemieHeight;

	Point tmp;
	tmp = EnemiePos;
	tmp.x = tmp.x - EnemieWidth/2;
	tmp.y = tmp.y - EnemieHeight/2;

	int CollideCount = 0;

	BYTE Stand = 0;

	Rect tmprect;

	if(IntersectRect(&tmprect, &EnemieRect, &DrainRect) && EnemieHp > 0)
	{
		DrainEnemie = true;
		transition(_T("Drain"));
		if(_current)
			_current->SetKirbyPoint(KirbyPos);

		if (BBox)
			dynamic_cast<SquareBox*>(BBox)->SetRect(Rect(1000,1000,1000,1000));
	}
	if(DrainEnemie && _current->GetRect().right == 0 && EnemieHp > 0)
	{
		transition(_T("Drain"));
		if(_current)
			_current->SetKirbyPoint(KirbyPos);

		if (BBox)
			dynamic_cast<SquareBox*>(BBox)->SetRect(Rect(1000,1000,1000,1000));
	}

	if(EnemieType != 3)
	{
		std::list<Block*> bList = BlockDepot.getList();
		std::list<Block*>::iterator it;
		for (it = bList.begin(); it != bList.end(); it++)
		{
			Rect tmp;

			if(IntersectRect(&tmp, &EnemieRect, &(*it)->GetBBoxRect()))
			{
				BYTE tmpstate = BBox->BoxIsCollide((*it)->getBBox(), !BackPosition);

				CollideCount++;
				if(tmpstate == 0)
				{
					Rect tmp = (*it)->GetBBoxRect();

					EnemiePos.y = tmp.top - (EnemieHeight/2) + 5;

					_current->GetStand(true, false);
					_current->GetState(0);
					_current->SetCharPoint(EnemiePos);

					Stand = 1;
					EnemieState = tmpstate;
				}
				else if(tmpstate == 10)
				{
					Rect tmp = (*it)->GetBBoxRect();

					EnemiePos.y = tmp.top - (EnemieHeight/2) + 5;

					_current->GetStand(true, false);
					_current->GetState(2);
					_current->SetCharPoint(EnemiePos);

					Stand = 1;
					EnemieState = tmpstate;
				}
				else if(tmpstate == 20)
				{
					Rect tmp = (*it)->GetBBoxRect();

					EnemiePos.y = tmp.top - (EnemieHeight/2) + 5;

					_current->GetStand(true, false);
					_current->GetState(1);
					_current->SetCharPoint(EnemiePos);

					Stand = 1;
					EnemieState = tmpstate;
				}
				if(tmpstate == 1)
				{
					_current->GetState(1);
					EnemieState = tmpstate;
				}
				else if(tmpstate == 2)
				{
					_current->GetState(2);
					EnemieState = tmpstate;
				}
				else if(tmpstate == 3)
				{
					_current->GetState(3);
					EnemieState = tmpstate;
				}

				if(CollideCount >= 3)
				{
					break;
				}
			}
		}
	}
	else
	{
		_current->SetCharPoint(EnemiePos);
		_current->GetStand(true, true);
		CollideCount++;
	}

	if(CollideCount == 0)
	{
		if (_current)
		{
			_current->GetStand(false, false);
			_current->GetState(0);
		}
		EnemieState = 4;
	}

	if(EnemieHitCount != 0)
	{
		if(update_dt_hit > 100)
		{
			EnemieHitCount += 1;

			update_dt_hit %= 100;
		}
		update_dt_hit += tick;
	}
	if(EnemieHitCount > 2)
		EnemieHitCount = 0;

	Rect Tmp;
	if(StarHit)
	{
		Setposition(PlayerPos, EnemiePos, BackPosition);

		transition(_T("Hit"));

		EnemieHp = 0;

		StarHit = false;
	}
	if(AirHit)
	{
		if(Tmp.right < EnemieRect.right)
			BackPosition = false;
		else
			BackPosition = true;

		Setposition(PlayerPos, EnemiePos, BackPosition);

		EnemieHp -= 5;
		transition(_T("Hit"));

		AirHit = false;
	}
	if(IntersectRect(&Tmp, &EnemieRect, &KirbyRect) && EnemieHitCount == 0 && !DrainEnemie && EnemieHp > 0)
	{
		if(Tmp.right < EnemieRect.right)
			BackPosition = false;
		else
			BackPosition = true;

		Setposition(PlayerPos, EnemiePos, BackPosition);

		EnemieHp -= 4;
		if(EnemieType == 3)
			_current->GetStand(true, false);
		transition(_T("Hit"));

		EnemieHitCount += 1;
	}

	if(update_dt2 > 300 && EnemieHp <= 0 && !DrainEnemie)
	{
		if(EnemieHp <= 0)
		{
			Rect rc(1000,1000,1000,1000);

			if (BBox)
				dynamic_cast<SquareBox*>(BBox)->SetRect(rc);

			transition(_T("Dead"));
		}
		update_dt2 %= 300;
	}
	if(EnemieHp <= 0)
	{
		Setposition(PlayerPos, EnemiePos, BackPosition);
		update_dt2 += tick;
	}

	if (_current)
		_current->Update(tick);

	if (BBox && EnemieHp > 0 && !DrainEnemie)
		dynamic_cast<SquareBox*>(BBox)->SetRect(EnemieRect);
}

Point Enemies::RetrunEnemiePos() const
{
	return PlayerPos;
}
void Enemies::Setposition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;
	EnemiePos = kpt;
	BackPosition = back;

	StateDepotType::iterator it;
	for (it = StateDepot.begin();
		it != StateDepot.end(); it++)
	{
		it->second->SetPosition(PlayerPos, EnemiePos, BackPosition);
	}
}
void Enemies::init(const BYTE& type)
{
	move.SetPosition(PlayerPos, EnemiePos, BackPosition);
	hit.SetPosition(PlayerPos, EnemiePos, BackPosition);
	dead.SetPosition(PlayerPos, EnemiePos, BackPosition);
	drain.SetPosition(PlayerPos, EnemiePos, BackPosition);
	end.SetPosition(PlayerPos, EnemiePos, BackPosition);
	idle.SetPosition(PlayerPos, EnemiePos, BackPosition);
	attack.SetPosition(PlayerPos, EnemiePos, BackPosition);
	fly.SetPosition(PlayerPos, EnemiePos, BackPosition);

	EnemieType = type;

	if(EnemieType == 1)
	{
		Animation* Anitmp1 = AniDepot["WaddleDeeMove"]->clone();
		Animation* Anitmp2 = AniDepot["WaddleDeeMoveBack"]->clone();
		move.AniEnter(Anitmp1, Anitmp2);

		Anitmp1 = AniDepot["WaddleDeeHit"]->clone();
		Anitmp2 = AniDepot["WaddleDeeHitBack"]->clone();
		hit.AniEnter(Anitmp1, Anitmp2);

		Anitmp1 = AniDepot["WaddleDeeDrainHit"]->clone();
		Anitmp2 = AniDepot["WaddleDeeDrainHitBack"]->clone();
		drain.AniEnter(Anitmp1, Anitmp2);

		Anitmp1 = AniDepot["EnemiesDead"]->clone();
		dead.AniEnter(Anitmp1, NULL);

		AddEntry(_T("Idle"), &move);
	}
	else if(EnemieType == 2)
	{
		Animation* Anitmp1 = AniDepot["KibbleIdle"]->clone();
		Animation* Anitmp2 = AniDepot["KibbleIdleBack"]->clone();
		idle.AniEnter(Anitmp1, Anitmp2);

		Anitmp1 = AniDepot["KibbleHit"]->clone();
		Anitmp2 = AniDepot["KibbleHitBack"]->clone();
		hit.AniEnter(Anitmp1, Anitmp2);

		Anitmp1 = AniDepot["KibbleDrainHit"]->clone();
		Anitmp2 = AniDepot["KibbleDrainHitBack"]->clone();
		drain.AniEnter(Anitmp1, Anitmp2);

		Anitmp1 = AniDepot["EnemiesDead"]->clone();
		dead.AniEnter(Anitmp1, NULL);

		Anitmp1 = AniDepot["KibbleAtt"]->clone();
		Anitmp2 = AniDepot["KibbleAttBack"]->clone();
		attack.AniEnter(Anitmp1, Anitmp2);

		AddEntry(_T("Idle"), &idle);
		AddEntry(_T("Attack"), &attack);
	}
	else if(EnemieType == 3)
	{
		Animation* Anitmp1 = AniDepot["BrontoMove"]->clone();
		Animation* Anitmp2 = AniDepot["BrontoMoveBack"]->clone();
		fly.AniEnter(Anitmp1, Anitmp2);

		Anitmp1 = AniDepot["BrontoHit"]->clone();
		Anitmp2 = AniDepot["BrontoHitBack"]->clone();
		hit.AniEnter(Anitmp1, Anitmp2);

		Anitmp1 = AniDepot["BrontoDrainHit"]->clone();
		Anitmp2 = AniDepot["BrontoDrainHitBack"]->clone();
		drain.AniEnter(Anitmp1, Anitmp2);

		Anitmp1 = AniDepot["EnemiesDead"]->clone();
		dead.AniEnter(Anitmp1, NULL);

		AddEntry(_T("Idle"), &fly);
	}

	AddEntry(_T("Hit"), &hit);
	AddEntry(_T("Dead"), &dead);
	AddEntry(_T("Drain"), &drain);
	AddEntry(_T("End"), &end);

	transition(_T("Idle"));
}
Vector Enemies::GetPosition() const
{
	Vector tmp(EnemiePos);
	return tmp;
}
Rect Enemies::GetRect() const
{
	return EnemieRect;
}
void Enemies::SetPlayerPos(const LONG& px)
{
	if(MoveEnemie == 0)
		MoveEnemie = px;

	if(MoveEnemie < px)
	{
		MoveEnemie = px - MoveEnemie;
	}
	else if(MoveEnemie > px)
	{
		MoveEnemie = -(MoveEnemie - px);
	}
	else
		MoveEnemie = 0;

	EnemiePos.x -= MoveEnemie;

	MoveEnemie = px;
}
Rect Enemies::GetBBoxRect() const
{
	return dynamic_cast<SquareBox*>(BBox)->getBox();
}
void Enemies::SetKirbyPos(const Point& kt)
{
	KirbyPos = kt;

	if(_current)
		_current->SetKirbyPoint(KirbyPos);

	KirbyRect.left = kt.x- 60/2;
	KirbyRect.top = kt.y - 58/2;
	KirbyRect.right = KirbyRect.left + 60;
	KirbyRect.bottom = KirbyRect.top + 58;
}
void Enemies::SetDrainRect(const Rect& rc)
{
	DrainRect = rc;
}
BYTE Enemies::ReturnType() const
{
	return EnemieType;
}
void Enemies::GetStarHit(const bool& hit, const bool& bk)
{
	StarHit = hit;
	BackPosition = bk;
}
void Enemies::GetAirHit(const bool& hit, const bool& bk)
{
	AirHit = hit;
	BackPosition = bk;
}
BoundaryBox* Enemies::getBBox()
{
	return BBox;
}
bool Enemies::DrainReturn() const
{
	return DrainEnemie;
}
Rect Enemies::DeadCon()
{
	if(_current)
	{
		return _current->GetRect();
	}

	return Rect(0,0,0,0);
}
void Enemies::DeadSet(const BYTE& st)
{
	DeadType = st;
}