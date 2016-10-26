#include "EnemiesState.h"
#include "Enemies.h"
#include "MissileManager.h"

/////////////////////////////////////////////////////////////
// 걷기 동작
/////////////////////////////////////////////////////////////
EnemieMove::EnemieMove()
: update_dt(0), MoveAcc(0), update_delay(30)
, KeyPush(true), update_dt2(0), update_delay2(60)
, RightKey(false), Stand(false), Wall(0), MoveInput(0)
{
	MoveAni = NULL;
	MoveAniBack = NULL;
}
EnemieMove::~EnemieMove()
{
	SafeDelete(MoveAni);
	SafeDelete(MoveAniBack);
	//delete MoveAni;
	//delete MoveAniBack;
}
void EnemieMove::AniEnter(Animation* fr, Animation* bk)
{
	MoveAni = fr;
	MoveAniBack = bk;
}
void EnemieMove::Enter()
{

}
void EnemieMove::Input(DWORD tick)
{	
	//if(update_dt2 > update_delay2)
	//{
	//	int count = update_dt2/update_delay2;

	//	for(int i = 0; i < count; i++)
	//	{
	//		MoveInput += 1;

	//		if(MoveInput >= 30)
	//		{
	//			MoveInput = 0;
	//			BackPosition = !BackPosition;
	//		}
	//	}

	//	update_dt2 %= update_delay2;
	//}

	//update_dt2 += tick;
}
void EnemieMove::Update(DWORD tick)
{
	// 이동좌표 업데이트
	if(update_dt > update_delay)
	{
		int count = update_dt / update_delay;
		for(int i = 0; i < count; i++)
		{
			Rect tmp;
			if(BackPosition)
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(!(Wall == 2))
				{
					EnemiePos.x += MoveAcc;
				}
				else
					BackPosition = !BackPosition;

			}
			else if(!BackPosition)
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(!(Wall == 1))
					EnemiePos.x -= MoveAcc;
				else
					BackPosition = !BackPosition;
			}
		}
		update_dt = update_dt % update_delay;
	}
	update_dt += tick;

	if (pMachine)
		dynamic_cast<Enemies*>(pMachine)->Setposition(PlayerPos, EnemiePos, BackPosition);

	if(!Stand)
	{
		EnemiePos.y += 1;
	}

	// 애니메이션 업데이트
	MoveAni->Update(tick);
	MoveAniBack->Update(tick);
}
void EnemieMove::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		MoveAni->SetRect(Rect(EnemieRect.left, EnemieRect.top, EnemieRect.right+5, EnemieRect.bottom));
		MoveAni->Draw(hdc);
	}
	else
	{
		MoveAniBack->SetRect(Rect(EnemieRect.left-5, EnemieRect.top, EnemieRect.right, EnemieRect.bottom));
		MoveAniBack->Draw(hdc);
	}
}
void EnemieMove::Leave()
{
}
void EnemieMove::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	EnemiePos = kpt;

	BackPosition = back;

	EnemieRect.left = EnemiePos.x - EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieWidth + EnemieRect.left;
	EnemieRect.bottom = EnemieHeight + EnemieRect.top;
}
void EnemieMove::GetState(const BYTE& wl)
{
	Wall = wl;
}
void EnemieMove::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void EnemieMove::SetCharPoint(const Point& kpt)
{
	EnemiePos = kpt;
}
void EnemieMove::SetKirbyPoint(const Point&)
{
}


/////////////////////////////////////////////////////////////
// 맞았을때 동작
/////////////////////////////////////////////////////////////
EnemieHit::EnemieHit()
: update_dt(0), MoveAcc(0), update_delay(20), JumpAcc(0)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20)
{
	HitAni = NULL;
	HitAniBack = NULL;
}
EnemieHit::~EnemieHit()
{
	SafeDelete(HitAni);
	SafeDelete(HitAniBack);
	//delete HitAni;
	//delete HitAniBack;
}
void EnemieHit::Enter()
{
}
void EnemieHit::AniEnter(Animation* fr, Animation* bk)
{
	HitAni = fr;
	HitAniBack = bk;
}
void EnemieHit::Input(DWORD tick)
{
	
}
void EnemieHit::Update(DWORD tick)
{
	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; i < count; i++)
		{
			if(BackPosition)
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(!(Wall == 1))
					EnemiePos.x -= MoveAcc;

				if(EnemiePos.x - EnemieWidth/2 < 0)
					EnemiePos.x = EnemieWidth/2;
			}
			else
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(!(Wall == 2))
					EnemiePos.x += MoveAcc;

				if(EnemiePos.x - EnemieWidth/2 < 0)
					EnemiePos.x = EnemieWidth/2;
			}
		}
		update_dt %= update_delay;
	}
	update_dt += tick;

	if(!Stand)
	{
		if(update_dt2 > update_delay2)
		{
			int count = update_dt2/update_delay2;
			for(int i = 0; i < count; i++)
			{
				JumpAcc += 2;

				if(JumpAcc >= 8)
					JumpAcc = 8;

				EnemiePos.y += JumpAcc;
			}
			update_dt2 %= update_delay2;
		}
		update_dt2 += tick;
	}

	if (pMachine)
		dynamic_cast<Enemies*>(pMachine)->Setposition(PlayerPos, EnemiePos, BackPosition);

	if(!(HitAni->IsPlaying()) || !(HitAniBack->IsPlaying()))
	{
		HitAni->reset();
		HitAniBack->reset();
		pMachine->transition(_T("Idle"));
	}

	HitAni->SetRect(Rect(EnemieRect.left, EnemieRect.top, EnemieRect.right+5, EnemieRect.bottom));
	HitAniBack->SetRect(Rect(EnemieRect.left-5, EnemieRect.top, EnemieRect.right, EnemieRect.bottom));

	HitAni->Update(tick);
	HitAniBack->Update(tick);
}
void EnemieHit::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		HitAni->Draw(hdc);
	}
	else
	{
		HitAniBack->Draw(hdc);
	}
}
void EnemieHit::Leave()
{
}
void EnemieHit::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	EnemiePos = kpt;

	BackPosition = back;

	EnemieRect.left = EnemiePos.x - EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieWidth + EnemieRect.left;
	EnemieRect.bottom = EnemieHeight + EnemieRect.top;
}
void EnemieHit::GetState(const BYTE& wl)
{
	Wall = wl;
}
void EnemieHit::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void EnemieHit::SetCharPoint(const Point& kpt)
{
	EnemiePos = kpt;
}
void EnemieHit::SetKirbyPoint(const Point&)
{
}

/////////////////////////////////////////////////////////////
// 흡수당할때 동작
/////////////////////////////////////////////////////////////
EnemieDrainHit::EnemieDrainHit()
: update_dt(0), MoveAcc(0), update_delay(40)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20)
, Acc(0)
{
	HitAni = NULL;
	HitAniBack = NULL;
}
EnemieDrainHit::~EnemieDrainHit()
{
	SafeDelete(HitAni);
	SafeDelete(HitAniBack);
	//delete HitAni;
	//delete HitAniBack;
}
void EnemieDrainHit::Enter()
{
}
void EnemieDrainHit::AniEnter(Animation* fr, Animation* bk)
{
	HitAni = fr;
	HitAniBack = bk;
}
void EnemieDrainHit::Input(DWORD tick)
{
	
}
void EnemieDrainHit::Update(DWORD tick)
{
	if(KirbyPos.x <= EnemiePos.x)
		BackPosition = true;
	else
		BackPosition = false;

	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; i < count; i++)
		{
			Acc++;

			MoveAcc += Acc;

			if(MoveAcc > 30)
				MoveAcc = 30;

			pos = pos + dir.normalize() * MoveAcc;

			EnemiePos.x = pos.x;
			EnemiePos.y = pos.y;
		}
		update_dt %= update_delay;
	}
	update_dt += tick;

	if (pMachine)
		dynamic_cast<Enemies*>(pMachine)->Setposition(PlayerPos, EnemiePos, BackPosition);

	HitAni->SetRect(Rect(EnemieRect.left, EnemieRect.top, EnemieRect.right+5, EnemieRect.bottom));
	HitAniBack->SetRect(Rect(EnemieRect.left-5, EnemieRect.top, EnemieRect.right, EnemieRect.bottom));

	HitAni->Update(tick);
	HitAniBack->Update(tick);

	Rect tmp;

	Rect KirbyRect;

	KirbyRect.left = KirbyPos.x- 60/2;
	KirbyRect.top = KirbyPos.y - 58/2;
	KirbyRect.right = KirbyRect.left + 60;
	KirbyRect.bottom = KirbyRect.top + 58;

	if(IntersectRect(&tmp, &EnemieRect, &KirbyRect))
	{
		if(tmp.width() > 25)
			pMachine->transition(_T("End"));
	}
}
void EnemieDrainHit::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		HitAni->Draw(hdc);
	}
	else
	{
		HitAniBack->Draw(hdc);
	}
}
void EnemieDrainHit::Leave()
{
}
void EnemieDrainHit::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	EnemiePos = kpt;

	BackPosition = back;

	EnemieRect.left = EnemiePos.x - EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieWidth + EnemieRect.left;
	EnemieRect.bottom = EnemieHeight + EnemieRect.top;
}
void EnemieDrainHit::GetState(const BYTE& wl)
{
	Wall = wl;
}
void EnemieDrainHit::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void EnemieDrainHit::SetCharPoint(const Point& kpt)
{
	EnemiePos = kpt;
}
void EnemieDrainHit::SetKirbyPoint(const Point& pt)
{
	origin = EnemiePos;
	pos = EnemiePos;

	Vector tmppt = pt;

	dir = tmppt - origin;

	KirbyPos = pt;
}

/////////////////////////////////////////////////////////////
// 죽을떄 동작
/////////////////////////////////////////////////////////////
EnemieDead::EnemieDead()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), HitEnd(false)
{
	DeadAni = NULL;
	DeadAniBack = NULL;
}
EnemieDead::~EnemieDead()
{
	SafeDelete(DeadAni);
	//delete DeadAni;
}
void EnemieDead::Enter()
{
}
void EnemieDead::AniEnter(Animation* fr, Animation* bk)
{
	DeadAni = fr;
	DeadAniBack = bk;
}
void EnemieDead::Input(DWORD tick)
{
	
}
void EnemieDead::Update(DWORD tick)
{
	if(!HitEnd)
	{
		SndDepot["HitEnd"]->Play();
		HitEnd = true;
	}

	if(!(DeadAni->IsPlaying()))
	{
		EnemiePos.x = 1000;
		EnemiePos.y = 1000;
	}

	if (pMachine)
		dynamic_cast<Enemies*>(pMachine)->Setposition(PlayerPos, EnemiePos, BackPosition);

	DeadAni->SetRect(Rect(EnemieRect.left, EnemieRect.top, EnemieRect.right+5, EnemieRect.bottom));

	DeadAni->Update(tick);

	if(!(DeadAni->IsPlaying()))
	{
		pMachine->transition(_T("End"));
	}
}
void EnemieDead::Draw(HDC hdc)
{
	DeadAni->Draw(hdc);
}
void EnemieDead::Leave()
{
}
void EnemieDead::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	EnemiePos = kpt;

	BackPosition = back;

	EnemieRect.left = EnemiePos.x - EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieWidth + EnemieRect.left;
	EnemieRect.bottom = EnemieHeight + EnemieRect.top;
}
void EnemieDead::GetState(const BYTE& wl)
{
	Wall = wl;
}
void EnemieDead::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void EnemieDead::SetCharPoint(const Point& kpt)
{
	EnemiePos = kpt;
}
void EnemieDead::SetKirbyPoint(const Point&)
{
}

/////////////////////////////////////////////////////////////
// 사라짐
/////////////////////////////////////////////////////////////
EnemieEnd::EnemieEnd()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0)
{
}
EnemieEnd::~EnemieEnd()
{
}
void EnemieEnd::Enter()
{
}
void EnemieEnd::AniEnter(Animation* fr, Animation* bk)
{
}
void EnemieEnd::Input(DWORD tick)
{
	
}
void EnemieEnd::Update(DWORD tick)
{
	if (pMachine)
		dynamic_cast<Enemies*>(pMachine)->Setposition(PlayerPos, EnemiePos, BackPosition);
}
void EnemieEnd::Draw(HDC hdc)
{
}
void EnemieEnd::Leave()
{
}
void EnemieEnd::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	EnemiePos = kpt;

	BackPosition = back;

	EnemieRect.left = EnemiePos.x - EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieWidth + EnemieRect.left;
	EnemieRect.bottom = EnemieHeight + EnemieRect.top;
}
void EnemieEnd::GetState(const BYTE& wl)
{
	Wall = wl;
}
void EnemieEnd::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void EnemieEnd::SetCharPoint(const Point& kpt)
{
	EnemiePos = kpt;
}
void EnemieEnd::SetKirbyPoint(const Point&)
{
}
/////////////////////////////////////////////////////////////
// 서있는 동작
/////////////////////////////////////////////////////////////
EnemieIdle::EnemieIdle()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0)
{
	IdleAni = NULL;
	IdleAniBack = NULL;
}
EnemieIdle::~EnemieIdle()
{
	SafeDelete(IdleAni);
	SafeDelete(IdleAniBack);
	//delete DeadAni;
}
void EnemieIdle::Enter()
{
}
void EnemieIdle::AniEnter(Animation* fr, Animation* bk)
{
	IdleAni = fr;
	IdleAniBack = bk;
}
void EnemieIdle::Input(DWORD tick)
{
}
void EnemieIdle::Update(DWORD tick)
{
	if(!Stand)
	{
		EnemiePos.y += 1;
	}
	if(KirbyPos.x < EnemiePos.x)
	{
		BackPosition = false;
	}
	else if(KirbyPos.x > EnemiePos.x)
	{
		BackPosition = true;
	}

	if (pMachine)
		dynamic_cast<Enemies*>(pMachine)->Setposition(PlayerPos, EnemiePos, BackPosition);

	IdleAni->Update(tick);
	IdleAniBack->Update(tick);

	if(!(IdleAni->IsPlaying()) || !(IdleAniBack->IsPlaying()))
	{
		IdleAni->reset();
		IdleAniBack->reset();
		pMachine->transition(_T("Attack"));
	}
}
void EnemieIdle::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		IdleAni->SetRect(Rect(EnemieRect.left-4, EnemieRect.top-9, EnemieRect.right+8, EnemieRect.bottom));
		IdleAni->Draw(hdc);
	}
	else
	{
		IdleAniBack->SetRect(Rect(EnemieRect.left-8, EnemieRect.top-9, EnemieRect.right+8, EnemieRect.bottom));
		IdleAniBack->Draw(hdc);
	}
}
void EnemieIdle::Leave()
{
}
void EnemieIdle::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	EnemiePos = kpt;

	BackPosition = back;

	EnemieRect.left = EnemiePos.x - EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieWidth + EnemieRect.left;
	EnemieRect.bottom = EnemieHeight + EnemieRect.top;
}
void EnemieIdle::GetState(const BYTE& wl)
{
	Wall = wl;
}
void EnemieIdle::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void EnemieIdle::SetCharPoint(const Point& kpt)
{
	EnemiePos = kpt;
}
void EnemieIdle::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}
/////////////////////////////////////////////////////////////
// 공격하는 동작
/////////////////////////////////////////////////////////////
EnemieAttack::EnemieAttack()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), AttackCount(0)
{
	AttackAni = NULL;
	AttackAniBack = NULL;
}
EnemieAttack::~EnemieAttack()
{
	SafeDelete(AttackAni);
	SafeDelete(AttackAniBack);
	//delete DeadAni;
}
void EnemieAttack::Enter()
{
}
void EnemieAttack::AniEnter(Animation* fr, Animation* bk)
{
	AttackAni = fr;
	AttackAniBack = bk;
}
void EnemieAttack::Input(DWORD tick)
{
	
}
void EnemieAttack::Update(DWORD tick)
{
	if(!Stand)
	{
		EnemiePos.y += 1;
	}

	if (pMachine)
		dynamic_cast<Enemies*>(pMachine)->Setposition(PlayerPos, EnemiePos, BackPosition);

	AttackAni->Update(tick);
	AttackAniBack->Update(tick);

	if((!(AttackAni->IsPlaying()) || !(AttackAniBack->IsPlaying())) && AttackCount < 3)
	{
		Rect tmp = GameGlobal.rcClient;

		tmp.left = tmp.left - 100;
		tmp.right = tmp.right + 100;

		Rect tmprc;

		if(::IntersectRect(&tmprc, &tmp, &EnemieRect))
		{
			MissileDepot.ECutterPush(EnemiePos, !BackPosition);
		}
		AttackAni->reset();
		AttackAniBack->reset();
		AttackCount++;
	}
	else if((!(AttackAni->IsPlaying()) || !(AttackAniBack->IsPlaying())) && AttackCount >= 3)
	{
		AttackAni->reset();
		AttackAniBack->reset();
		AttackCount = 0;
		pMachine->transition(_T("Idle"));
	}
}
void EnemieAttack::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AttackAni->SetRect(Rect(EnemieRect.left-4, EnemieRect.top-9, EnemieRect.right+8, EnemieRect.bottom));
		AttackAni->Draw(hdc);
	}
	else
	{
		AttackAniBack->SetRect(Rect(EnemieRect.left-8, EnemieRect.top-9, EnemieRect.right+8, EnemieRect.bottom));
		AttackAniBack->Draw(hdc);
	}
}
void EnemieAttack::Leave()
{
}
void EnemieAttack::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	EnemiePos = kpt;

	BackPosition = back;

	EnemieRect.left = EnemiePos.x - EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieWidth + EnemieRect.left;
	EnemieRect.bottom = EnemieHeight + EnemieRect.top;
}
void EnemieAttack::GetState(const BYTE& wl)
{
	Wall = wl;
}
void EnemieAttack::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void EnemieAttack::SetCharPoint(const Point& kpt)
{
	EnemiePos = kpt;
}
void EnemieAttack::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}

/////////////////////////////////////////////////////////////
// 공중을 나는 동작
/////////////////////////////////////////////////////////////
EnemieFly::EnemieFly()
: update_dt(0), MoveAcc(0), update_delay(30)
, KeyPush(true), update_dt2(0), update_delay2(60)
, RightKey(false), Wall(0), MoveInput(0)
, FlyInput(0), FlySet(false), Stand(true)
{
	FlyAni = NULL;
	FlyAniBack = NULL;
}
EnemieFly::~EnemieFly()
{
	SafeDelete(FlyAni);
	SafeDelete(FlyAniBack);
	//delete MoveAni;
	//delete MoveAniBack;
}
void EnemieFly::AniEnter(Animation* fr, Animation* bk)
{
	FlyAni = fr;
	FlyAniBack = bk;
}
void EnemieFly::Enter()
{

}
void EnemieFly::Input(DWORD tick)
{	
	if(update_dt2 > update_delay2)
	{
		int count = update_dt2/update_delay2;

		for(int i = 0; i < count; i++)
		{
			MoveInput += 1;

			if(MoveInput >= 50)
			{
				MoveInput = 0;
				BackPosition = !BackPosition;
			}
		}

		update_dt2 %= update_delay2;
	}

	update_dt2 += tick;
}
void EnemieFly::Update(DWORD tick)
{
	// 이동좌표 업데이트
	if(update_dt > update_delay)
	{
		int count = update_dt / update_delay;
		for(int i = 0; i < count; i++)
		{
			Rect tmp;
			if(BackPosition)
			{
				MoveAcc += 1;

				if(MoveAcc >= 4)
					MoveAcc = 4;

					EnemiePos.x += MoveAcc;
			}
			else if(!BackPosition)
			{
				MoveAcc += 1;

				if(MoveAcc >= 4)
					MoveAcc = 4;

					EnemiePos.x -= MoveAcc;
			}

			FlyInput++;
			if(FlySet)
				EnemiePos.y -= 4;
			else
				EnemiePos.y += 4;

			if(FlyInput > 25)
			{
				FlySet = !FlySet;
				FlyInput = 0;
			}
		}
		update_dt = update_dt % update_delay;
	}
	update_dt += tick;

	if (pMachine)
		dynamic_cast<Enemies*>(pMachine)->Setposition(PlayerPos, EnemiePos, BackPosition);

	// 애니메이션 업데이트
	FlyAni->Update(tick);
	FlyAniBack->Update(tick);
}
void EnemieFly::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		FlyAni->SetRect(Rect(EnemieRect.left-4, EnemieRect.top, EnemieRect.right+8, EnemieRect.bottom));
		FlyAni->Draw(hdc);
	}
	else
	{
		FlyAniBack->SetRect(Rect(EnemieRect.left-8, EnemieRect.top, EnemieRect.right+4, EnemieRect.bottom));
		FlyAniBack->Draw(hdc);
	}
}
void EnemieFly::Leave()
{
}
void EnemieFly::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	EnemiePos = kpt;

	BackPosition = back;

	EnemieRect.left = EnemiePos.x - EnemieWidth/2;
	EnemieRect.top = EnemiePos.y - EnemieHeight/2;
	EnemieRect.right = EnemieWidth + EnemieRect.left;
	EnemieRect.bottom = EnemieHeight + EnemieRect.top;
}
void EnemieFly::GetState(const BYTE& wl)
{
	Wall = wl;
}
void EnemieFly::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void EnemieFly::SetCharPoint(const Point& kpt)
{
	EnemiePos = kpt;
}
void EnemieFly::SetKirbyPoint(const Point&)
{
}