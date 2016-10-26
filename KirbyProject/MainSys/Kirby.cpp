#include "Kirby.h"

Kirby::Kirby()
:KirbyPos(200, 0), PlayerPos(375, 0), update_dt(0),
BackPosition(false), MoveAcc(0), MoveAccCount(0)
, KirbyState(4), Wallcount(0), KirbyHp(10), KirbyHitCount(0)
,update_dt_hit(0), DrainC(false), KirbyFat(0), update_drain(0)
, Dead(false), End(false), Reset(false), DrainIn(false)
,MissileHit(false), StageChange(false), BBox(NULL), Sound(true)
{
	SquareBox* pBox = new SquareBox;

	KirbyRect.left = KirbyPos.x- KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyRect.left + KirbyWidth;
	KirbyRect.bottom = KirbyRect.top + KirbyHeight;

	pBox->SetRect(KirbyRect);

	BBox = pBox;
}
Kirby::~Kirby()
{
	if (BBox)
		delete BBox;
}
void Kirby::Load(const Rect& rc)
{
	ClientRect = rc;

	init();
}
void Kirby::Input(DWORD tick)
{
	if (_current)
		_current->Input(tick);	
}
void Kirby::Draw(HDC hdc)
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
void Kirby::Update(DWORD tick)
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

						_current->GetStand(true, false);
						_current->GetState(0);
						_current->SetCharPoint(KirbyPos);

						Stand = 1;
						KirbyState = tmpstate;
					}
					if(tmpstate == 1)
					{
						_current->GetState(1);
						KirbyState = tmpstate;
					}
					else if(tmpstate == 2)
					{
						_current->GetState(2);
						KirbyState = tmpstate;
					}
					else if(tmpstate == 3)
					{
						_current->GetStand(false, true);
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

		if(_current->GetRect().bottom == 1900)
			Dead = true;

		if(_current->GetRect().bottom == 2000)
			End = true;

		if(_current->GetRect().right > 0)
		{
			DrainC = true;
			DrainIn = true;
		}
		else
		{
			DrainC = false;
		}
		if(EnemiesDepot.ReturnDrain())
		{
			_current->GetState(99);
		}

		if(_current->GetRect().left == 2000)
			KirbyFat = 0;

		if(_current->GetRect().bottom == 20000)
		{
			StateDepotType::iterator it;
			for (it = StateDepot.begin();
				it != StateDepot.end(); it++)
			{
				it->second->SetBossStage(true);
			}
			StageChange = true;
		}

		if(MissileHit && KirbyHitCount == 0)
		{
			BackPosition = Missilebk;
			Setposition(PlayerPos, KirbyPos, BackPosition);

			KirbyHp -= 1;
			if(KirbyFat == 0)
				transition(_T("Hit"));
			else
				transition(_T("HitFat"));
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
				if(KirbyFat == 0)
					transition(_T("Hit"));
				else
					transition(_T("HitFat"));

				KirbyHitCount += 1;
			}

			std::list<Enemies*> eList = EnemiesDepot.getList();
			std::list<Enemies*>::iterator jt;
			for (jt = eList.begin(); jt != eList.end(); jt++)
			{
				Rect tmp;

				Rect tmprc = KirbyRect;

				tmprc.left -= 10;
				tmprc.top -= 10;
				tmprc.right += 10;
				tmprc.bottom += 10;

				if(IntersectRect(&tmp, &tmprc, &(*jt)->GetRect()) && DrainIn && KirbyFat == 0)
				{
					if(!BackPosition)
					{
						if(tmp.left > KirbyRect.left)
						{
							RemoveEntry(_T("Drain"));

							static KirbyDrain drain;
							drain.SetPosition(PlayerPos, KirbyPos, BackPosition);
							drain.Reset();
							AddEntry(_T("Drain"), &drain);

							SndDepot["DrainS"]->Stop();
							SndDepot["DrainR"]->Stop();
							transition(_T("IdleFat"));
							KirbyFat = (*jt)->ReturnType();
							DrainIn = false;
						}
						else
						{
							Rect Test = (*jt)->GetRect();

							if(tmp.right < KirbyRect.right)
								BackPosition = true;
							else
								BackPosition = false;

							RemoveEntry(_T("Drain"));

							static KirbyDrain drain;
							drain.SetPosition(PlayerPos, KirbyPos, BackPosition);
							drain.Reset();
							AddEntry(_T("Drain"), &drain);

							Setposition(PlayerPos, KirbyPos, BackPosition);

							SndDepot["DrainS"]->Stop();
							SndDepot["DrainR"]->Stop();

							KirbyHp -= 1;
							transition(_T("Hit"));
							KirbyHitCount += 1;
							DrainIn = false;
						}
					}
					else
					{
						if(tmp.right < KirbyRect.right)
						{
							RemoveEntry(_T("Drain"));

							static KirbyDrain drain;
							drain.SetPosition(PlayerPos, KirbyPos, BackPosition);
							drain.Reset();
							AddEntry(_T("Drain"), &drain);

							SndDepot["DrainS"]->Stop();
							SndDepot["DrainR"]->Stop();
							transition(_T("IdleFat"));
							KirbyFat = (*jt)->ReturnType();
							DrainIn = false;
						}
						else
						{
							if(tmp.right < KirbyRect.right)
								BackPosition = true;
							else
								BackPosition = false;

							RemoveEntry(_T("Drain"));

							static KirbyDrain drain;
							drain.SetPosition(PlayerPos, KirbyPos, BackPosition);
							drain.Reset();
							AddEntry(_T("Drain"), &drain);

							Setposition(PlayerPos, KirbyPos, BackPosition);

							SndDepot["DrainS"]->Stop();
							SndDepot["DrainR"]->Stop();

							KirbyHp -= 1;
							transition(_T("Hit"));
							KirbyHitCount += 1;
							DrainIn = false;
						}
					}
				}
				else if(IntersectRect(&tmp, &KirbyRect, &(*jt)->GetBBoxRect()) && KirbyHitCount == 0 && !DrainC && KirbyFat == 0 && !DrainIn)
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
				else if(IntersectRect(&tmp, &KirbyRect, &(*jt)->GetBBoxRect()) && KirbyHitCount == 0 && !DrainC && KirbyFat != 0 && !DrainIn)
				{
					if(tmp.right < KirbyRect.right)
						BackPosition = true;
					else
						BackPosition = false;

					Setposition(PlayerPos, KirbyPos, BackPosition);

					KirbyHp -= 1;
					transition(_T("HitFat"));
					KirbyHitCount += 1;
				}
			}
		} // if(Dead)
		{
			std::list<Item*> eList = ItemDepot.getList();
			std::list<Item*>::iterator jt;
			for (jt = eList.begin(); jt != eList.end(); jt++)
			{
				Rect tmp;
				if(IntersectRect(&tmp, &KirbyRect, &(*jt)->GetRect()) && DrainIn && KirbyFat == 0)
				{
					if(!BackPosition)
					{
						RemoveEntry(_T("Drain"));

						static KirbyDrain drain;
						drain.SetPosition(PlayerPos, KirbyPos, BackPosition);
						drain.Reset();
						AddEntry(_T("Drain"), &drain);

						SndDepot["DrainS"]->Stop();
						SndDepot["DrainR"]->Stop();
						transition(_T("IdleFat"));
						DrainIn = false;
					}
					else
					{
						RemoveEntry(_T("Drain"));

						static KirbyDrain drain;
						drain.SetPosition(PlayerPos, KirbyPos, BackPosition);
						drain.Reset();
						AddEntry(_T("Drain"), &drain);

						SndDepot["DrainS"]->Stop();
						SndDepot["DrainR"]->Stop();
						transition(_T("IdleFat"));
						DrainIn = false;
					}
					if((*jt)->ReturnEff() == 10)
						KirbyFat = 2;

					(*jt)->SetDel(true);
				}
				else if(IntersectRect(&tmp, &KirbyRect, &(*jt)->GetRect()))
				{
					if((*jt)->ReturnEff() == 100)
					{
						(*jt)->SetDel(true);
						transition(_T("KirbyStar"));
					}
					else if((*jt)->ReturnEff() == 70)
					{
						(*jt)->SetDel(true);
						if(Sound)
						{
							SndDepot["Item"]->Play();
							Sound = false;
						}
						KirbyHp = 10;
					}
					else if((*jt)->ReturnEff() == 200)
					{
						(*jt)->SetDel(true);
						transition(_T("Dance"));
					}
				}
			}
		}
		Sound = true;

		if(KirbyHp <= 0)
		{
			transition(_T("Dead"));
		}

		if(KirbyHp < 0)
			KirbyHp = 0;

		if (_current)
			_current->Update(tick);

		if (BBox)
			dynamic_cast<SquareBox*>(BBox)->SetRect(KirbyRect);

		DWORD timeE = ::GetTickCount() - timeF;

		std::wostringstream oss;
		std::wostringstream sss;
		oss << _T("KirbyPos : ") << KirbyPos.x << _T(',') << KirbyPos.y << _T("\n");
		sss << _T("PlayerPos : ") <<PlayerPos.x << _T(',') << PlayerPos.y << _T("\n");

		::OutputDebugString(oss.str().c_str());
		::OutputDebugString(sss.str().c_str());
	}
}

Point Kirby::RetrunPlayerPos() const
{
	return PlayerPos;
}
Point Kirby::RetrunKirbyPos() const
{
	return KirbyPos;
}
void Kirby::Setposition(const Point& ppt, const Point& kpt, const bool& back)
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
void Kirby::init()
{
	static KirbyIdle idle;
	static KirbyMove move;
	static KirbyRun run;
	static KirbyJump jump;
	static KirbyLanding landing;
	static KirbyFloat flo;
	static KirbyDrain drain;
	static KirbyHit hit;
	static KirbyFatIdle idlefat;
	static KirbyFatMove movefat;
	static KirbyFatRun runfat;
	static KirbyFatJump jumpfat;
	static KirbyFatLanding landingfat;
	static KirbyShot shot;
	static KirbyFatHit hitfat;
	static KirbyDead dead;
	static KirbyEat eat;
	static KirbyStarIn star;
	static KirbyDance dance;

	idle.SetPosition(PlayerPos, KirbyPos, BackPosition);
	idlefat.SetPosition(PlayerPos, KirbyPos, BackPosition);
	move.SetPosition(PlayerPos, KirbyPos, BackPosition);
	run.SetPosition(PlayerPos, KirbyPos, BackPosition);
	jump.SetPosition(PlayerPos, KirbyPos, BackPosition);
	landing.SetPosition(PlayerPos, KirbyPos, BackPosition);
	flo.SetPosition(PlayerPos, KirbyPos, BackPosition);
	drain.SetPosition(PlayerPos, KirbyPos, BackPosition);
	hit.SetPosition(PlayerPos, KirbyPos, BackPosition);
	movefat.SetPosition(PlayerPos, KirbyPos, BackPosition);
	runfat.SetPosition(PlayerPos, KirbyPos, BackPosition);
	jumpfat.SetPosition(PlayerPos, KirbyPos, BackPosition);
	landingfat.SetPosition(PlayerPos, KirbyPos, BackPosition);
	shot.SetPosition(PlayerPos, KirbyPos, BackPosition);
	hitfat.SetPosition(PlayerPos, KirbyPos, BackPosition);
	dead.SetPosition(PlayerPos, KirbyPos, BackPosition);
	eat.SetPosition(PlayerPos, KirbyPos, BackPosition);
	star.SetPosition(PlayerPos, KirbyPos, BackPosition);
	dance.SetPosition(PlayerPos, KirbyPos, BackPosition);

	AddEntry(_T("Idle"), &idle);
	AddEntry(_T("IdleFat"), &idlefat);
	AddEntry(_T("Move"), &move);
	AddEntry(_T("Run"), &run);
	AddEntry(_T("Jump"), &jump);
	AddEntry(_T("Landing"), &landing);
	AddEntry(_T("Float"), &flo);
	AddEntry(_T("Drain"), &drain);
	AddEntry(_T("Hit"), &hit);
	AddEntry(_T("MoveFat"), &movefat);
	AddEntry(_T("RunFat"), &runfat);
	AddEntry(_T("JumpFat"), &jumpfat);
	AddEntry(_T("LandingFat"), &landingfat);
	AddEntry(_T("Shot"), &shot);
	AddEntry(_T("HitFat"), &hitfat);
	AddEntry(_T("Dead"), &dead);
	AddEntry(_T("Eat"), &eat);
	AddEntry(_T("KirbyStar"), &star);
	AddEntry(_T("Dance"), &dance);

	transition(_T("Landing"));
}
Vector Kirby::GetPosition() const
{
	Vector tmp(KirbyPos);
	return tmp;
}
Rect Kirby::ReturnDrainRect()
{
	if (_current)
	{
		return _current->GetRect();
	}
	return Rect(0,0,0,0);
}
bool Kirby::ReturnBack() const
{
	return BackPosition;
}
bool Kirby::ReturnDead() const
{
	return Dead;
}
bool Kirby::ReturnEnd() const
{
	return End;
}
void Kirby::KirbyReset()
{
	PlayerPos.x = 375;
	PlayerPos.y = 0;
	KirbyPos.x = 200;
	KirbyPos.y = 0;

	Setposition(PlayerPos, KirbyPos, false);

	KirbyHitCount = 0;

	KirbyHp = 10;
	KirbyState = 4;
	KirbyFat = 0;
	MoveAccCount = 0;

	RemoveEntry(_T("Dead"));

	static KirbyDead dead;
	dead.SetPosition(PlayerPos, KirbyPos, BackPosition);
	dead.Reset();
	AddEntry(_T("Dead"), &dead);

	static KirbyDance dance;
	dance.SetPosition(PlayerPos, KirbyPos, BackPosition);
	AddEntry(_T("Dance"), &dance);

	StateDepotType::iterator it;
	for (it = StateDepot.begin();
		it != StateDepot.end(); it++)
	{
		it->second->SetBossStage(false);
	}

	Dead = false;
	End = false;
	Reset = true;
	StageChange = false;
	transition(_T("Landing"));
}
void Kirby::SetReset(const bool& re)
{
	Reset = re;
}
char Kirby::ReturnHP() const
{
	return KirbyHp;
}
BYTE Kirby::ReturnType() const
{
	if(_current->GetRect().bottom == 4000)
		return KirbyFat;
	else
		return 0;
}
void Kirby::SetMissileHit(const bool& bk)
{
	MissileHit = true;
	Missilebk = !bk;
}
BoundaryBox* Kirby::GetBBox() const
{
	return BBox;
}
void Kirby::TypeReset()
{
	KirbyFat = 0;
}
bool Kirby::ReturnStageChange() const
{
	return StageChange;
}