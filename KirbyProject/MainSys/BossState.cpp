#include "BossState.h"
#include "Boss.h"
#include "MissileManager.h"
#include "ItemManager.h"

/////////////////////////////////////////////////////////////
// 죽을떄 동작
/////////////////////////////////////////////////////////////
BossDead::BossDead()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), HitEnd(false)
{
}
BossDead::~BossDead()
{
}
void BossDead::Enter()
{
}
void BossDead::AniEnter(Animation* fr, Animation* bk)
{
}
void BossDead::Input(DWORD tick)
{
	
}
void BossDead::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("BossDead")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(!HitEnd)
	{
		SndDepot["HitEnd"]->Play();
		SndDepot["HitEnd"]->Play();
		SndDepot["HitEnd"]->Play();
		SndDepot["BossBattle"]->Stop();

		ItemDepot.DanceStarPush(Point(400,100));

		HitEnd = true;
	}

	if (pMachine)
		dynamic_cast<Boss*>(pMachine)->Setposition(PlayerPos, BossPos, BackPosition);

	AniDepot["BossEnd"]->SetRect(BossRect);
	AniDepot["BossEnd"]->Update(tick);
}
void BossDead::Draw(HDC hdc)
{
	AniDepot["BossEnd"]->Draw(hdc);
}
void BossDead::Leave()
{
}
void BossDead::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	BossPos = kpt;

	BackPosition = back;

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossWidth + BossRect.left;
	BossRect.bottom = BossHeight + BossRect.top;
}
void BossDead::GetState(const BYTE& wl)
{
	Wall = wl;
}
void BossDead::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void BossDead::SetCharPoint(const Point& kpt)
{
	BossPos = kpt;
}
void BossDead::SetKirbyPoint(const Point&)
{
}

/////////////////////////////////////////////////////////////
// 서있는 동작
/////////////////////////////////////////////////////////////
BossIdle::BossIdle()
: update_dt(0), MoveAcc(0), update_delay(100)
, Stand(false), Wall(0), TransCount(0), Phase(0)
{
}
BossIdle::~BossIdle()
{
}
void BossIdle::Enter()
{
	ImgDepot["BossIdle"]->SetRect(BossRect);
	ImgDepot["BossIdleBack"]->SetRect(BossRect);
}
void BossIdle::AniEnter(Animation* fr, Animation* bk)
{
}
void BossIdle::Input(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("BossIdle")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; i < count; i++)
		{
			TransCount++;
		}
		update_dt %= update_delay;
	}
	update_dt += tick;

	if(TransCount > 15 && Phase == 0)
	{
		Phase = 1;
		TransCount = 0;
		pMachine->transition(_T("Attack"));
	}
	else if(TransCount > 15 && Phase == 1)
	{
		Phase = 0;
		TransCount = 0;
		pMachine->transition(_T("Dance"));
	}
}
void BossIdle::Update(DWORD tick)
{
	if(!Stand)
	{
		BossPos.y += 1;
	}

	if (pMachine)
		dynamic_cast<Boss*>(pMachine)->Setposition(PlayerPos, BossPos, BackPosition);

	ImgDepot["BossIdle"]->SetRect(BossRect);
	ImgDepot["BossIdleBack"]->SetRect(BossRect);
	AniDepot["BossEye"]->Update(tick);
	AniDepot["BossEye"]->ResetAni(tick, 1000);
	AniDepot["BossEyeBack"]->Update(tick);
	AniDepot["BossEyeBack"]->ResetAni(tick, 1000);
}
void BossIdle::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		if(!AniDepot["BossEye"]->IsPlaying())
			ImgDepot["BossIdle"]->Draw(hdc);
		else
		{
			AniDepot["BossEye"]->SetRect(BossRect);
			AniDepot["BossEye"]->Draw(hdc);
		}
	}
	else
	{
		if(!AniDepot["BossEyeBack"]->IsPlaying())
			ImgDepot["BossIdleBack"]->Draw(hdc);
		else
		{
			AniDepot["BossEyeBack"]->SetRect(BossRect);
			AniDepot["BossEyeBack"]->Draw(hdc);
		}
	}
}
void BossIdle::Leave()
{
}
void BossIdle::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	BossPos = kpt;

	BackPosition = back;

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossWidth + BossRect.left;
	BossRect.bottom = BossHeight + BossRect.top;
}
void BossIdle::GetState(const BYTE& wl)
{
	Wall = wl;
}
void BossIdle::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void BossIdle::SetCharPoint(const Point& kpt)
{
	BossPos = kpt;
}
void BossIdle::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}
/////////////////////////////////////////////////////////////
// 공격하는 동작
/////////////////////////////////////////////////////////////
BossAttack::BossAttack()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), AttackCount(0)
{
}
BossAttack::~BossAttack()
{
}
void BossAttack::Enter()
{
}
void BossAttack::AniEnter(Animation* fr, Animation* bk)
{
}
void BossAttack::Input(DWORD tick)
{
	
}
void BossAttack::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("BossAtt")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; i < count; i++)
		{
			if(!BackPosition)
			{
				BossPos.x -= 5;
			}
			else
			{
				BossPos.x += 5;
			}
		}
		update_dt %= update_delay;
	}
	update_dt += tick;

	if(!BackPosition)
	{
		if(BossPos.x - 80 < 0)
		{
			SndDepot["HitEnd"]->Play();

			ItemDepot.NormalStarPush(BossPos, !BackPosition);
			BackPosition = !BackPosition;
			pMachine->transition(_T("Idle"));
		}
	}
	else
	{
		if(BossPos.x + 80 > GameGlobal.rcClient.right)
		{
			SndDepot["HitEnd"]->Play();

			ItemDepot.NormalStarPush(BossPos, !BackPosition);
			BackPosition = !BackPosition;
			pMachine->transition(_T("Idle"));
		}
	}

	if (pMachine)
		dynamic_cast<Boss*>(pMachine)->Setposition(PlayerPos, BossPos, BackPosition);

	AniDepot["BossAttackBack"]->SetRect(BossRect);
	AniDepot["BossAttack"]->SetRect(BossRect);
	AniDepot["BossAttack"]->Update(tick);
	AniDepot["BossAttackBack"]->Update(tick);
}
void BossAttack::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["BossAttack"]->Draw(hdc);
	}
	else
	{
		AniDepot["BossAttackBack"]->Draw(hdc);
	}
}
void BossAttack::Leave()
{
}
void BossAttack::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	BossPos = kpt;

	BackPosition = back;

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossWidth + BossRect.left;
	BossRect.bottom = BossHeight + BossRect.top;
}
void BossAttack::GetState(const BYTE& wl)
{
	Wall = wl;
}
void BossAttack::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void BossAttack::SetCharPoint(const Point& kpt)
{
	BossPos = kpt;
}
void BossAttack::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}
/////////////////////////////////////////////////////////////
// 분노한 공격하는 동작
/////////////////////////////////////////////////////////////
RageBossAttack::RageBossAttack()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), AttackCount(0)
{
}
RageBossAttack::~RageBossAttack()
{
}
void RageBossAttack::Enter()
{
}
void RageBossAttack::AniEnter(Animation* fr, Animation* bk)
{
}
void RageBossAttack::Input(DWORD tick)
{
	
}
void RageBossAttack::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("BossAtt")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; i < count; i++)
		{
			if(!BackPosition)
			{
				BossPos.x -= 5;
			}
			else
			{
				BossPos.x += 5;
			}
		}
		update_dt %= update_delay;
	}
	update_dt += tick;

	if(!BackPosition)
	{
		if(BossPos.x - 80 < 0)
		{
			SndDepot["HitEnd"]->Play();

			ItemDepot.NormalStarPush(BossPos, !BackPosition);
			BackPosition = !BackPosition;
			pMachine->transition(_T("Rage"));
		}
	}
	else
	{
		if(BossPos.x + 80 > GameGlobal.rcClient.right)
		{
			SndDepot["HitEnd"]->Play();

			ItemDepot.NormalStarPush(BossPos, !BackPosition);
			BackPosition = !BackPosition;
			pMachine->transition(_T("Rage"));
		}
	}

	if (pMachine)
		dynamic_cast<Boss*>(pMachine)->Setposition(PlayerPos, BossPos, BackPosition);

	AniDepot["BossAttackBack"]->SetRect(BossRect);
	AniDepot["BossAttack"]->SetRect(BossRect);
	AniDepot["BossAttack"]->Update(tick);
	AniDepot["BossAttackBack"]->Update(tick);
}
void RageBossAttack::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["BossAttack"]->Draw(hdc);
	}
	else
	{
		AniDepot["BossAttackBack"]->Draw(hdc);
	}
}
void RageBossAttack::Leave()
{
}
void RageBossAttack::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	BossPos = kpt;

	BackPosition = back;

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossWidth + BossRect.left;
	BossRect.bottom = BossHeight + BossRect.top;
}
void RageBossAttack::GetState(const BYTE& wl)
{
	Wall = wl;
}
void RageBossAttack::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void RageBossAttack::SetCharPoint(const Point& kpt)
{
	BossPos = kpt;
}
void RageBossAttack::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}
/////////////////////////////////////////////////////////////
// 분노하는 동작
/////////////////////////////////////////////////////////////
BossRage::BossRage()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), AttackCount(0)
, Phase(0)
{
}
BossRage::~BossRage()
{
}
void BossRage::Enter()
{
}
void BossRage::AniEnter(Animation* fr, Animation* bk)
{
}
void BossRage::Input(DWORD tick)
{	
}
void BossRage::Update(DWORD tick)
{
	tick = tick/2;

	std::wostringstream oss;
	oss << _T("BossRage")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if (pMachine)
		dynamic_cast<Boss*>(pMachine)->Setposition(PlayerPos, BossPos, BackPosition);

	AniDepot["BossRage"]->Update(tick);
	AniDepot["BossRageBack"]->Update(tick);

	if(!AniDepot["BossRage"]->IsPlaying() || !AniDepot["BossRageBack"]->IsPlaying())
	{
		AniDepot["BossRage"]->reset();
		AniDepot["BossRageBack"]->reset();

		if(Phase == 0)
		{
			Phase = 1;
			pMachine->transition(_T("RAttack"));
		}
		else if(Phase == 1)
		{
			Phase = 0;
			pMachine->transition(_T("RDance"));
		}
	}
}
void BossRage::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["BossRage"]->SetRect(BossRect);
		AniDepot["BossRage"]->Draw(hdc);
	}
	else
	{
		AniDepot["BossRageBack"]->SetRect(BossRect);
		AniDepot["BossRageBack"]->Draw(hdc);
	}
}
void BossRage::Leave()
{
}
void BossRage::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	BossPos = kpt;

	BackPosition = back;

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossWidth + BossRect.left;
	BossRect.bottom = BossHeight + BossRect.top;
}
void BossRage::GetState(const BYTE& wl)
{
	Wall = wl;
}
void BossRage::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void BossRage::SetCharPoint(const Point& kpt)
{
	BossPos = kpt;
}
void BossRage::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}
/////////////////////////////////////////////////////////////
// 춤추는 동작
/////////////////////////////////////////////////////////////
BossDance::BossDance()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), AttackCount(0)
, Setting(true)
{
}
BossDance::~BossDance()
{
}
void BossDance::Enter()
{
}
void BossDance::AniEnter(Animation* fr, Animation* bk)
{
}
void BossDance::Input(DWORD tick)
{	
}
void BossDance::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("BossDance")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(Setting)
	{
		MissileDepot.IceShotPush(Point(BossPos.x, BossPos.y + (BossHeight/2) - 5), BackPosition);
		Setting = false;
	}

	if (pMachine)
		dynamic_cast<Boss*>(pMachine)->Setposition(PlayerPos, BossPos, BackPosition);

	AniDepot["BossDance"]->Update(tick);
	AniDepot["BossDanceBack"]->Update(tick);

	if(!AniDepot["BossDance"]->IsPlaying() || !AniDepot["BossDanceBack"]->IsPlaying())
	{
		Setting = true;
		AniDepot["BossDance"]->reset();
		AniDepot["BossDanceBack"]->reset();
		pMachine->transition(_T("Shot"));
	}
}
void BossDance::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["BossDance"]->SetRect(BossRect);
		AniDepot["BossDance"]->Draw(hdc);
	}
	else
	{
		AniDepot["BossDanceBack"]->SetRect(BossRect);
		AniDepot["BossDanceBack"]->Draw(hdc);
	}
}
void BossDance::Leave()
{
}
void BossDance::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	BossPos = kpt;

	BackPosition = back;

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossWidth + BossRect.left;
	BossRect.bottom = BossHeight + BossRect.top;
}
void BossDance::GetState(const BYTE& wl)
{
	Wall = wl;
}
void BossDance::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void BossDance::SetCharPoint(const Point& kpt)
{
	BossPos = kpt;
}
void BossDance::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}
/////////////////////////////////////////////////////////////
// 분노한 춤추는 동작
/////////////////////////////////////////////////////////////
RageBossDance::RageBossDance()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), AttackCount(0)
, Setting(true)
{
}
RageBossDance::~RageBossDance()
{
}
void RageBossDance::Enter()
{
}
void RageBossDance::AniEnter(Animation* fr, Animation* bk)
{
}
void RageBossDance::Input(DWORD tick)
{	
}
void RageBossDance::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("BossDance")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(Setting)
	{
		MissileDepot.RageIceShotPush(Point(BossPos.x, BossPos.y + (BossHeight/2) - 5), BackPosition);
		Setting = false;
	}

	if (pMachine)
		dynamic_cast<Boss*>(pMachine)->Setposition(PlayerPos, BossPos, BackPosition);

	AniDepot["BossDance"]->Update(tick);
	AniDepot["BossDanceBack"]->Update(tick);

	if(!AniDepot["BossDance"]->IsPlaying() || !AniDepot["BossDanceBack"]->IsPlaying())
	{
		Setting = true;
		AniDepot["BossDance"]->reset();
		AniDepot["BossDanceBack"]->reset();
		pMachine->transition(_T("RShot"));
	}
}
void RageBossDance::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["BossDance"]->SetRect(BossRect);
		AniDepot["BossDance"]->Draw(hdc);
	}
	else
	{
		AniDepot["BossDanceBack"]->SetRect(BossRect);
		AniDepot["BossDanceBack"]->Draw(hdc);
	}
}
void RageBossDance::Leave()
{
}
void RageBossDance::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	BossPos = kpt;

	BackPosition = back;

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossWidth + BossRect.left;
	BossRect.bottom = BossHeight + BossRect.top;
}
void RageBossDance::GetState(const BYTE& wl)
{
	Wall = wl;
}
void RageBossDance::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void RageBossDance::SetCharPoint(const Point& kpt)
{
	BossPos = kpt;
}
void RageBossDance::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}
/////////////////////////////////////////////////////////////
// 발사하는 동작
/////////////////////////////////////////////////////////////
BossShot::BossShot()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), AttackCount(0)
{
}
BossShot::~BossShot()
{
}
void BossShot::Enter()
{
}
void BossShot::AniEnter(Animation* fr, Animation* bk)
{
}
void BossShot::Input(DWORD tick)
{	
}
void BossShot::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("BossShot")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if (pMachine)
		dynamic_cast<Boss*>(pMachine)->Setposition(PlayerPos, BossPos, BackPosition);

	AniDepot["BossShot"]->Update(tick);
	AniDepot["BossShotBack"]->Update(tick);

	if(!AniDepot["BossShot"]->IsPlaying() || !AniDepot["BossShotBack"]->IsPlaying())
	{
		AniDepot["BossShot"]->reset();
		AniDepot["BossShotBack"]->reset();

		pMachine->transition(_T("Idle"));
	}
}
void BossShot::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["BossShot"]->SetRect(BossRect);
		AniDepot["BossShot"]->Draw(hdc);
	}
	else
	{
		AniDepot["BossShotBack"]->SetRect(BossRect);
		AniDepot["BossShotBack"]->Draw(hdc);
	}
}
void BossShot::Leave()
{
}
void BossShot::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	BossPos = kpt;

	BackPosition = back;

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossWidth + BossRect.left;
	BossRect.bottom = BossHeight + BossRect.top;
}
void BossShot::GetState(const BYTE& wl)
{
	Wall = wl;
}
void BossShot::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void BossShot::SetCharPoint(const Point& kpt)
{
	BossPos = kpt;
}
void BossShot::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}
/////////////////////////////////////////////////////////////
// 분노한 발사하는 동작
/////////////////////////////////////////////////////////////
RageBossShot::RageBossShot()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), AttackCount(0)
{
}
RageBossShot::~RageBossShot()
{
}
void RageBossShot::Enter()
{
}
void RageBossShot::AniEnter(Animation* fr, Animation* bk)
{
}
void RageBossShot::Input(DWORD tick)
{	
}
void RageBossShot::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("RageBossShot")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if (pMachine)
		dynamic_cast<Boss*>(pMachine)->Setposition(PlayerPos, BossPos, BackPosition);

	AniDepot["BossShot"]->Update(tick);
	AniDepot["BossShotBack"]->Update(tick);

	if(!AniDepot["BossShot"]->IsPlaying() || !AniDepot["BossShotBack"]->IsPlaying())
	{
		AniDepot["BossShot"]->reset();
		AniDepot["BossShotBack"]->reset();

		pMachine->transition(_T("Rage"));
	}
}
void RageBossShot::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["BossShot"]->SetRect(BossRect);
		AniDepot["BossShot"]->Draw(hdc);
	}
	else
	{
		AniDepot["BossShotBack"]->SetRect(BossRect);
		AniDepot["BossShotBack"]->Draw(hdc);
	}
}
void RageBossShot::Leave()
{
}
void RageBossShot::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	BossPos = kpt;

	BackPosition = back;

	BossRect.left = BossPos.x - BossWidth/2;
	BossRect.top = BossPos.y - BossHeight/2;
	BossRect.right = BossWidth + BossRect.left;
	BossRect.bottom = BossHeight + BossRect.top;
}
void RageBossShot::GetState(const BYTE& wl)
{
	Wall = wl;
}
void RageBossShot::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
}
void RageBossShot::SetCharPoint(const Point& kpt)
{
	BossPos = kpt;
}
void RageBossShot::SetKirbyPoint(const Point& pt)
{
	KirbyPos = pt;
}