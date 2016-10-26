#include "KirbyState.h"

/////////////////////////////////////////////////////////////
// 대기 동작
/////////////////////////////////////////////////////////////
KirbyIdle::KirbyIdle()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyIdle::~KirbyIdle()
{
}
void KirbyIdle::Enter()
{
	srand((unsigned)time(NULL));

	ImgDepot["KirbyStd"]->SetRect(KirbyRect);
	ImgDepot["KirbyStdBack"]->SetRect(KirbyRect);
	AniDepot["KirbyStdEye"]->SetRect(KirbyRect);
	AniDepot["KirbyStdEyeBack"]->SetRect(KirbyRect);
}
void KirbyIdle::Input(DWORD tick)
{
	if(InputDevice[VK_RIGHT] && !(Wall == 2))
	{
		BackPosition = false;
		pMachine->transition(_T("Move"));
	}
	else if(InputDevice[VK_LEFT] && !(Wall == 1))
	{
		BackPosition = true;
		pMachine->transition(_T("Move"));
	}
	if(InputDevice.OnClick('C'))
	{
		pMachine->transition(_T("Jump"));
	}
	if(InputDevice['X'])
	{
		pMachine->transition(_T("Drain"));
	}
}
void KirbyIdle::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("IdleState")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!Stand)
	{
		pMachine->transition(_T("Landing"));
	}

	ImgDepot["KirbyStd"]->SetRect(KirbyRect);
	AniDepot["KirbyStdEye"]->SetRect(KirbyRect);
	ImgDepot["KirbyStdBack"]->SetRect(KirbyRect);
	AniDepot["KirbyStdEyeBack"]->SetRect(KirbyRect);

	AniDepot["KirbyStdEye"]->Update(tick);
	AniDepot["KirbyStdEye"]->ResetAni(tick, rand()%5000 + 1000);
	AniDepot["KirbyStdEyeBack"]->Update(tick);
	AniDepot["KirbyStdEyeBack"]->ResetAni(tick, rand()%5000 + 1000);
}
void KirbyIdle::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		if(!(AniDepot["KirbyStdEye"]->IsPlaying()))
			ImgDepot["KirbyStd"]->Draw(hdc);
		else
			AniDepot["KirbyStdEye"]->Draw(hdc);
	}
	else
	{
		if(!(AniDepot["KirbyStdEyeBack"]->IsPlaying()))
			ImgDepot["KirbyStdBack"]->Draw(hdc);
		else
			AniDepot["KirbyStdEyeBack"]->Draw(hdc);
	}
}
void KirbyIdle::Leave()
{
}
void KirbyIdle::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyIdle::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyIdle::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyIdle::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyIdle::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyIdle::GetRect()
{
	return Rect(2000,0,0,0);
}

/////////////////////////////////////////////////////////////
// 뚱뚱한 대기 동작
/////////////////////////////////////////////////////////////
KirbyFatIdle::KirbyFatIdle()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyFatIdle::~KirbyFatIdle()
{
}
void KirbyFatIdle::Enter()
{
	srand((unsigned)time(NULL));

	ImgDepot["KirbyFatStd"]->SetRect(KirbyRect);
	ImgDepot["KirbyFatStdBack"]->SetRect(KirbyRect);
	AniDepot["KirbyFatStdEye"]->SetRect(KirbyRect);
	AniDepot["KirbyFatStdEyeBack"]->SetRect(KirbyRect);
}
void KirbyFatIdle::Input(DWORD tick)
{
	if(InputDevice[VK_RIGHT] && !(Wall == 2))
	{
		BackPosition = false;
		pMachine->transition(_T("MoveFat"));
	}
	else if(InputDevice[VK_LEFT] && !(Wall == 1))
	{
		BackPosition = true;
		pMachine->transition(_T("MoveFat"));
	}
	else if(InputDevice[VK_DOWN])
	{
		pMachine->transition(_T("Eat"));
	}
	if(InputDevice.OnClick('C'))
	{
		pMachine->transition(_T("JumpFat"));
	}
	if(update_shot > 500)
	{
		if(InputDevice.OnClick('X'))
		{
			update_shot = 0;
			pMachine->transition(_T("Shot"));
		}
	}
	update_shot += tick;
}
void KirbyFatIdle::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("IdleState")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!Stand)
	{
		pMachine->transition(_T("LandingFat"));
	}

	ImgDepot["KirbyFatStd"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top-9, KirbyRect.right+10, KirbyRect.bottom));
	AniDepot["KirbyFatStdEye"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top-9, KirbyRect.right+10, KirbyRect.bottom));
	ImgDepot["KirbyFatStdBack"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-9, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyFatStdEyeBack"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-9, KirbyRect.right+5, KirbyRect.bottom));

	AniDepot["KirbyFatStdEye"]->Update(tick);
	AniDepot["KirbyFatStdEye"]->ResetAni(tick, rand()%5000 + 1000);
	AniDepot["KirbyFatStdEyeBack"]->Update(tick);
	AniDepot["KirbyFatStdEyeBack"]->ResetAni(tick, rand()%5000 + 1000);
}
void KirbyFatIdle::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		if(!(AniDepot["KirbyFatStdEye"]->IsPlaying()))
			ImgDepot["KirbyFatStd"]->Draw(hdc);
		else
			AniDepot["KirbyFatStdEye"]->Draw(hdc);
	}
	else
	{
		if(!(AniDepot["KirbyFatStdEyeBack"]->IsPlaying()))
			ImgDepot["KirbyFatStdBack"]->Draw(hdc);
		else
			AniDepot["KirbyFatStdEyeBack"]->Draw(hdc);
	}
}
void KirbyFatIdle::Leave()
{
}
void KirbyFatIdle::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyFatIdle::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyFatIdle::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyFatIdle::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyFatIdle::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyFatIdle::GetRect()
{
	return Rect(100,0,0,0);
}

/////////////////////////////////////////////////////////////
// 걷기 동작
/////////////////////////////////////////////////////////////
KirbyMove::KirbyMove()
: update_dt(0), MoveAcc(0), update_delay(20)
, KeyPush(true), update_dt2(0), update_delay2(60)
, RightKey(false), Stand(false), Wall(0)
, MapEnd(false), Boss(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyMove::~KirbyMove()
{
}
void KirbyMove::Enter()
{
	AniDepot["KirbyMove"]->SetRect(KirbyRect);
	AniDepot["KirbyMoveBack"]->SetRect(KirbyRect);
}
void KirbyMove::Input(DWORD tick)
{	
	if(MoveAcc > 0 && !KeyPush)
	{
		if (InputDevice[VK_RIGHT] && RightKey)
		{
			BackPosition = false;
			pMachine->transition(_T("Run"));			
		}
		else if (InputDevice[VK_LEFT] && !RightKey)
		{
			BackPosition = true;
			pMachine->transition(_T("Run"));
		}		
	}

	if (InputDevice[VK_RIGHT])
	{
		BackPosition = false;
		if(Wall == 2)
			pMachine->transition(_T("Idle"));
		KeyPush = true;
		RightKey = true;
	}
	else if (InputDevice[VK_LEFT])
	{
		BackPosition = true;
		if(Wall == 1)
			pMachine->transition(_T("Idle"));
		KeyPush = true;
		RightKey = false;
	}
	else
	{
		KeyPush = false;
	}
	if(InputDevice.OnClick('C'))
	{
		pMachine->transition(_T("Jump"));
	}

	if(!KeyPush && MoveAcc == 0)
	{
		pMachine->transition(_T("Idle"));
	}
	if(InputDevice['X'])
	{
		pMachine->transition(_T("Drain"));
	}
}
void KirbyMove::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("MoveState")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	// 이동좌표 업데이트
	if(KeyPush)
	{
		update_dt2 = 0;
		if(update_dt > update_delay)
		{
			int count = update_dt / update_delay;
			for(int i = 0; i < count; i++)
			{
				Rect tmp;
				if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect) && !Boss)
				{
					MoveAcc += 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(PlayerPos.x < 390)
						PlayerPos.x = 390;
					if(Wall == 2)
						pMachine->transition(_T("Idle"));
					else
						PlayerPos.x += MoveAcc;
				}
				else if(!Boss && BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
				{
					MoveAcc += 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(Wall == 1)
						pMachine->transition(_T("Idle"));
					else
						PlayerPos.x -= MoveAcc;

					if(PlayerPos.x < 0)
						PlayerPos.x = 0;
				}
				else if(!BackPosition)
				{
					MoveAcc += 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(Wall == 2)
						pMachine->transition(_T("Idle"));
					else
						KirbyPos.x += MoveAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
				}
				else if(BackPosition)
				{
					MoveAcc += 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(Wall == 1)
						pMachine->transition(_T("Idle"));
					else
						KirbyPos.x -= MoveAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
				}
			}
			update_dt = update_dt % update_delay;
		}
		update_dt += tick;
	}
	else if(MoveAcc > 0)
	{
		update_dt = 0;
		if(update_dt2 > update_delay2)
		{
			int count = update_dt2 / update_delay2;
			for(int i = 0; i < count; i++)
			{
				Rect tmp;
				if(!(::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect)))
				{
					if(BackPosition)
					{
						MoveAcc -= 1;
						if(Wall == 1)
							pMachine->transition(_T("Idle"));
						else
							KirbyPos.x -= MoveAcc;
						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
					else
					{
						MoveAcc -= 1;
						if(Wall == 2)
							pMachine->transition(_T("Idle"));
						else
							KirbyPos.x += MoveAcc;
					}
				}
				else
				{
					if(BackPosition && !Boss)
					{
						MoveAcc -= 1;
						if(Wall == 1)
							pMachine->transition(_T("Idle"));
						else
							PlayerPos.x -= MoveAcc;
						if(PlayerPos.x < 0)
							PlayerPos.x = 0;
					}
					else if(!Boss)
					{
						MoveAcc -= 1;
						if(Wall == 2)
							pMachine->transition(_T("Idle"));
						else
							PlayerPos.x += MoveAcc;
					}
				}
			}
			update_dt2 = update_dt2 % update_delay2;
		}
		update_dt2 += tick;
	}

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!Stand)
	{
		pMachine->transition(_T("Landing"));
	}

	// 애니메이션 업데이트
	AniDepot["KirbyMove"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyMoveBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));
	AniDepot["KirbyMove"]->Update(tick);
	AniDepot["KirbyMoveBack"]->Update(tick);
}
void KirbyMove::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["KirbyMove"]->Draw(hdc);
	}
	else
	{
		AniDepot["KirbyMoveBack"]->Draw(hdc);
	}
}
void KirbyMove::Leave()
{
}
void KirbyMove::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyMove::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyMove::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyMove::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyMove::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyMove::GetRect()
{
	return Rect(2000,0,0,0);
}
void KirbyMove::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}

/////////////////////////////////////////////////////////////
// 뚱뚱한 걷는 동작
/////////////////////////////////////////////////////////////
KirbyFatMove::KirbyFatMove()
: update_dt(0), MoveAcc(0), update_delay(20), update_shot(0)
, KeyPush(true), update_dt2(0), update_delay2(60)
, RightKey(false), Stand(false), Wall(0), Boss(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyFatMove::~KirbyFatMove()
{
}
void KirbyFatMove::Enter()
{
	AniDepot["KirbyFatMove"]->SetRect(KirbyRect);
	AniDepot["KirbyFatMoveBack"]->SetRect(KirbyRect);
}
void KirbyFatMove::Input(DWORD tick)
{	
	if(MoveAcc > 0 && !KeyPush)
	{
		if (InputDevice[VK_RIGHT] && RightKey)
		{
			BackPosition = false;
			pMachine->transition(_T("RunFat"));			
		}
		else if (InputDevice[VK_LEFT] && !RightKey)
		{
			BackPosition = true;
			pMachine->transition(_T("RunFat"));
		}		
	}

	if (InputDevice[VK_RIGHT])
	{
		BackPosition = false;
		if(Wall == 2)
			pMachine->transition(_T("IdleFat"));
		KeyPush = true;
		RightKey = true;
	}
	else if (InputDevice[VK_LEFT])
	{
		BackPosition = true;
		if(Wall == 1)
			pMachine->transition(_T("IdleFat"));
		KeyPush = true;
		RightKey = false;
	}
	else if(InputDevice[VK_DOWN])
	{
		pMachine->transition(_T("Eat"));
	}
	else
	{
		KeyPush = false;
	}
	if(InputDevice.OnClick('C'))
	{
		pMachine->transition(_T("JumpFat"));
	}

	if(!KeyPush && MoveAcc == 0)
	{
		pMachine->transition(_T("IdleFat"));
	}
	if(update_shot > 500)
	{
		if(InputDevice.OnClick('X'))
		{
			update_shot = 0;
			pMachine->transition(_T("Shot"));
		}
	}
	update_shot += tick;
}
void KirbyFatMove::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("MoveState")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	// 이동좌표 업데이트
	if(KeyPush)
	{
		update_dt2 = 0;
		if(update_dt > update_delay)
		{
			int count = update_dt / update_delay;
			for(int i = 0; i < count; i++)
			{
				Rect tmp;
				if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect) && !Boss)
				{
					MoveAcc += 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(PlayerPos.x < 390)
						PlayerPos.x = 390;
					if(Wall == 2)
						pMachine->transition(_T("IdleFat"));
					else
						PlayerPos.x += MoveAcc;
				}
				else if(!Boss && BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
				{
					MoveAcc += 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(Wall == 1)
						pMachine->transition(_T("IdleFat"));
					else
						PlayerPos.x -= MoveAcc;

					if(PlayerPos.x < 0)
						PlayerPos.x = 0;
				}
				else if(!BackPosition)
				{
					MoveAcc += 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(Wall == 2)
						pMachine->transition(_T("IdleFat"));
					else
						KirbyPos.x += MoveAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
				}
				else if(BackPosition)
				{
					MoveAcc += 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(Wall == 1)
						pMachine->transition(_T("IdleFat"));
					else
						KirbyPos.x -= MoveAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
				}
			}
			update_dt = update_dt % update_delay;
		}
		update_dt += tick;
	}
	else if(MoveAcc > 0)
	{
		update_dt = 0;
		if(update_dt2 > update_delay2)
		{
			int count = update_dt2 / update_delay2;
			for(int i = 0; i < count; i++)
			{
				Rect tmp;
				if(!(::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect)))
				{
					if(BackPosition)
					{
						MoveAcc -= 1;
						if(Wall == 1)
							pMachine->transition(_T("IdleFat"));
						else
							KirbyPos.x -= MoveAcc;
						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
					else
					{
						MoveAcc -= 1;
						if(Wall == 2)
							pMachine->transition(_T("IdleFat"));
						else
							KirbyPos.x += MoveAcc;
					}
				}
				else
				{
					if(BackPosition && !Boss)
					{
						MoveAcc -= 1;
						if(Wall == 1)
							pMachine->transition(_T("IdleFat"));
						else
							PlayerPos.x -= MoveAcc;
						if(PlayerPos.x < 0)
							PlayerPos.x = 0;
					}
					else if(!Boss)
					{
						MoveAcc -= 1;
						if(Wall == 2)
							pMachine->transition(_T("IdleFat"));
						else
							PlayerPos.x += MoveAcc;
					}
				}
			}
			update_dt2 = update_dt2 % update_delay2;
		}
		update_dt2 += tick;
	}
	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!Stand)
	{
		pMachine->transition(_T("LandingFat"));
	}

	// 애니메이션 업데이트
	AniDepot["KirbyFatMove"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top-14, KirbyRect.right+10, KirbyRect.bottom));
	AniDepot["KirbyFatMoveBack"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-14, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyFatMove"]->Update(tick);
	AniDepot["KirbyFatMoveBack"]->Update(tick);
}
void KirbyFatMove::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["KirbyFatMove"]->Draw(hdc);
	}
	else
	{
		AniDepot["KirbyFatMoveBack"]->Draw(hdc);
	}
}
void KirbyFatMove::Leave()
{
}
void KirbyFatMove::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyFatMove::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyFatMove::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyFatMove::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyFatMove::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyFatMove::GetRect()
{
	return Rect(100,0,0,0);
}
void KirbyFatMove::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}


/////////////////////////////////////////////////////////////
// 달리는 동작
/////////////////////////////////////////////////////////////
KirbyRun::KirbyRun()
: Break(false), update_dt(0), update_delay(20), MoveAcc(4)
, KeyPush(true), update_dt2(0), update_delay2(60), Stand(false), Wall(0)
, Run(false), Boss(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyRun::~KirbyRun()
{
}
void KirbyRun::Enter()
{
	ImgDepot["KirbyBreak"]->SetRect(KirbyRect);
	ImgDepot["KirbyBreakBack"]->SetRect(KirbyRect);
	AniDepot["KirbyRun"]->SetRect(KirbyRect);
	AniDepot["KirbyRunBack"]->SetRect(KirbyRect);
}
void KirbyRun::Input(DWORD)
{
	if (InputDevice[VK_RIGHT])
	{
		if(BackPosition && MoveAcc >= 5)
		{
			MoveAcc = -MoveAcc - 3;
			Break = true;
		}

		BackPosition = false;
		KeyPush = true;
	}
	else if (InputDevice[VK_LEFT])
	{
		if(!BackPosition && MoveAcc >= 5)
		{
			MoveAcc = -MoveAcc - 3;
			Break = true;
		}

		BackPosition = true;
		KeyPush = true;
	}
	else
	{
		KeyPush = false;
	}
	if(InputDevice.OnClick('C'))
	{
		Run = false;
		Break = false;
		MoveAcc = 4;
		pMachine->transition(_T("Jump"));
	}

	if(!KeyPush && MoveAcc == 0)
	{
		Run = false;
		Break = false;
		MoveAcc = 4;
		pMachine->transition(_T("Idle"));
	}
	if(InputDevice['X'])
	{
		Run = false;
		Break = false;
		MoveAcc = 4;
		pMachine->transition(_T("Drain"));
	}
}
void KirbyRun::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("RunState")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	if(!Run && !SndDepot["Run"]->IsPlaying() )
	{
		SndDepot["Run"]->Play();
		Run = true;
	}

	// 캐릭터 좌표 업데이트
	if(KeyPush)
	{
		update_dt2 = 0;
		if(update_dt > update_delay)
		{
			int count = update_dt / update_delay;
			for(int i = 0; i < count; i++)
			{
				if(!Break)
				{
					if(MoveAcc >= 0 && MoveAcc < 3)
					{
						Run = false;
						Break = false;
						MoveAcc = 4;
						pMachine->transition(_T("Idle"));
					}
					Rect tmp;
					if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(PlayerPos.x < 375)
							PlayerPos.x = 375;

						if(Wall == 2)
						{
							Run = false;
							Break = false;
							MoveAcc = 4;
							pMachine->transition(_T("Idle"));
						}
						else
							PlayerPos.x += MoveAcc;
					}
					else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 1)
						{
							Run = false;
							Break = false;
							MoveAcc = 4;
							pMachine->transition(_T("Idle"));
						}
						else
							PlayerPos.x -= MoveAcc;

						if(PlayerPos.x < 0)
							PlayerPos.x = 0;
					}
					else if(!BackPosition)
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 2)
						{
							Run = false;
							Break = false;
							MoveAcc = 4;
							pMachine->transition(_T("Idle"));
						}
						else
							KirbyPos.x += MoveAcc;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
					else if(BackPosition)
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 1)
						{
							Run = false;
							Break = false;
							MoveAcc = 4;
							pMachine->transition(_T("Idle"));
						}
						else
							KirbyPos.x -= MoveAcc;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
				}
				else
				{
					if(MoveAcc >= 0 && MoveAcc < 3)
					{
						Run = false;
						Break = false;
						MoveAcc = 4;
						pMachine->transition(_T("Idle"));
					}
					Rect tmp;
					if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(PlayerPos.x < 375)
							PlayerPos.x = 375;

						if(Wall == 1)
						{
							Run = false;
							Break = false;
							MoveAcc = 4;
							pMachine->transition(_T("Idle"));
						}
						else
							PlayerPos.x += MoveAcc;
					}
					else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 2)
						{
							Run = false;
							Break = false;
							MoveAcc = 4;
							pMachine->transition(_T("Idle"));
						}
						else
							PlayerPos.x -= MoveAcc;

						if(PlayerPos.x < 0)
							PlayerPos.x = 0;
					}
					else if(!BackPosition)
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 1)
						{
							Run = false;
							Break = false;
							MoveAcc = 4;
							pMachine->transition(_T("Idle"));
						}
						else
							KirbyPos.x += MoveAcc;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
					else if(BackPosition)
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 2)
						{
							Run = false;
							Break = false;
							MoveAcc = 4;
							pMachine->transition(_T("Idle"));
						}
						else
							KirbyPos.x -= MoveAcc;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
				}
			}
			update_dt = update_dt % update_delay;
		}
		update_dt += tick;
	}
	else if(MoveAcc > 0 || Break)
	{
		update_dt = 0;
		if(update_dt2 > update_delay2)
		{
			int count = update_dt2 / update_delay2;
			for(int i = 0; i < count; i++)
			{
				if(MoveAcc >= 0 && MoveAcc < 3)
				{
					Run = false;
					Break = false;
					MoveAcc = 4;
					pMachine->transition(_T("Idle"));
				}

				if(MoveAcc > 0)
				{
					Rect tmp;
					if(!(::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect)))
					{
						if(BackPosition)
						{
							MoveAcc -= 1;

							if(Wall == 1)
							{
								Run = false;
								Break = false;
								MoveAcc = 4;
								pMachine->transition(_T("Idle"));
							}
							else
								KirbyPos.x -= MoveAcc;
							if(KirbyPos.x - KirbyWidth/2 < 0)
								KirbyPos.x = KirbyWidth/2;
						}
						else
						{
							MoveAcc -= 1;

							if(Wall == 2)
							{
								Run = false;
								Break = false;
								MoveAcc = 4;
								pMachine->transition(_T("Idle"));
							}
							else
								KirbyPos.x += MoveAcc;
						}
					}
					else
					{
						if(BackPosition)
						{
							MoveAcc -= 1;

							if(Wall == 1)
							{
								Run = false;
								Break = false;
								MoveAcc = 4;
								pMachine->transition(_T("Idle"));
							}
							else
								PlayerPos.x -= MoveAcc;
							if(PlayerPos.x < 0)
								PlayerPos.x = 0;
						}
						else
						{
							MoveAcc -= 1;

							if(Wall == 2)
							{
								Run = false;
								Break = false;
								MoveAcc = 4;
								pMachine->transition(_T("Idle"));
							}
							else
								PlayerPos.x += MoveAcc;
						}
					}
				}
				else if(Break)
				{
					Rect tmp;
					if(!(::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect)))
					{
						if(BackPosition)
						{
							MoveAcc += 1;

							if(Wall == 2)
							{
								Run = false;
								Break = false;
								MoveAcc = 4;
								pMachine->transition(_T("Idle"));
							}
							else
								KirbyPos.x -= MoveAcc;
							if(KirbyPos.x - KirbyWidth/2 < 0)
								KirbyPos.x = KirbyWidth/2;
						}
						else
						{
							MoveAcc += 1;

							if(Wall == 1)
							{
								Run = false;
								Break = false;
								MoveAcc = 4;
								pMachine->transition(_T("Idle"));
							}
							else
								KirbyPos.x += MoveAcc;
							if(KirbyPos.x - KirbyWidth/2 < 0)
								KirbyPos.x = KirbyWidth/2;
						}
					}
					else
					{
						if(BackPosition)
						{
							MoveAcc += 1;

							if(Wall == 2)
							{
								Run = false;
								Break = false;
								MoveAcc = 4;
								pMachine->transition(_T("Idle"));
							}
							else
								PlayerPos.x -= MoveAcc;
							if(PlayerPos.x < 0)
								PlayerPos.x = 0;
						}
						else
						{
							MoveAcc += 1;

							if(Wall == 1)
							{
								Run = false;
								Break = false;
								MoveAcc = 4;
								pMachine->transition(_T("Idle"));
							}
							else
								PlayerPos.x += MoveAcc;
							if(PlayerPos.x < 375)
								PlayerPos.x = 375;
						}
					}
				}
			}
			update_dt2 = update_dt2 % update_delay2;
		}
		update_dt2 += tick;
	}

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!Stand)
	{
		Run = false;
		Break = false;
		MoveAcc = 4;
		pMachine->transition(_T("Landing"));
	}

	// 애니메이션 업데이트
	ImgDepot["KirbyBreak"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyRun"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));

	ImgDepot["KirbyBreakBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));
	AniDepot["KirbyRunBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));

	AniDepot["KirbyRun"]->Update(tick);

	AniDepot["KirbyRunBack"]->Update(tick);
}
void KirbyRun::Draw(HDC hdc)
{
	if(!Break)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyRun"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyRunBack"]->Draw(hdc);
		}
	}
	else
	{
		if(BackPosition)
		{
			ImgDepot["KirbyBreak"]->Draw(hdc);
		}
		else
		{
			ImgDepot["KirbyBreakBack"]->Draw(hdc);
		}
	}
}
void KirbyRun::Leave()
{
}
void KirbyRun::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyRun::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyRun::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyRun::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyRun::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyRun::GetRect()
{
	return Rect(2000,0,0,0);
}
void KirbyRun::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}

/////////////////////////////////////////////////////////////
// 뚱뚱한 달리는 동작
/////////////////////////////////////////////////////////////
KirbyFatRun::KirbyFatRun()
: Break(false), update_dt(0), update_delay(20), MoveAcc(4), update_shot(0)
, KeyPush(true), update_dt2(0), update_delay2(60), Stand(false), Wall(0)
, Run(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyFatRun::~KirbyFatRun()
{
}
void KirbyFatRun::Enter()
{
	ImgDepot["KirbyFatBreak"]->SetRect(KirbyRect);
	ImgDepot["KirbyFatBreakBack"]->SetRect(KirbyRect);
	AniDepot["KirbyFatRun"]->SetRect(KirbyRect);
	AniDepot["KirbyFatRunBack"]->SetRect(KirbyRect);
}
void KirbyFatRun::Input(DWORD tick)
{
	if (InputDevice[VK_RIGHT])
	{
		if(BackPosition && MoveAcc >= 5)
		{
			MoveAcc = -MoveAcc - 3;
			Break = true;
		}

		BackPosition = false;
		KeyPush = true;
	}
	else if (InputDevice[VK_LEFT])
	{
		if(!BackPosition && MoveAcc >= 5)
		{
			MoveAcc = -MoveAcc - 3;
			Break = true;
		}

		BackPosition = true;
		KeyPush = true;
	}
	else if(InputDevice[VK_DOWN])
	{
		pMachine->transition(_T("Eat"));
	}
	else
	{
		KeyPush = false;
	}
	if(InputDevice.OnClick('C'))
	{
		Break = false;
		MoveAcc = 4;
		Run = false;
		pMachine->transition(_T("JumpFat"));
	}

	if(!KeyPush && MoveAcc == 0)
	{
		Run = false;
		Break = false;
		MoveAcc = 4;
		pMachine->transition(_T("IdleFat"));
	}
	if(update_shot > 500)
	{
		if(InputDevice.OnClick('X'))
		{
			Break = false;
			MoveAcc = 4;
			Run = false;
			update_shot = 0;
			pMachine->transition(_T("Shot"));
		}
	}
	update_shot += tick;
}
void KirbyFatRun::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("RunState")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	if(!Run && !SndDepot["Run"]->IsPlaying())
	{
		SndDepot["Run"]->Play();
		Run = true;
	}

	// 캐릭터 좌표 업데이트
	if(KeyPush)
	{
		update_dt2 = 0;
		if(update_dt > update_delay)
		{
			int count = update_dt / update_delay;
			for(int i = 0; i < count; i++)
			{
				if(!Break)
				{
					if(MoveAcc >= 0 && MoveAcc < 3)
					{
						Break = false;
						MoveAcc = 4;
						Run = false;
						pMachine->transition(_T("IdleFat"));
					}
					Rect tmp;
					if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(PlayerPos.x < 375)
							PlayerPos.x = 375;

						if(Wall == 2)
						{
							Break = false;
							MoveAcc = 4;
							Run = false;
							pMachine->transition(_T("IdleFat"));
						}
						else
							PlayerPos.x += MoveAcc;
					}
					else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 1)
						{
							Break = false;
							MoveAcc = 4;
							Run = false;
							pMachine->transition(_T("IdleFat"));
						}
						else
							PlayerPos.x -= MoveAcc;

						if(PlayerPos.x < 0)
							PlayerPos.x = 0;
					}
					else if(!BackPosition)
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 2)
						{
							Break = false;
							MoveAcc = 4;
							Run = false;
							pMachine->transition(_T("IdleFat"));
						}
						else
							KirbyPos.x += MoveAcc;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
					else if(BackPosition)
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 1)
						{
							Break = false;
							MoveAcc = 4;
							Run = false;
							pMachine->transition(_T("IdleFat"));
						}
						else
							KirbyPos.x -= MoveAcc;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
				}
				else
				{
					if(MoveAcc >= 0 && MoveAcc < 3)
					{
						Run = false;
						Break = false;
						MoveAcc = 4;
						pMachine->transition(_T("IdleFat"));
					}
					Rect tmp;
					if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(PlayerPos.x < 375)
							PlayerPos.x = 375;

						if(Wall == 1)
						{
							Break = false;
							MoveAcc = 4;
							Run = false;
							pMachine->transition(_T("IdleFat"));
						}
						else
							PlayerPos.x += MoveAcc;
					}
					else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 2)
						{
							Break = false;
							MoveAcc = 4;
							Run = false;
							pMachine->transition(_T("IdleFat"));
						}
						else
							PlayerPos.x -= MoveAcc;

						if(PlayerPos.x < 0)
							PlayerPos.x = 0;
					}
					else if(!BackPosition)
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 1)
						{
							Break = false;
							MoveAcc = 4;
							Run = false;
							pMachine->transition(_T("IdleFat"));
						}
						else
							KirbyPos.x += MoveAcc;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
					else if(BackPosition)
					{
						MoveAcc += 2;

						if(MoveAcc >= 8)
							MoveAcc = 8;

						if(Wall == 2)
						{
							Break = false;
							MoveAcc = 4;
							Run = false;
							pMachine->transition(_T("IdleFat"));
						}
						else
							KirbyPos.x -= MoveAcc;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;
					}
				}
			}
			update_dt = update_dt % update_delay;
		}
		update_dt += tick;
	}
	else if(MoveAcc > 0 || Break)
	{
		update_dt = 0;
		if(update_dt2 > update_delay2)
		{
			int count = update_dt2 / update_delay2;
			for(int i = 0; i < count; i++)
			{
				if(MoveAcc >= 0 && MoveAcc < 3)
				{
					Break = false;
					MoveAcc = 4;
					Run = false;
					pMachine->transition(_T("IdleFat"));
				}

				if(MoveAcc > 0 && !Break)
				{
					Rect tmp;
					if(!(::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect)))
					{
						if(BackPosition)
						{
							MoveAcc -= 1;

							if(Wall == 1)
							{
								Break = false;
								MoveAcc = 4;
								Run = false;
								pMachine->transition(_T("IdleFat"));
							}
							else
								KirbyPos.x -= MoveAcc;
							if(KirbyPos.x - KirbyWidth/2 < 0)
								KirbyPos.x = KirbyWidth/2;
						}
						else
						{
							MoveAcc -= 1;

							if(Wall == 2)
							{
								Break = false;
								MoveAcc = 4;
								Run = false;
								pMachine->transition(_T("IdleFat"));
							}
							else
								KirbyPos.x += MoveAcc;
						}
					}
					else
					{
						if(BackPosition)
						{
							MoveAcc -= 1;

							if(Wall == 1)
							{
								Break = false;
								MoveAcc = 4;
								Run = false;
								pMachine->transition(_T("IdleFat"));
							}
							else
								PlayerPos.x -= MoveAcc;
							if(PlayerPos.x < 0)
								PlayerPos.x = 0;
						}
						else
						{
							MoveAcc -= 1;

							if(Wall == 2)
							{
								Break = false;
								MoveAcc = 4;
								Run = false;
								pMachine->transition(_T("IdleFat"));
							}
							else
								PlayerPos.x += MoveAcc;
						}
					}
				}
				else if(Break)
				{
					Rect tmp;
					if(!(::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect)))
					{
						if(BackPosition)
						{
							MoveAcc += 1;

							if(Wall == 2)
							{
								Break = false;
								MoveAcc = 4;
								Run = false;
								pMachine->transition(_T("IdleFat"));
							}
							else
								KirbyPos.x -= MoveAcc;
							if(KirbyPos.x - KirbyWidth/2 < 0)
								KirbyPos.x = KirbyWidth/2;
						}
						else
						{
							MoveAcc += 1;

							if(Wall == 1)
							{
								Break = false;
								MoveAcc = 4;
								Run = false;
								pMachine->transition(_T("IdleFat"));
							}
							else
								KirbyPos.x += MoveAcc;
							if(KirbyPos.x - KirbyWidth/2 < 0)
								KirbyPos.x = KirbyWidth/2;
						}
					}
					else
					{
						if(BackPosition)
						{
							MoveAcc += 1;

							if(Wall == 2)
							{
								Break = false;
								MoveAcc = 4;
								Run = false;
								pMachine->transition(_T("IdleFat"));
							}
							else
								PlayerPos.x -= MoveAcc;
							if(PlayerPos.x < 0)
								PlayerPos.x = 0;
						}
						else
						{
							MoveAcc += 1;

							if(Wall == 1)
							{
								Break = false;
								MoveAcc = 4;
								Run = false;
								pMachine->transition(_T("IdleFat"));
							}
							else
								PlayerPos.x += MoveAcc;
							if(PlayerPos.x < 375)
								PlayerPos.x = 375;
						}
					}
				}
			}
			update_dt2 = update_dt2 % update_delay2;
		}
		update_dt2 += tick;
	}
	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!Stand)
	{
		Break = false;
		MoveAcc = 4;
		Run = false;
		pMachine->transition(_T("LandingFat"));
	}

	// 애니메이션 업데이트
	ImgDepot["KirbyFatBreak"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top-14, KirbyRect.right+10, KirbyRect.bottom));
	AniDepot["KirbyFatRun"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top-14, KirbyRect.right+10, KirbyRect.bottom));

	ImgDepot["KirbyFatBreakBack"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-14, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyFatRunBack"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-14, KirbyRect.right+5, KirbyRect.bottom));

	AniDepot["KirbyFatRun"]->Update(tick);

	AniDepot["KirbyFatRunBack"]->Update(tick);
}
void KirbyFatRun::Draw(HDC hdc)
{
	if(!Break)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyFatRun"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyFatRunBack"]->Draw(hdc);
		}
	}
	else
	{
		if(BackPosition)
		{
			ImgDepot["KirbyFatBreak"]->Draw(hdc);
		}
		else
		{
			ImgDepot["KirbyFatBreakBack"]->Draw(hdc);
		}
	}
}
void KirbyFatRun::Leave()
{
}
void KirbyFatRun::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyFatRun::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyFatRun::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyFatRun::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyFatRun::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyFatRun::GetRect()
{
	return Rect(100,0,0,0);
}
void KirbyFatRun::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}

/////////////////////////////////////////////////////////////
// 점프하는 동작
/////////////////////////////////////////////////////////////
KirbyJump::KirbyJump()
: Rolling(false), update_dt(0), update_delay(20), MoveAcc(4)
, Stand(false), Wall(0), JumpEnd(false), Jump(false)
,JumpAcc(18), KeyPush(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyJump::~KirbyJump()
{
}
void KirbyJump::Enter()
{
	ImgDepot["KirbyJumpStart"]->SetRect(KirbyRect);
	ImgDepot["KirbyJumpStartBack"]->SetRect(KirbyRect);

	AniDepot["KirbyRolling"]->SetRect(KirbyRect);
	AniDepot["KirbyRollingBack"]->SetRect(KirbyRect);
}
void KirbyJump::Input(DWORD)
{
	if (InputDevice[VK_RIGHT])
	{
		BackPosition = false;
		KeyPush = true;
	}
	else if (InputDevice[VK_LEFT])
	{
		BackPosition = true;
		KeyPush = true;
	}
	else
		KeyPush = false;

	if (InputDevice.OnClick('C'))
	{
		AniDepot["KirbyRolling"]->reset();
		AniDepot["KirbyRollingBack"]->reset();
		Rolling = false;
		JumpAcc = 18;
		Jump = false;
		pMachine->transition(_T("Float"));
	}
	if(InputDevice['X'])
	{
		AniDepot["KirbyRolling"]->reset();
		AniDepot["KirbyRollingBack"]->reset();
		Rolling = false;
		JumpAcc = 18;
		Jump = false;
		pMachine->transition(_T("Drain"));
	}
}
void KirbyJump::Update(DWORD tick)
{
	// 캐릭터 좌표 업데이트
	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	if(update_dt > update_delay)
	{
		int count = update_dt / update_delay;
		for(int i = 0; i < count; i++)
		{
			Rect tmp;
			if(KeyPush)
			{
				if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
				{
					MoveAcc += 1;

					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(PlayerPos.x < 375)
						PlayerPos.x = 375;

					if(!(Wall == 2))
						PlayerPos.x += MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
				{
					MoveAcc += 1;

					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 1))
						PlayerPos.x -= MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(PlayerPos.x < 0)
						PlayerPos.x = 0;

					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				else if(!BackPosition)
				{
					MoveAcc += 1;

					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 2))
						KirbyPos.x += MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				else if(BackPosition)
				{
					MoveAcc += 1;

					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 1))
						KirbyPos.x -= MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				if(JumpAcc <= 0)
					Rolling = true;
			}
			else
			{
				if(!BackPosition)
				{
					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				else if(BackPosition)
				{
					JumpAcc -= 1;

					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				if(JumpAcc <= 0)
					Rolling = true;
			}
		}
		update_dt = update_dt % update_delay;
	} // if(update_dt > update_delay)
	update_dt += tick;

	if(!Jump && !SndDepot["Jump"]->IsPlaying())
	{
		SndDepot["Jump"]->Play();
		Jump = true;
	}
	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	// 애니메이션 업데이트
	ImgDepot["KirbyJumpStart"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
	ImgDepot["KirbyJumpStartBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));

	AniDepot["KirbyRolling"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyRollingBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));
	if(Rolling)
	{
		AniDepot["KirbyRolling"]->Update(tick);
		AniDepot["KirbyRollingBack"]->Update(tick);
	}

	if(!(AniDepot["KirbyRolling"]->IsPlaying()) || !(AniDepot["KirbyRollingBack"]->IsPlaying()) && Rolling)
	{
		AniDepot["KirbyRolling"]->reset();
		AniDepot["KirbyRollingBack"]->reset();

		Rolling = false;
		JumpAcc = 18;
		Jump = false;
		pMachine->transition(_T("Landing"));
	}
}
void KirbyJump::Draw(HDC hdc)
{
	if(!Rolling)
	{
		if(!BackPosition)
		{
			ImgDepot["KirbyJumpStart"]->Draw(hdc);
		}
		else
		{
			ImgDepot["KirbyJumpStartBack"]->Draw(hdc);
		}
	}
	if(Rolling)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyRolling"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyRollingBack"]->Draw(hdc);
		}
	}
}
void KirbyJump::Leave()
{
}
void KirbyJump::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyJump::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyJump::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyJump::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyJump::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyJump::GetRect()
{
	return Rect(2000,0,0,0);
}
void KirbyJump::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}


/////////////////////////////////////////////////////////////
// 뚱뚱한 점프하는 동작
/////////////////////////////////////////////////////////////
KirbyFatJump::KirbyFatJump()
: Rolling(false), update_dt(0), update_delay(20), MoveAcc(4)
, Stand(false), Wall(0), JumpEnd(false), update_shot(0)
,JumpAcc(18), KeyPush(false), Jump(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyFatJump::~KirbyFatJump()
{
}
void KirbyFatJump::Enter()
{
	ImgDepot["KirbyFatJumpStart"]->SetRect(KirbyRect);
	ImgDepot["KirbyFatJumpStartBack"]->SetRect(KirbyRect);

	AniDepot["KirbyFatRolling"]->SetRect(KirbyRect);
	AniDepot["KirbyFatRollingBack"]->SetRect(KirbyRect);
}
void KirbyFatJump::Input(DWORD tick)
{
	if (InputDevice[VK_RIGHT])
	{
		BackPosition = false;
		KeyPush = true;
	}
	else if (InputDevice[VK_LEFT])
	{
		BackPosition = true;
		KeyPush = true;
	}
	else
		KeyPush = false;

	if(update_shot > 250)
	{
		if(InputDevice.OnClick('X'))
		{
			update_shot = 0;
			AniDepot["KirbyFatRolling"]->reset();
			AniDepot["KirbyFatRollingBack"]->reset();
			Rolling = false;
			JumpAcc = 18;
			Jump = false;
			pMachine->transition(_T("Shot"));
		}
	}
	update_shot += tick;
}
void KirbyFatJump::Update(DWORD tick)
{
	// 캐릭터 좌표 업데이트
	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	if(update_dt > update_delay)
	{
		int count = update_dt / update_delay;
		for(int i = 0; i < count; i++)
		{
			Rect tmp;
			if(KeyPush)
			{
				if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
				{
					MoveAcc += 1;

					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(PlayerPos.x < 375)
						PlayerPos.x = 375;

					if(!(Wall == 2))
						PlayerPos.x += MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
				{
					MoveAcc += 1;

					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 1))
						PlayerPos.x -= MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(PlayerPos.x < 0)
						PlayerPos.x = 0;

					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				else if(!BackPosition)
				{
					MoveAcc += 1;

					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 2))
						KirbyPos.x += MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				else if(BackPosition)
				{
					MoveAcc += 1;

					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 1))
						KirbyPos.x -= MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				if(JumpAcc <= 0)
					Rolling = true;
			}
			else
			{
				if(!BackPosition)
				{
					JumpAcc -= 1;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				else if(BackPosition)
				{
					JumpAcc -= 1;

					if(!UpBlock)
						KirbyPos.y -= JumpAcc;

					if(KirbyPos.y < 0)
						KirbyPos.y = 0;
				}
				if(JumpAcc <= 0)
					Rolling = true;
			}
		}
		update_dt = update_dt % update_delay;
	} // if(update_dt > update_delay)
	update_dt += tick;

	if(!Jump && !SndDepot["Jump"]->IsPlaying())
	{
		SndDepot["Jump"]->Play();
		Jump = true;
	}

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	/*if(!Stand)
	{
	Rolling = false;
	JumpAcc = 15;
	pMachine->transition(_T("Landing"));
	}*/

	// 애니메이션 업데이트
	ImgDepot["KirbyFatJumpStart"]->SetRect(Rect(KirbyRect.left-6, KirbyRect.top-9, KirbyRect.right+12, KirbyRect.bottom));
	ImgDepot["KirbyFatJumpStartBack"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-9, KirbyRect.right+6, KirbyRect.bottom));

	AniDepot["KirbyFatRolling"]->SetRect(Rect(KirbyRect.left-6, KirbyRect.top-9, KirbyRect.right+12, KirbyRect.bottom));
	AniDepot["KirbyFatRollingBack"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-9, KirbyRect.right+6, KirbyRect.bottom));
	if(Rolling)
	{
		AniDepot["KirbyFatRolling"]->Update(tick);
		AniDepot["KirbyFatRollingBack"]->Update(tick);
	}

	if(!(AniDepot["KirbyFatRolling"]->IsPlaying()) || !(AniDepot["KirbyFatRollingBack"]->IsPlaying()) && Rolling)
	{
		AniDepot["KirbyFatRolling"]->reset();
		AniDepot["KirbyFatRollingBack"]->reset();

		Rolling = false;
		JumpAcc = 18;
		Jump = false;
		pMachine->transition(_T("LandingFat"));
	}
}
void KirbyFatJump::Draw(HDC hdc)
{
	if(!Rolling)
	{
		if(!BackPosition)
		{
			ImgDepot["KirbyFatJumpStart"]->Draw(hdc);
		}
		else
		{
			ImgDepot["KirbyFatJumpStartBack"]->Draw(hdc);
		}
	}
	if(Rolling)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyFatRolling"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyFatRollingBack"]->Draw(hdc);
		}
	}
}
void KirbyFatJump::Leave()
{
}
void KirbyFatJump::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyFatJump::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyFatJump::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyFatJump::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyFatJump::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyFatJump::GetRect()
{
	return Rect(100,0,0,0);
}
void KirbyFatJump::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}

/////////////////////////////////////////////////////////////
// 낙하하는 동작
/////////////////////////////////////////////////////////////
KirbyLanding::KirbyLanding()
: update_dt(0), update_delay(20), MoveAcc(4)
, Stand(false), Wall(0), Landing(false)
,JumpAcc(0), KeyPush(false), Land(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyLanding::~KirbyLanding()
{
}
void KirbyLanding::Enter()
{
	AniDepot["KirbyLanding"]->SetRect(KirbyRect);
	AniDepot["KirbyLandingBack"]->SetRect(KirbyRect);

	AniDepot["KirbyJumpEnd"]->SetRect(KirbyRect);
	AniDepot["KirbyJumpEndBack"]->SetRect(KirbyRect);
}
void KirbyLanding::Input(DWORD)
{
	if (InputDevice[VK_RIGHT])
	{
		BackPosition = false;
		KeyPush = true;
	}
	else if (InputDevice[VK_LEFT])
	{
		BackPosition = true;
		KeyPush = true;
	}
	else
		KeyPush = false;

	if (InputDevice.OnClick('C'))
	{
		JumpAcc = 0;
		Stand = false;
		Landing = false;
		AniDepot["KirbyLanding"]->reset();
		AniDepot["KirbyLandingBack"]->reset();
		Land = false;
		pMachine->transition(_T("Float"));
	}
	if(InputDevice['X'])
	{
		JumpAcc = 0;
		Stand = false;
		Landing = false;
		AniDepot["KirbyLanding"]->reset();
		AniDepot["KirbyLandingBack"]->reset();
		Land = false;
		pMachine->transition(_T("Drain"));
	}
}
void KirbyLanding::Update(DWORD tick)
{
	// 캐릭터 좌표 업데이트

	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	if(update_dt > update_delay)
	{
		int count = update_dt / update_delay;
		for(int i = 0; i < count; i++)
		{
			Rect tmp;
			if(KeyPush && !Landing)
			{
				if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
				{
					MoveAcc += 1;

					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(PlayerPos.x < 375)
						PlayerPos.x = 375;

					if(!(Wall == 2))
						PlayerPos.x += MoveAcc;

					KirbyPos.y += JumpAcc;
				}
				else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
				{
					MoveAcc += 1;

					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 1))
						PlayerPos.x -= MoveAcc;

					KirbyPos.y += JumpAcc;

					if(PlayerPos.x < 0)
						PlayerPos.x = 0;
				}
				else if(!BackPosition)
				{
					MoveAcc += 1;

					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 2))
						KirbyPos.x += MoveAcc;

					KirbyPos.y += JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
				}
				else if(BackPosition)
				{
					MoveAcc += 1;

					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 1))
						KirbyPos.x -= MoveAcc;

					KirbyPos.y += JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
				}
			}
			else if(!Landing)
			{
				if(!BackPosition)
				{
					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					KirbyPos.y += JumpAcc;
				}
				else if(BackPosition)
				{
					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					KirbyPos.y += JumpAcc;
				}
			}
		}
		update_dt = update_dt % update_delay;
	}
	update_dt += tick;

	if(Stand)
	{
		if(!Land && !SndDepot["Land"]->IsPlaying())
		{
			SndDepot["Land"]->Play();
			Land = true;
		}
		Landing = true;
	}
	if(!(AniDepot["KirbyLanding"]->IsPlaying()) && Landing)
	{
		JumpAcc = 0;
		Stand = false;
		Landing = false;
		AniDepot["KirbyLanding"]->reset();
		AniDepot["KirbyLandingBack"]->reset();
		Land = false;
		pMachine->transition(_T("Idle"));
	}

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	// 애니메이션 업데이트
	AniDepot["KirbyLanding"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyLandingBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));

	AniDepot["KirbyJumpEnd"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyJumpEndBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));

	if(Landing)
	{
		AniDepot["KirbyLanding"]->Update(tick);
		AniDepot["KirbyLandingBack"]->Update(tick);
	}
	AniDepot["KirbyJumpEnd"]->Update(tick);
	AniDepot["KirbyJumpEndBack"]->Update(tick);
}
void KirbyLanding::Draw(HDC hdc)
{
	if(!Landing)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyJumpEnd"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyJumpEndBack"]->Draw(hdc);
		}
	}
	else
	{
		if(!BackPosition)
		{
			AniDepot["KirbyLanding"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyLandingBack"]->Draw(hdc);
		}
	}
}
void KirbyLanding::Leave()
{
}
void KirbyLanding::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyLanding::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyLanding::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyLanding::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyLanding::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyLanding::GetRect()
{
	return Rect(2000,0,0,0);
}
void KirbyLanding::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}

/////////////////////////////////////////////////////////////
// 뚱뚱한 낙하하는 동작
/////////////////////////////////////////////////////////////
KirbyFatLanding::KirbyFatLanding()
: update_dt(0), update_delay(20), MoveAcc(4)
, Stand(false), Wall(0), Landing(false), update_shot(0)
,JumpAcc(0), KeyPush(false), Land(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyFatLanding::~KirbyFatLanding()
{
}
void KirbyFatLanding::Enter()
{
	AniDepot["KirbyFatLanding"]->SetRect(KirbyRect);
	AniDepot["KirbyFatLandingBack"]->SetRect(KirbyRect);

	AniDepot["KirbyFatJumpEnd"]->SetRect(KirbyRect);
	AniDepot["KirbyFatJumpEndBack"]->SetRect(KirbyRect);
}
void KirbyFatLanding::Input(DWORD tick)
{
	if (InputDevice[VK_RIGHT])
	{
		BackPosition = false;
		KeyPush = true;
	}
	else if (InputDevice[VK_LEFT])
	{
		BackPosition = true;
		KeyPush = true;
	}
	else
		KeyPush = false;

	if(update_shot > 250)
	{
		if(InputDevice.OnClick('X'))
		{
			update_shot = 0;
			JumpAcc = 0;
			Stand = false;
			Landing = false;
			Land = false;
			AniDepot["KirbyFatLanding"]->reset();
			AniDepot["KirbyFatLandingBack"]->reset();

			pMachine->transition(_T("Shot"));
		}
	}
	update_shot += tick;
}
void KirbyFatLanding::Update(DWORD tick)
{
	// 캐릭터 좌표 업데이트

	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	if(update_dt > update_delay)
	{
		int count = update_dt / update_delay;
		for(int i = 0; i < count; i++)
		{
			Rect tmp;
			if(KeyPush && !Landing)
			{
				if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
				{
					MoveAcc += 1;

					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(PlayerPos.x < 375)
						PlayerPos.x = 375;

					if(!(Wall == 2))
						PlayerPos.x += MoveAcc;

					KirbyPos.y += JumpAcc;
				}
				else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
				{
					MoveAcc += 1;

					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 1))
						PlayerPos.x -= MoveAcc;

					KirbyPos.y += JumpAcc;

					if(PlayerPos.x < 0)
						PlayerPos.x = 0;
				}
				else if(!BackPosition)
				{
					MoveAcc += 1;

					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 2))
						KirbyPos.x += MoveAcc;

					KirbyPos.y += JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
				}
				else if(BackPosition)
				{
					MoveAcc += 1;

					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					if(MoveAcc >= 4)
						MoveAcc = 4;

					if(!(Wall == 1))
						KirbyPos.x -= MoveAcc;

					KirbyPos.y += JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;
				}
			}
			else if(!Landing)
			{
				if(!BackPosition)
				{
					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					KirbyPos.y += JumpAcc;
				}
				else if(BackPosition)
				{
					JumpAcc += 2;

					if(JumpAcc >= 8)
						JumpAcc = 8;

					KirbyPos.y += JumpAcc;
				}
			}
		}
		update_dt = update_dt % update_delay;
	}
	update_dt += tick;

	if(Stand)
	{
		if(!Land && !SndDepot["Land"]->IsPlaying())
		{
			SndDepot["Land"]->Play();
			Land = true;
		}
		Landing = true;
	}
	if(!(AniDepot["KirbyFatLanding"]->IsPlaying()) && Landing)
	{
		JumpAcc = 0;
		Stand = false;
		Landing = false;
		Land = false;
		AniDepot["KirbyFatLanding"]->reset();
		AniDepot["KirbyFatLandingBack"]->reset();
		pMachine->transition(_T("IdleFat"));
	}

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	// 애니메이션 업데이트
	AniDepot["KirbyFatLanding"]->SetRect(Rect(KirbyRect.left-9, KirbyRect.top-9, KirbyRect.right+15, KirbyRect.bottom));
	AniDepot["KirbyFatLandingBack"]->SetRect(Rect(KirbyRect.left-15, KirbyRect.top-9, KirbyRect.right+9, KirbyRect.bottom));

	AniDepot["KirbyFatJumpEnd"]->SetRect(Rect(KirbyRect.left-6, KirbyRect.top-9, KirbyRect.right+12, KirbyRect.bottom));
	AniDepot["KirbyFatJumpEndBack"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-9, KirbyRect.right+6, KirbyRect.bottom));

	if(Landing)
	{
		AniDepot["KirbyFatLanding"]->Update(tick);
		AniDepot["KirbyFatLandingBack"]->Update(tick);
	}
	AniDepot["KirbyFatJumpEnd"]->Update(tick);
	AniDepot["KirbyFatJumpEndBack"]->Update(tick);
}
void KirbyFatLanding::Draw(HDC hdc)
{
	if(!Landing)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyFatJumpEnd"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyFatJumpEndBack"]->Draw(hdc);
		}
	}
	else
	{
		if(!BackPosition)
		{
			AniDepot["KirbyFatLanding"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyFatLandingBack"]->Draw(hdc);
		}
	}
}
void KirbyFatLanding::Leave()
{
}
void KirbyFatLanding::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyFatLanding::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyFatLanding::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyFatLanding::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyFatLanding::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyFatLanding::GetRect()
{
	return Rect(100,0,0,0);
}
void KirbyFatLanding::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}
/////////////////////////////////////////////////////////////
// 공중을 나는 동작
/////////////////////////////////////////////////////////////
KirbyFloat::KirbyFloat()
: update_dt(0), update_delay(10), MoveAcc(4)
, Stand(false), Wall(0), Landing(false), FloatSound(false)
,JumpAcc(0), KeyPush(false), Float(false), KirbyUp(false)
,FloatAirSound(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyFloat::~KirbyFloat()
{
}
void KirbyFloat::Enter()
{
	AniDepot["KirbyFloatStart"]->SetRect(KirbyRect);
	AniDepot["KirbyFloatStartBack"]->SetRect(KirbyRect);

	AniDepot["KirbyFloat"]->SetRect(KirbyRect);
	AniDepot["KirbyFloatBack"]->SetRect(KirbyRect);

	AniDepot["KirbyFloatUp"]->SetRect(KirbyRect);
	AniDepot["KirbyFloatUpBack"]->SetRect(KirbyRect);

	AniDepot["KirbyFloatEnd"]->SetRect(KirbyRect);
	AniDepot["KirbyFloatEndBack"]->SetRect(KirbyRect);
}
void KirbyFloat::Input(DWORD)
{
	if (InputDevice[VK_RIGHT])
	{
		BackPosition = false;
		KeyPush = true;
	}
	else if (InputDevice[VK_LEFT])
	{
		BackPosition = true;
		KeyPush = true;
	}
	else
		KeyPush = false;

	if (InputDevice.OnClick('C'))
	{
		if(!(AniDepot["KirbyFloatStart"]->IsPlaying()) || !(AniDepot["KirbyFloatStartBack"]->IsPlaying()))
		{
			KirbyUp = true;
			FloatSound = false;
		}
	}
	if(InputDevice.OnClick('X'))
	{
		if(!FloatAirSound && !SndDepot["FloatAir"]->IsPlaying())
		{
			SndDepot["FloatAir"]->Play();
			FloatAirSound = true;
		}
		MissileDepot.AirPush(KirbyPos, BackPosition);

		Landing = true;
	}
}
void KirbyFloat::Update(DWORD tick)
{
	// 캐릭터 좌표 업데이트

	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	if(update_dt > update_delay)
	{
		int count = update_dt / update_delay;
		for(int i = 0; i < count; i++)
		{
			Rect tmp;

			if(AniDepot["KirbyFloatStart"]->IsPlaying() || AniDepot["KirbyFloatStartBack"]->IsPlaying())
			{
				if(KeyPush)
				{
					if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
					{
						MoveAcc += 1;

						if(MoveAcc >= 2)
							MoveAcc = 2;

						if(PlayerPos.x < 375)
							PlayerPos.x = 375;

						if(!(Wall == 2))
							PlayerPos.x += MoveAcc;
						if(!UpBlock)
							KirbyPos.y -= 2;

						if(KirbyPos.y - KirbyHeight/2 < 0)
							KirbyPos.y = KirbyHeight/2;
					}
					else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
					{
						MoveAcc += 1;

						if(MoveAcc >= 2)
							MoveAcc = 2;

						if(!(Wall == 1))
							PlayerPos.x -= MoveAcc;
						if(!UpBlock)
							KirbyPos.y -= 2;

						if(PlayerPos.x < 0)
							PlayerPos.x = 0;

						if(KirbyPos.y - KirbyHeight/2 < 0)
							KirbyPos.y = KirbyHeight/2;
					}
					else if(!BackPosition)
					{
						MoveAcc += 1;

						if(MoveAcc >= 2)
							MoveAcc = 2;

						if(!(Wall == 2))
							KirbyPos.x += MoveAcc;
						if(!UpBlock)
							KirbyPos.y -= 2;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;

						if(KirbyPos.y - KirbyHeight/2 < 0)
							KirbyPos.y = KirbyHeight/2;
					}
					else if(BackPosition)
					{
						MoveAcc += 1;

						if(MoveAcc >= 2)
							MoveAcc = 2;

						if(!(Wall == 1))
							KirbyPos.x -= MoveAcc;
						if(!UpBlock)
							KirbyPos.y -= 2;

						if(KirbyPos.x - KirbyWidth/2 < 0)
							KirbyPos.x = KirbyWidth/2;

						if(KirbyPos.y - KirbyHeight/2 < 0)
							KirbyPos.y = KirbyHeight/2;
					}
				}
				else
				{
					if(!BackPosition)
					{
						if(!UpBlock)
							KirbyPos.y -= 2;

						if(KirbyPos.y - KirbyHeight/2 < 0)
							KirbyPos.y = KirbyHeight/2;
					}
					else if(BackPosition)
					{
						if(!UpBlock)
							KirbyPos.y -= 2;

						if(KirbyPos.y - KirbyHeight/2 < 0)
							KirbyPos.y = KirbyHeight/2;
					}
				}
			}
			if(KeyPush && Float)
			{
				if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
				{
					MoveAcc += 1;

					JumpAcc += 1;

					if(JumpAcc >= 1)
						JumpAcc = 1;

					if(MoveAcc >= 2)
						MoveAcc = 2;

					if(PlayerPos.x < 375)
						PlayerPos.x = 375;

					if(!(Wall == 2))
						PlayerPos.x += MoveAcc;

					KirbyPos.y += JumpAcc;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
				else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
				{
					MoveAcc += 1;

					JumpAcc += 1;

					if(JumpAcc >= 1)
						JumpAcc = 1;

					if(MoveAcc >= 2)
						MoveAcc = 2;

					if(!(Wall == 1))
						PlayerPos.x -= MoveAcc;

					KirbyPos.y += JumpAcc;

					if(PlayerPos.x < 0)
						PlayerPos.x = 0;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
				else if(!BackPosition)
				{
					MoveAcc += 1;

					JumpAcc += 1;

					if(JumpAcc >= 1)
						JumpAcc = 1;

					if(MoveAcc >= 2)
						MoveAcc = 2;

					if(!(Wall == 2))
						KirbyPos.x += MoveAcc;

					KirbyPos.y += JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
				else if(BackPosition)
				{
					MoveAcc += 1;

					JumpAcc += 1;

					if(JumpAcc >= 1)
						JumpAcc = 1;

					if(MoveAcc >= 2)
						MoveAcc = 2;

					if(!(Wall == 1))
						KirbyPos.x -= MoveAcc;

					KirbyPos.y += JumpAcc;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
			}
			else if(Float)
			{
				if(!BackPosition)
				{
					JumpAcc += 1;

					if(JumpAcc >= 1)
						JumpAcc = 1;

					KirbyPos.y += JumpAcc;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
				else if(BackPosition)
				{
					JumpAcc += 1;

					if(JumpAcc >= 1)
						JumpAcc = 1;


					KirbyPos.y += JumpAcc;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
			} // if(KeyPush && Float)
			if(KeyPush && KirbyUp)
			{
				if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
				{
					MoveAcc += 1;

					if(MoveAcc >= 2)
						MoveAcc = 2;

					if(PlayerPos.x < 375)
						PlayerPos.x = 375;

					if(!(Wall == 2))
						PlayerPos.x += MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= 2;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
				else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
				{
					MoveAcc += 1;

					if(MoveAcc >= 2)
						MoveAcc = 2;

					if(!(Wall == 1))
						PlayerPos.x -= MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= 2;

					if(PlayerPos.x < 0)
						PlayerPos.x = 0;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
				else if(!BackPosition)
				{
					MoveAcc += 1;

					if(MoveAcc >= 2)
						MoveAcc = 2;

					if(!(Wall == 2))
						KirbyPos.x += MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= 2;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
				else if(BackPosition)
				{
					MoveAcc += 1;

					if(MoveAcc >= 2)
						MoveAcc = 2;

					if(!(Wall == 1))
						KirbyPos.x -= MoveAcc;
					if(!UpBlock)
						KirbyPos.y -= 2;

					if(KirbyPos.x - KirbyWidth/2 < 0)
						KirbyPos.x = KirbyWidth/2;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
			}
			else if(KirbyUp)
			{
				if(!BackPosition)
				{
					if(!UpBlock)
						KirbyPos.y -= 2;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
				else if(BackPosition)
				{
					if(!UpBlock)
						KirbyPos.y -= 2;

					if(KirbyPos.y - KirbyHeight/2 < 0)
						KirbyPos.y = KirbyHeight/2;
				}
			}
		} // for(int i = 0; i < count; i++)
		update_dt = update_dt % update_delay;
	}
	update_dt += tick;

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if(!FloatSound && !SndDepot["Float"]->IsPlaying())
	{
		SndDepot["Float"]->Play();
		FloatSound = true;
	}

	if(!(AniDepot["KirbyFloatStart"]->IsPlaying()) || !(AniDepot["KirbyFloatStartBack"]->IsPlaying()) && !KirbyUp && !Float)
	{
		Float = true;
	}
	if(Stand)
	{
		if(!FloatAirSound && !SndDepot["FloatAir"]->IsPlaying())
		{
			SndDepot["FloatAir"]->Play();
			FloatAirSound = true;
			MissileDepot.AirPush(KirbyPos, BackPosition);
		}
		Float = false;
		Landing = true;
	}
	if(Float && KirbyUp)
	{
		Float = false;
	}

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	AniDepot["KirbyFloatStart"]->SetRect(Rect(KirbyRect.left, KirbyRect.top - 8, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyFloatStartBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top - 8, KirbyRect.right, KirbyRect.bottom));

	AniDepot["KirbyFloat"]->SetRect(Rect(KirbyRect.left-3, KirbyRect.top - 18, KirbyRect.right+15, KirbyRect.bottom));
	AniDepot["KirbyFloatBack"]->SetRect(Rect(KirbyRect.left-15, KirbyRect.top - 18, KirbyRect.right+3, KirbyRect.bottom));

	AniDepot["KirbyFloatUp"]->SetRect(Rect(KirbyRect.left-3, KirbyRect.top - 18, KirbyRect.right+15, KirbyRect.bottom));
	AniDepot["KirbyFloatUpBack"]->SetRect(Rect(KirbyRect.left-15, KirbyRect.top - 18, KirbyRect.right+3, KirbyRect.bottom));

	AniDepot["KirbyFloatEnd"]->SetRect(Rect(KirbyRect.left, KirbyRect.top - 8, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyFloatEndBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top - 8, KirbyRect.right, KirbyRect.bottom));

	if(!Float && !KirbyUp && !Stand && !Landing)
	{
		AniDepot["KirbyFloatStart"]->Update(tick);
		AniDepot["KirbyFloatStartBack"]->Update(tick);
	}
	if(Float && !Landing)
	{
		AniDepot["KirbyFloat"]->Update(tick);
		AniDepot["KirbyFloatBack"]->Update(tick);
	}
	if(KirbyUp && !Landing)
	{
		AniDepot["KirbyFloatUp"]->Update(tick);
		AniDepot["KirbyFloatUpBack"]->Update(tick);
	}
	if(Landing)
	{
		AniDepot["KirbyFloatEnd"]->Update(tick);
		AniDepot["KirbyFloatEndBack"]->Update(tick);
	}

	if(Landing && !(AniDepot["KirbyFloatEnd"]->IsPlaying()) || !(AniDepot["KirbyFloatEndBack"]->IsPlaying()))
	{
		AniDepot["KirbyFloatStart"]->reset();
		AniDepot["KirbyFloatStartBack"]->reset();
		AniDepot["KirbyFloatUp"]->reset();
		AniDepot["KirbyFloatUpBack"]->reset();
		AniDepot["KirbyFloatEnd"]->reset();
		AniDepot["KirbyFloatEndBack"]->reset();

		FloatAirSound = false;
		FloatSound = false;
		Landing = false;
		Stand = false;
		KirbyUp = false;
		Float = false;

		pMachine->transition(_T("Landing"));
	}
	if(!(AniDepot["KirbyFloatUp"]->IsPlaying()) || !(AniDepot["KirbyFloatUpBack"]->IsPlaying()) && KirbyUp)
	{
		KirbyUp = false;
		AniDepot["KirbyFloatUp"]->reset();
		AniDepot["KirbyFloatUpBack"]->reset();
		Float = true;
	}
}
void KirbyFloat::Draw(HDC hdc)
{
	if(!Float && !KirbyUp && !Stand && !Landing)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyFloatStart"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyFloatStartBack"]->Draw(hdc);
		}
	}
	else if(Float && !Landing)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyFloat"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyFloatBack"]->Draw(hdc);
		}
	}
	else if(KirbyUp && !Landing)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyFloatUp"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyFloatUpBack"]->Draw(hdc);
		}
	}
	else if(Landing)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyFloatEnd"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyFloatEndBack"]->Draw(hdc);
		}
	}
}
void KirbyFloat::Leave()
{
}
void KirbyFloat::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyFloat::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyFloat::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyFloat::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyFloat::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyFloat::GetRect()
{
	return Rect(2000,0,0,0);
}
void KirbyFloat::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}

/////////////////////////////////////////////////////////////
// 흡수하는 동작
/////////////////////////////////////////////////////////////
KirbyDrain::KirbyDrain()
: update_dt(0), update_delay(20), Stand(false)
, Wall(0),JumpAcc(0), KeyPush(false), DrainStart(true), test(false)
, Drain(false), DrainR(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;

	DrainBox = new SquareBox; 

	for(int i = 0; i < 1; i++)
	{
		Effect* tmp = new Effect;

		EffectDepot.Push(tmp);
	}
}
KirbyDrain::~KirbyDrain()
{
	if (DrainBox)
		delete DrainBox;

	EffectDepot.Rerease();
}
void KirbyDrain::Enter()
{
	AniDepot["KirbyDrainStart"]->SetRect(KirbyRect);
	AniDepot["KirbyDrainStartBack"]->SetRect(KirbyRect);

	AniDepot["KirbyDrain"]->SetRect(KirbyRect);
	AniDepot["KirbyDrainBack"]->SetRect(KirbyRect);
}
void KirbyDrain::Input(DWORD)
{
	if (InputDevice['X'])
	{
		if(!Stand)
			test = false;
		else
			test = true;

		KeyPush = true;
	}
	else if(Wall != 99)
	{
		DrainStart = true;
		Drain = false;
		DrainR = false;
		SndDepot["DrainS"]->Stop();
		SndDepot["DrainR"]->Stop();
		AniDepot["KirbyDrainStart"]->reset();
		AniDepot["KirbyDrainStartBack"]->reset();
		test = false;

		if(Stand)
		{
			pMachine->transition(_T("Idle"));
		}
		else
		{
			pMachine->transition(_T("Landing"));
		}
	}
}
void KirbyDrain::Update(DWORD tick)
{
	// 캐릭터 좌표 업데이트

	if(KeyPush)
	{
		if(update_dt > update_delay)
		{
			int count = update_dt / update_delay;
			for(int i = 0; i < count; i++)
			{
				if(!Stand)
				{
					if(!BackPosition)
					{
						JumpAcc += 2;

						if(JumpAcc >= 8)
							JumpAcc = 8;

						if(!Stand)
							KirbyPos.y += JumpAcc;
					}
					else if(BackPosition)
					{
						JumpAcc += 2;

						if(JumpAcc >= 8)
							JumpAcc = 8;

						if(!Stand)
							KirbyPos.y += JumpAcc;
					}
				}
			}
			update_dt %= update_delay; 
		}
		update_dt += tick;
	}
	if(!Drain && !SndDepot["DrainS"]->IsPlaying())
	{
		SndDepot["DrainS"]->Play();
		Drain = true;
	}
	if(!(SndDepot["DrainS"]->IsPlaying()) && !DrainR)
	{
		SndDepot["DrainR"]->Play();
		DrainR = true;
	}

	// 캐릭터 상태 업데이트

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!(AniDepot["KirbyDrainStart"]->IsPlaying()) || !(AniDepot["KirbyDrainStartBack"]->IsPlaying()))
	{
		DrainStart = false;
	}

	AniDepot["KirbyDrainStart"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyDrainStartBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));

	AniDepot["KirbyDrain"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyDrainBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));

	if(DrainStart)
	{
		AniDepot["KirbyDrainStart"]->Update(tick);
		AniDepot["KirbyDrainStartBack"]->Update(tick);
	}
	else
	{
		AniDepot["KirbyDrain"]->Update(tick);
		AniDepot["KirbyDrainBack"]->Update(tick);
		EffectDepot.Update(tick, KirbyPos);
	}

}
void KirbyDrain::Draw(HDC hdc)
{
	if(DrainStart)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyDrainStart"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyDrainStartBack"]->Draw(hdc);
		}
	}
	else
	{
		if(!BackPosition)
		{
			AniDepot["KirbyDrain"]->Draw(hdc);
			EffectDepot.Draw(hdc);
		}
		else
		{
			AniDepot["KirbyDrainBack"]->Draw(hdc);
			EffectDepot.Draw(hdc);
		}
	}
	if (DrainBox)
		DrainBox->Draw(hdc);
}
void KirbyDrain::Leave()
{
}
void KirbyDrain::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;

	if(!DrainStart)
	{
		if(!BackPosition)
		{
			DrainRect.left = KirbyRect.right;
			DrainRect.top = KirbyRect.top - 40;
			DrainRect.right = DrainRect.left + 150;
			DrainRect.bottom = KirbyRect.bottom + 40;
		}
		else
		{
			DrainRect.right = KirbyRect.left;
			DrainRect.top = KirbyRect.top - 40;
			DrainRect.left = DrainRect.right - 150;
			DrainRect.bottom = KirbyRect.bottom + 40;
		}
	}
	else
		DrainRect = KirbyRect;

	if (DrainBox)
		dynamic_cast<SquareBox*>(DrainBox)->SetRect(DrainRect);

	EffectDepot.SetPosition(DrainRect, BackPosition);

}
void KirbyDrain::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyDrain::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyDrain::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyDrain::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyDrain::GetRect()
{
	if(!DrainStart)
		return DrainRect;
	else
		return Rect(0,0,0,0);
}
void KirbyDrain::Reset()
{
	DrainStart = true;
	Drain = false;
	DrainR = false;
	SndDepot["DrainS"]->Stop();
	SndDepot["DrainR"]->Stop();
	AniDepot["KirbyDrainStart"]->reset();
	AniDepot["KirbyDrainStartBack"]->reset();
	EffectDepot.Rerease();
	Effect* tmp = new Effect;

	EffectDepot.Push(tmp);
	test = false;
}

/////////////////////////////////////////////////////////////
// 맞았을때 동작
/////////////////////////////////////////////////////////////
KirbyHit::KirbyHit()
: update_dt(0), MoveAcc(0), update_delay(20), JumpAcc(0)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20)
, Hit(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyHit::~KirbyHit()
{
}
void KirbyHit::Enter()
{
}
void KirbyHit::Input(DWORD tick)
{
	if(Wall == 1)
	{
		AniDepot["KirbyHit"]->reset();
		AniDepot["KirbyHitBack"]->reset();
		Hit = false;
		pMachine->transition(_T("Idle"));
	}
	if(Wall == 2)
	{
		AniDepot["KirbyHit"]->reset();
		AniDepot["KirbyHitBack"]->reset();
		Hit = false;
		pMachine->transition(_T("Idle"));
	}
}
void KirbyHit::Update(DWORD tick)
{
	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; i < count; i++)
		{
			Rect tmp;
			if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(PlayerPos.x < 390)
					PlayerPos.x = 390;
				if(Wall == 1)
				{
					AniDepot["KirbyHit"]->reset();
					AniDepot["KirbyHitBack"]->reset();
					Hit = false;
					pMachine->transition(_T("Idle"));
				}
				else
					PlayerPos.x -= MoveAcc;
			}
			else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(Wall == 2)
				{
					AniDepot["KirbyHit"]->reset();
					AniDepot["KirbyHitBack"]->reset();
					Hit = false;
					pMachine->transition(_T("Idle"));
				}
				else
					PlayerPos.x += MoveAcc;

				if(PlayerPos.x < 0)
					PlayerPos.x = 0;
			}
			else if(!BackPosition)
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(Wall == 1)
				{
					AniDepot["KirbyHit"]->reset();
					AniDepot["KirbyHitBack"]->reset();
					Hit = false;
					pMachine->transition(_T("Idle"));
				}
				else
					KirbyPos.x -= MoveAcc;

				if(KirbyPos.x - KirbyWidth/2 < 0)
					KirbyPos.x = KirbyWidth/2;
			}
			else if(BackPosition)
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(Wall == 2)
				{
					AniDepot["KirbyHit"]->reset();
					AniDepot["KirbyHitBack"]->reset();
					Hit = false;
					pMachine->transition(_T("Idle"));
				}
				else
					KirbyPos.x += MoveAcc;

				if(KirbyPos.x - KirbyWidth/2 < 0)
					KirbyPos.x = KirbyWidth/2;
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

				KirbyPos.y += JumpAcc;
			}
			update_dt2 %= update_delay2;
		}
		update_dt2 += tick;
	}
	if(!Hit && !SndDepot["Hit"]->IsPlaying())
	{
		SndDepot["Hit"]->Play();
		Hit = true;
	}
	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!(AniDepot["KirbyHit"]->IsPlaying()) || !(AniDepot["KirbyHitBack"]->IsPlaying()))
	{
		AniDepot["KirbyHit"]->reset();
		AniDepot["KirbyHitBack"]->reset();
		Hit = false;
		pMachine->transition(_T("Idle"));
	}

	AniDepot["KirbyHit"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
	AniDepot["KirbyHitBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));

	AniDepot["KirbyHit"]->Update(tick);
	AniDepot["KirbyHitBack"]->Update(tick);
}
void KirbyHit::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["KirbyHit"]->Draw(hdc);
	}
	else
	{
		AniDepot["KirbyHitBack"]->Draw(hdc);
	}
}
void KirbyHit::Leave()
{
}
void KirbyHit::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyHit::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyHit::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyHit::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyHit::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyHit::GetRect()
{
	return Rect(2000,0,0,0);
}
void KirbyHit::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}


/////////////////////////////////////////////////////////////
// 뚱뚱한 맞았을때 동작
/////////////////////////////////////////////////////////////
KirbyFatHit::KirbyFatHit()
: update_dt(0), MoveAcc(0), update_delay(20), Hit(false)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyFatHit::~KirbyFatHit()
{
}
void KirbyFatHit::Enter()
{
}
void KirbyFatHit::Input(DWORD tick)
{
	if(Wall == 1)
	{
		AniDepot["KirbyFatHit"]->reset();
		AniDepot["KirbyFatHitBack"]->reset();
		Hit = false;
		pMachine->transition(_T("IdleFat"));
	}
	if(Wall == 2)
	{
		AniDepot["KirbyFatHit"]->reset();
		AniDepot["KirbyFatHitBack"]->reset();
		Hit = false;
		pMachine->transition(_T("IdleFat"));
	}
}
void KirbyFatHit::Update(DWORD tick)
{
	if(PlayerPos.x >= 11300)
	{
		PlayerPos.x = 11300;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}

	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; i < count; i++)
		{
			Rect tmp;
			if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(PlayerPos.x < 390)
					PlayerPos.x = 390;
				if(Wall == 1)
				{
					AniDepot["KirbyFatHit"]->reset();
					AniDepot["KirbyFatHitBack"]->reset();
					Hit = false;
					pMachine->transition(_T("IdleFat"));
				}
				else
					PlayerPos.x -= MoveAcc;
			}
			else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(Wall == 2)
				{
					AniDepot["KirbyFatHit"]->reset();
					AniDepot["KirbyFatHitBack"]->reset();
					Hit = false;
					pMachine->transition(_T("IdleFat"));
				}
				else
					PlayerPos.x += MoveAcc;

				if(PlayerPos.x < 0)
					PlayerPos.x = 0;
			}
			else if(!BackPosition)
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(Wall == 1)
				{
					AniDepot["KirbyFatHit"]->reset();
					AniDepot["KirbyFatHitBack"]->reset();
					Hit = false;
					pMachine->transition(_T("IdleFat"));
				}
				else
					KirbyPos.x -= MoveAcc;

				if(KirbyPos.x - KirbyWidth/2 < 0)
					KirbyPos.x = KirbyWidth/2;
			}
			else if(BackPosition)
			{
				MoveAcc += 1;

				if(MoveAcc >= 2)
					MoveAcc = 2;

				if(Wall == 2)
				{
					AniDepot["KirbyFatHit"]->reset();
					AniDepot["KirbyFatHitBack"]->reset();
					Hit = false;
					pMachine->transition(_T("IdleFat"));
				}
				else
					KirbyPos.x += MoveAcc;

				if(KirbyPos.x - KirbyWidth/2 < 0)
					KirbyPos.x = KirbyWidth/2;
			}
		}
		update_dt %= update_delay;
	}
	update_dt += tick;

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

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

				KirbyPos.y += JumpAcc;
			}
			update_dt2 %= update_delay2;
		}
		update_dt2 += tick;
	}
	if(!Hit && !SndDepot["Hit"]->IsPlaying())
	{
		SndDepot["Hit"]->Play();
		Hit = true;
	}

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!(AniDepot["KirbyFatHit"]->IsPlaying()) || !(AniDepot["KirbyFatHitBack"]->IsPlaying()))
	{
		AniDepot["KirbyFatHit"]->reset();
		AniDepot["KirbyFatHitBack"]->reset();
		Hit = false;
		pMachine->transition(_T("IdleFat"));
	}

	AniDepot["KirbyFatHit"]->SetRect(Rect(KirbyRect.left-6, KirbyRect.top-10, KirbyRect.right+12, KirbyRect.bottom));
	AniDepot["KirbyFatHitBack"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-10, KirbyRect.right+6, KirbyRect.bottom));

	AniDepot["KirbyFatHit"]->Update(tick);
	AniDepot["KirbyFatHitBack"]->Update(tick);
}
void KirbyFatHit::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["KirbyFatHit"]->Draw(hdc);
	}
	else
	{
		AniDepot["KirbyFatHitBack"]->Draw(hdc);
	}
}
void KirbyFatHit::Leave()
{
}
void KirbyFatHit::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyFatHit::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyFatHit::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyFatHit::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyFatHit::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyFatHit::GetRect()
{
	return Rect(100,0,0,0);
}
void KirbyFatHit::SetBossStage(const bool& b)
{
	Boss = b;
	if(Boss)
	{
		Zone[LeftZone].right = Zone[LeftZone].left;
		Zone[RightZone].left = Zone[RightZone].right;
	}
	else
	{
		Zone[LeftZone].right = Zone[LeftZone].left + 375;
		Zone[RightZone].left = Zone[RightZone].right - 375;
	}
}

/////////////////////////////////////////////////////////////
// 별 발사 동작
/////////////////////////////////////////////////////////////
KirbyShot::KirbyShot()
: update_dt(0), MoveAcc(0), update_delay(20), Shot(true)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20), Shotcount(0)
, StarShot(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyShot::~KirbyShot()
{
}
void KirbyShot::Enter()
{
}
void KirbyShot::Input(DWORD tick)
{

}
void KirbyShot::Update(DWORD tick)
{
	if(!StarShot)
	{
		SndDepot["StarShot"]->Play();
		StarShot = true;
	}

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	AniDepot["KirbyShotStart"]->SetRect(Rect(KirbyRect.left-68, KirbyRect.top-14, KirbyRect.right+100, KirbyRect.bottom+4));
	AniDepot["KirbyShotStartBack"]->SetRect(Rect(KirbyRect.left-100, KirbyRect.top-14, KirbyRect.right+68, KirbyRect.bottom+4));
	AniDepot["KirbyShotEnd"]->SetRect(Rect(KirbyRect.left-2, KirbyRect.top-4, KirbyRect.right+4, KirbyRect.bottom));
	AniDepot["KirbyShotEndBack"]->SetRect(Rect(KirbyRect.left-4, KirbyRect.top-4, KirbyRect.right+2, KirbyRect.bottom));

	if(Shot)
	{
		AniDepot["KirbyShotStart"]->Update(tick);
		AniDepot["KirbyShotStartBack"]->Update(tick);
	}
	else
	{
		AniDepot["KirbyShotEnd"]->Update(tick);
		AniDepot["KirbyShotEndBack"]->Update(tick);
	}

	if(update_dt > 100)
	{
		if(Shotcount == 0)
		{
			MissileDepot.StarPush(KirbyPos, BackPosition);
			Shotcount ++;
		}

		update_dt %= 100;
	}
	update_dt += tick;

	if(!(AniDepot["KirbyShotStart"]->IsPlaying()) || !(AniDepot["KirbyShotStartBack"]->IsPlaying()))
	{
		Shot = false;
	}

	if(!(AniDepot["KirbyShotEnd"]->IsPlaying()) || !(AniDepot["KirbyShotEndBack"]->IsPlaying()))
	{
		Shotcount = 0;
		Shot = true;
		StarShot = false;
		AniDepot["KirbyShotStart"]->reset();
		AniDepot["KirbyShotStartBack"]->reset();
		AniDepot["KirbyShotEnd"]->reset();
		AniDepot["KirbyShotEndBack"]->reset();
		pMachine->transition(_T("Idle"));
	}
}
void KirbyShot::Draw(HDC hdc)
{
	if(Shot)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyShotStart"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyShotStartBack"]->Draw(hdc);
		}
	}
	else
	{
		if(!BackPosition)
		{
			AniDepot["KirbyShotEnd"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyShotEndBack"]->Draw(hdc);
		}
	}
}
void KirbyShot::Leave()
{
}
void KirbyShot::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyShot::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyShot::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyShot::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyShot::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyShot::GetRect()
{
	return Rect(2000,100,0,0);
}
/////////////////////////////////////////////////////////////
// 죽었을때 동작
/////////////////////////////////////////////////////////////
KirbyDead::KirbyDead()
: update_dt(0), MoveAcc(0), update_delay(20), JumpAcc(30), update_dead(0), HitEnd(false)
, Stand(false), Wall(0), update_dt2(0), update_delay2(3500), Dead(false), Start(true), DieBGM(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyDead::~KirbyDead()
{
}
void KirbyDead::Enter()
{
}
void KirbyDead::Input(DWORD tick)
{
}
void KirbyDead::Update(DWORD tick)
{
	if(!Start)
	{
		if(update_dt > update_delay)
		{
			int count = update_dt/update_delay;
			for(int i = 0; i < count; i++)
			{
				JumpAcc -= 2;

				if(JumpAcc <= -14)
					JumpAcc = -14;

				KirbyPos.y -= JumpAcc;
			}
			update_dt %= update_delay;
		}
		update_dt += tick;

		if(update_dt2 > update_delay2)
		{
			Dead = true;

			update_dt2 %= update_delay2;
		}
		update_dt2 += tick;
	}

	if(Start)
	{
		if(!HitEnd)
		{
			SndDepot["HitEnd"]->Play();
			HitEnd = true;
		}

		if(update_dead > 1100)
			Start = false;

		update_dead += tick;
	}
	if(!(SndDepot["HitEnd"]->IsPlaying()) && !DieBGM && !Start && !SndDepot["DieBGMSet"]->IsPlaying())
	{
		SndDepot["DieBGMSet"]->Play();
	}
	SndDepot["Stage1"]->Stop();
	SndDepot["Stage2"]->Stop();

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(Start)
	{
		ImgDepot["KirbyDeadStart"]->SetRect(Rect(KirbyRect.left-2, KirbyRect.top-12, KirbyRect.right+4, KirbyRect.bottom));
	}
	else
	{
		AniDepot["KirbyDead"]->SetRect(Rect(KirbyRect.left-2, KirbyRect.top-12, KirbyRect.right+4, KirbyRect.bottom));
		AniDepot["KirbyDead"]->Update(tick);
	}
}
void KirbyDead::Draw(HDC hdc)
{
	if(Start)
	{
		ImgDepot["KirbyDeadStart"]->Draw(hdc);
	}
	else
	{
		AniDepot["KirbyDead"]->Draw(hdc);
	}
}
void KirbyDead::Leave()
{
}
void KirbyDead::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyDead::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyDead::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyDead::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyDead::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyDead::GetRect()
{
	if(!Dead)
		return Rect(0,0,0,1900);
	else
	{
		return Rect(0,0,0,2000);
	}
}
void KirbyDead::Reset()
{
	Start = true;
	DieBGM = false;
	HitEnd = false;
	Dead = false;
	update_dead = 0;
	update_dt2 = 0;
	JumpAcc = 30;
}
/////////////////////////////////////////////////////////////
// 먹는 동작
/////////////////////////////////////////////////////////////
KirbyEat::KirbyEat()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20)
, Sound(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyEat::~KirbyEat()
{
}
void KirbyEat::Enter()
{
}
void KirbyEat::Input(DWORD tick)
{

}
void KirbyEat::Update(DWORD tick)
{
	if(!Sound)
	{
		SndDepot["Eat"]->Play();
		Sound = true;
	}

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	AniDepot["KirbyEat"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-9, KirbyRect.right+24, KirbyRect.bottom));
	AniDepot["KirbyEatBack"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-9, KirbyRect.right+24, KirbyRect.bottom));

	if(!(AniDepot["KirbyEat"]->IsPlaying()) || !(AniDepot["KirbyEatBack"]->IsPlaying()))
	{
		Sound = false;
		AniDepot["KirbyEat"]->reset();
		AniDepot["KirbyEatBack"]->reset();
		pMachine->transition(_T("Idle"));
	}

	AniDepot["KirbyEat"]->Update(tick);
	AniDepot["KirbyEatBack"]->Update(tick);

}
void KirbyEat::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["KirbyEat"]->Draw(hdc);
	}
	else
	{
		AniDepot["KirbyEatBack"]->Draw(hdc);
	}
}
void KirbyEat::Leave()
{
}
void KirbyEat::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyEat::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyEat::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyEat::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyEat::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyEat::GetRect()
{
	if(!(AniDepot["KirbyEat"]->IsPlaying()) || !(AniDepot["KirbyEatBack"]->IsPlaying()))
		return Rect(0,0,0,4000);
	
	return Rect(0,0,0,0);
}
/////////////////////////////////////////////////////////////
// 별에 탄 동작
/////////////////////////////////////////////////////////////
KirbyStarIn::KirbyStarIn()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20)
, Sound(false), Start(true), Phase(0), Phase1_count(0)
, Phase2_count(0), Turn(true), TurnCount(0), Phase3_count(0)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyStarIn::~KirbyStarIn()
{
}
void KirbyStarIn::Enter()
{
}
void KirbyStarIn::Input(DWORD tick)
{

}
void KirbyStarIn::Update(DWORD tick)
{
	if(!Sound)
	{
		SndDepot["StarIn"]->Play();
		Sound = true;
	}

	if(update_dt > update_delay)
	{
		int count = update_dt / update_delay;
		for(int i = 0; i < count; i++)
		{
			if(Phase == 1)
			{
				MoveAcc += 1;

				if(MoveAcc >= 40)
					MoveAcc = 40;

				PlayerPos.x += MoveAcc;
				KirbyPos.x += 1;
				KirbyPos.y += 1;

				Phase1_count++;
			}
			else if(Phase == 2)
			{
				MoveAcc += 1;

				if(MoveAcc >= 40)
					MoveAcc = 40;

				PlayerPos.x += MoveAcc;
				if(Turn)
				{
					KirbyPos.y += 10;
				}
				else
				{
					KirbyPos.y -= 10;
				}
				KirbyPos.x -= 1;

				TurnCount++;
				Phase2_count++;
			}
			else if(Phase == 3)
			{
				MoveAcc += 1;

				if(MoveAcc >= 40)
					MoveAcc = 40;

				PlayerPos.x += MoveAcc;
				KirbyPos.x += 10;

				KirbyPos.y -= 30;

				Phase3_count++;
			}
			else if(Phase == 4)
			{
				KirbyPos.x += 2;
				KirbyPos.y += 5;

				if(KirbyPos.y >= 200)
				{
					KirbyPos.y = 200;
					pMachine->transition(_T("Jump"));
				}
			}
		}

		update_dt %= update_delay;
	}
	update_dt += tick;

	if(Phase1_count > 100 && Phase == 1)
	{
		Phase = 2;
	}
	if(Phase2_count > 100 && Phase == 2)
	{
		Phase = 3;
	}
	if(Phase3_count > 100 && Phase == 3)
	{
		KirbyPos.x = 0;
		KirbyPos.y = 0;
		Phase = 4;
	}
	if(TurnCount > 2)
	{
		Turn = !Turn;
		TurnCount = 0;
	}

	if(Start)
	{
		KirbyPos.y = 200;
		Start = false;
		Phase = 1;
	}

	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	AniDepot["KirbyStarIn"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-54, KirbyRect.right+30, KirbyRect.bottom));
	AniDepot["KirbyStarIn"]->Update(tick);

}
void KirbyStarIn::Draw(HDC hdc)
{
	AniDepot["KirbyStarIn"]->Draw(hdc);
}
void KirbyStarIn::Leave()
{
}
void KirbyStarIn::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyStarIn::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyStarIn::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyStarIn::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyStarIn::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyStarIn::GetRect()
{
	if(Phase != 4)
		return Rect(0,0,0,10000);
	else
		return Rect(0,0,0,20000);
}
/////////////////////////////////////////////////////////////
// 커비 댄스
/////////////////////////////////////////////////////////////
KirbyDance::KirbyDance()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20)
, Sound(false), Start(true), Phase(0), Phase1_count(0)
, Phase2_count(0), Turn1(true), TurnCount(0), Phase3_count(0)
, Phase4_count(0), Turn1Count(0), Phase5_count(0), Phase6_count(0)
, Phase7_count(0), Phase8_count(0)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 375;
	Zone[RightZone].left = Zone[RightZone].right - 375;
}
KirbyDance::~KirbyDance()
{
}
void KirbyDance::Enter()
{
}
void KirbyDance::Input(DWORD tick)
{

}
void KirbyDance::Update(DWORD tick)
{
	if(update_dt > update_delay)
	{
		int count = update_dt / update_delay;
		for(int i = 0; i < count; i++)
		{
			if(!Stand)
			{
				KirbyPos.y += 6;
			}

			if(Phase == 0 && Stand)
			{
				if(KirbyPos.x < 410 && KirbyPos.x > 390)
				{
					Phase = 1;
				}

				if(KirbyPos.x < 400)
				{
					BackPosition = false;
					KirbyPos.x += 2;
				}
				else if(KirbyPos.x > 400)
				{
					BackPosition = true;
					KirbyPos.x -= 2;
				}
			}
			else if(Phase == 1)
			{
				KirbyPos.x += 4;

				Phase1_count++;
			}
			else if(Phase == 2)
			{
				if(Turn1)
				{
					KirbyPos.y -= 15;
					Turn1Count++;
				}
				else
					KirbyPos.y += 15;

				if(Turn1Count > 12)
					Turn1 = false;

				Phase2_count++;
			}
			else if(Phase == 3)
			{
				KirbyPos.x -= 4;

				Phase3_count++;
			}
			else if(Phase == 4)
			{
				if(Turn1)
				{
					KirbyPos.y -= 15;
					Turn1Count++;
				}
				else
					KirbyPos.y += 15;

				if(Turn1Count > 12)
					Turn1 = false;

				Phase4_count++;
			}
			else if(Phase == 5)
			{
				if(Turn1)
				{
					KirbyPos.x -= 5;
					Turn1Count++;
				}
				else
					KirbyPos.x += 10;


				if(Turn1Count > 20)
					Turn1 = false;

				Phase5_count++;
			}
			else if(Phase == 6)
			{
				
				if(Turn1)
				{
					KirbyPos.y -= 15;
					Turn1Count++;
				}
				else
				{
					KirbyPos.y += 15;
					Turn1Count++;
				}

				KirbyPos.x -= 10;

				if(Turn1Count > 6)
				{
					Turn1 = !Turn1;
					Turn1Count = 0;
				}

				Phase6_count++;
			}
			else if(Phase == 7)
			{
				KirbyPos.y -= 20;
				KirbyPos.x += 11;

				Phase7_count++;
			}
			else if(Phase == 8)
			{
				KirbyPos.y += 10;

				Phase8_count++;
			}
		}

		update_dt %= update_delay;
	}
	update_dt += tick;

	if(Phase == 1 && !Sound)
	{
		SndDepot["Dance"]->Play();
		Sound = true;
	}

	if(Phase1_count > 40 && Phase == 1)
	{
		Phase = 2;
	}
	if(Phase2_count > 25 && Phase == 2)
	{
		Turn1 = true;
		Turn1Count = 0;
		Phase = 3;
	}
	if(Phase3_count > 40 && Phase == 3)
	{
		Phase = 4;
	}
	if(Phase4_count > 25 && Phase == 4)
	{
		Turn1 = true;
		Turn1Count = 0;
		Phase = 5;
	}
	if(Phase5_count > 40 && Phase == 5)
	{
		Turn1 = true;
		Turn1Count = 0;
		Phase = 6;
	}
	if(Phase6_count > 25 && Phase == 6)
	{
		Turn1 = true;
		Turn1Count = 0;
		Phase = 7;
	}
	if(Phase7_count > 15 && Phase == 7)
	{
		Phase = 8;
	}
	if(Phase8_count > 40 && Phase == 8)
	{
		Phase = 9;
	}


	if (pMachine)
		dynamic_cast<Kirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(Phase == 0 && !Stand)
	{
		AniDepot["KirbyJumpEnd"]->Update(tick);
		AniDepot["KirbyJumpEndBack"]->Update(tick);
	}
	else if(Phase == 0 && Stand)
	{
		AniDepot["KirbyMove"]->Update(tick);
		AniDepot["KirbyMoveBack"]->Update(tick);
	}
	else if(Phase == 1)
	{
		AniDepot["KirbyRolling"]->Update(tick);
		if(!AniDepot["KirbyRolling"]->IsPlaying())
		{
			AniDepot["KirbyRolling"]->reset();
		}
	}
	else if(Phase == 2)
	{
		AniDepot["KirbyDead"]->Update(tick);		
	}
	else if(Phase == 3)
	{
		AniDepot["KirbyRollingBack"]->Update(tick);
		if(!AniDepot["KirbyRollingBack"]->IsPlaying())
		{
			AniDepot["KirbyRollingBack"]->reset();
		}
	}
	else if(Phase == 4)
	{
		AniDepot["KirbyDead"]->Update(tick);		
	}
	else if(Phase == 6 || Phase == 7)
	{
		AniDepot["KirbyDead"]->Update(tick);	
	}
	else if(Phase == 8)
	{
		AniDepot["KirbyRolling"]->Update(tick);
		if(!AniDepot["KirbyRolling"]->IsPlaying())
		{
			AniDepot["KirbyRolling"]->reset();
		}
	}

}
void KirbyDance::Draw(HDC hdc)
{
	if(Phase == 0 && !Stand)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyJumpEnd"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
			AniDepot["KirbyJumpEnd"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyJumpEndBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));
			AniDepot["KirbyJumpEndBack"]->Draw(hdc);
		}
	}
	else if (Phase == 0 && Stand)
	{
		if(!BackPosition)
		{
			AniDepot["KirbyMove"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
			AniDepot["KirbyMove"]->Draw(hdc);
		}
		else
		{
			AniDepot["KirbyMoveBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));
			AniDepot["KirbyMoveBack"]->Draw(hdc);
		}
	}
	else if(Phase == 1)
	{
		AniDepot["KirbyRolling"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
		AniDepot["KirbyRolling"]->Draw(hdc);
	}
	else if(Phase == 2)
	{
		AniDepot["KirbyDead"]->SetRect(Rect(KirbyRect.left-2, KirbyRect.top-12, KirbyRect.right+4, KirbyRect.bottom));
		AniDepot["KirbyDead"]->Draw(hdc);
	}
	else if(Phase == 3)
	{
		AniDepot["KirbyRollingBack"]->SetRect(Rect(KirbyRect.left-5, KirbyRect.top, KirbyRect.right, KirbyRect.bottom));
		AniDepot["KirbyRollingBack"]->Draw(hdc);
	}
	else if(Phase == 4)
	{
		AniDepot["KirbyDead"]->SetRect(Rect(KirbyRect.left-2, KirbyRect.top-12, KirbyRect.right+4, KirbyRect.bottom));
		AniDepot["KirbyDead"]->Draw(hdc);
	}
	else if(Phase == 5)
	{
		if(Turn1)
		{
			ImgDepot["KirbyBreakBack"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
			ImgDepot["KirbyBreakBack"]->Draw(hdc);
		}
		else
		{
			ImgDepot["KirbyBreak"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
			ImgDepot["KirbyBreak"]->Draw(hdc);
		}
	}
	else if(Phase == 6 || Phase == 7)
	{
		AniDepot["KirbyDead"]->SetRect(Rect(KirbyRect.left-2, KirbyRect.top-12, KirbyRect.right+4, KirbyRect.bottom));
		AniDepot["KirbyDead"]->Draw(hdc);
	}
	else if(Phase == 8)
	{
		AniDepot["KirbyRolling"]->SetRect(Rect(KirbyRect.left, KirbyRect.top, KirbyRect.right+5, KirbyRect.bottom));
		AniDepot["KirbyRolling"]->Draw(hdc);
	}
	else if(Phase == 9)
	{
		ImgDepot["KirbyDanceEnd"]->SetRect(Rect(KirbyRect.left, KirbyRect.top - 15, KirbyRect.right, KirbyRect.bottom));
		ImgDepot["KirbyDanceEnd"]->Draw(hdc);
	}
}
void KirbyDance::Leave()
{
}
void KirbyDance::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void KirbyDance::GetState(const BYTE& wl)
{
	Wall = wl;
}
void KirbyDance::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void KirbyDance::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void KirbyDance::AniEnter(Animation* fr, Animation* bk)
{
}
Rect KirbyDance::GetRect()
{
	if(Phase == 9 && !SndDepot["Dance"]->IsPlaying())
	{
		Phase = 0;
		Phase8_count = 0;
		Phase7_count = 0;
		Phase6_count = 0;
		Phase5_count = 0;
		Phase4_count = 0;
		Phase3_count = 0;
		Phase2_count = 0;
		Phase1_count = 0;
		return Rect(5555,0,0,0);
	}
	return Rect(0,0,0,0);
}