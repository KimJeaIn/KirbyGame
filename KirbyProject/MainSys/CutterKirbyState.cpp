#include "CutterKirbyState.h"

/////////////////////////////////////////////////////////////
// 대기 동작
/////////////////////////////////////////////////////////////
CutterKirbyIdle::CutterKirbyIdle()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 385;
	Zone[RightZone].left = Zone[RightZone].right - 385;
}
CutterKirbyIdle::~CutterKirbyIdle()
{
}
void CutterKirbyIdle::Enter()
{
	srand((unsigned)time(NULL));

	ImgDepot["CutterKirbyStd"]->SetRect(KirbyRect);
	ImgDepot["CutterKirbyStdBack"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyStdEye"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyStdEyeBack"]->SetRect(KirbyRect);
}
void CutterKirbyIdle::Input(DWORD tick)
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
	if(InputDevice.OnClick('X'))
	{
		pMachine->transition(_T("Shot"));
	}
}
void CutterKirbyIdle::Update(DWORD tick)
{
	std::wostringstream oss;
	oss << _T("IdleState")<< _T("\n");

	::OutputDebugString(oss.str().c_str());

	if (pMachine)
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!Stand)
	{
		pMachine->transition(_T("Landing"));
	}

	ImgDepot["CutterKirbyStd"]->SetRect(Rect(KirbyRect.left-3, KirbyRect.top-18, KirbyRect.right+6, KirbyRect.bottom));
	AniDepot["CutterKirbyStdEye"]->SetRect(Rect(KirbyRect.left-3, KirbyRect.top-18, KirbyRect.right+6, KirbyRect.bottom));
	ImgDepot["CutterKirbyStdBack"]->SetRect(Rect(KirbyRect.left-6, KirbyRect.top-18, KirbyRect.right+3, KirbyRect.bottom));
	AniDepot["CutterKirbyStdEyeBack"]->SetRect(Rect(KirbyRect.left-6, KirbyRect.top-18, KirbyRect.right+3, KirbyRect.bottom));

	AniDepot["CutterKirbyStdEye"]->Update(tick);
	AniDepot["CutterKirbyStdEye"]->ResetAni(tick, rand()%5000 + 1000);
	AniDepot["CutterKirbyStdEyeBack"]->Update(tick);
	AniDepot["CutterKirbyStdEyeBack"]->ResetAni(tick, rand()%5000 + 1000);
}
void CutterKirbyIdle::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		if(!(AniDepot["CutterKirbyStdEye"]->IsPlaying()))
			ImgDepot["CutterKirbyStd"]->Draw(hdc);
		else
			AniDepot["CutterKirbyStdEye"]->Draw(hdc);
	}
	else
	{
		if(!(AniDepot["CutterKirbyStdEyeBack"]->IsPlaying()))
			ImgDepot["CutterKirbyStdBack"]->Draw(hdc);
		else
			AniDepot["CutterKirbyStdEyeBack"]->Draw(hdc);
	}
}
void CutterKirbyIdle::Leave()
{
}
void CutterKirbyIdle::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyIdle::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyIdle::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyIdle::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyIdle::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyIdle::GetRect()
{
	return Rect(2000,0,0,0);
}
/////////////////////////////////////////////////////////////
// 걷기 동작
/////////////////////////////////////////////////////////////
CutterKirbyMove::CutterKirbyMove()
: update_dt(0), MoveAcc(0), update_delay(20)
, KeyPush(true), update_dt2(0), update_delay2(60)
, RightKey(false), Stand(false), Wall(0)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 385;
	Zone[RightZone].left = Zone[RightZone].right - 385;
}
CutterKirbyMove::~CutterKirbyMove()
{
}
void CutterKirbyMove::Enter()
{
	AniDepot["CutterKirbyMove"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyMoveBack"]->SetRect(KirbyRect);
}
void CutterKirbyMove::Input(DWORD tick)
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
	if(InputDevice.OnClick('X'))
	{
		pMachine->transition(_T("Shot"));
	}
}
void CutterKirbyMove::Update(DWORD tick)
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
				if(!BackPosition && ::IntersectRect(&tmp, &Zone[RightZone], &KirbyRect))
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
				else if(BackPosition && ::IntersectRect(&tmp, &Zone[LeftZone], &KirbyRect) && !(PtInRect(&Zone[LeftZone], PlayerPos)))
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
					if(BackPosition)
					{
						MoveAcc -= 1;
						if(Wall == 1)
							pMachine->transition(_T("Idle"));
						else
							PlayerPos.x -= MoveAcc;
						if(PlayerPos.x < 0)
							PlayerPos.x = 0;
					}
					else
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
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!Stand)
	{
		pMachine->transition(_T("Landing"));
	}

	// 애니메이션 업데이트
	AniDepot["CutterKirbyMove"]->SetRect(Rect(KirbyRect.left-4, KirbyRect.top-24, KirbyRect.right+8, KirbyRect.bottom));
	AniDepot["CutterKirbyMoveBack"]->SetRect(Rect(KirbyRect.left-8, KirbyRect.top-24, KirbyRect.right+4, KirbyRect.bottom));
	AniDepot["CutterKirbyMove"]->Update(tick);
	AniDepot["CutterKirbyMoveBack"]->Update(tick);
}
void CutterKirbyMove::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["CutterKirbyMove"]->Draw(hdc);
	}
	else
	{
		AniDepot["CutterKirbyMoveBack"]->Draw(hdc);
	}
}
void CutterKirbyMove::Leave()
{
}
void CutterKirbyMove::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyMove::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyMove::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyMove::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyMove::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyMove::GetRect()
{
	return Rect(2000,0,0,0);
}
void CutterKirbyMove::SetBossStage(const bool& b)
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
CutterKirbyRun::CutterKirbyRun()
: Break(false), update_dt(0), update_delay(20), MoveAcc(4)
, KeyPush(true), update_dt2(0), update_delay2(60), Stand(false), Wall(0)
, Run(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 385;
	Zone[RightZone].left = Zone[RightZone].right - 385;
}
CutterKirbyRun::~CutterKirbyRun()
{
}
void CutterKirbyRun::Enter()
{
	ImgDepot["CutterKirbyBreak"]->SetRect(KirbyRect);
	ImgDepot["CutterKirbyBreakBack"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyRun"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyRunBack"]->SetRect(KirbyRect);
}
void CutterKirbyRun::Input(DWORD)
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
	if(InputDevice.OnClick('X'))
	{
		Run = false;
		Break = false;
		MoveAcc = 4;
		pMachine->transition(_T("Shot"));
	}
}
void CutterKirbyRun::Update(DWORD tick)
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

	if(!Run)
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
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!Stand)
	{
		Run = false;
		Break = false;
		MoveAcc = 4;
		pMachine->transition(_T("Landing"));
	}

	// 애니메이션 업데이트
	ImgDepot["CutterKirbyBreak"]->SetRect(Rect(KirbyRect.left-6, KirbyRect.top-24, KirbyRect.right+12, KirbyRect.bottom));
	AniDepot["CutterKirbyRun"]->SetRect(Rect(KirbyRect.left-6, KirbyRect.top-24, KirbyRect.right+12, KirbyRect.bottom));

	ImgDepot["CutterKirbyBreakBack"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-24, KirbyRect.right+6, KirbyRect.bottom));
	AniDepot["CutterKirbyRunBack"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-24, KirbyRect.right+6, KirbyRect.bottom));

	AniDepot["CutterKirbyRun"]->Update(tick);

	AniDepot["CutterKirbyRunBack"]->Update(tick);
}
void CutterKirbyRun::Draw(HDC hdc)
{
	if(!Break)
	{
		if(!BackPosition)
		{
			AniDepot["CutterKirbyRun"]->Draw(hdc);
		}
		else
		{
			AniDepot["CutterKirbyRunBack"]->Draw(hdc);
		}
	}
	else
	{
		if(BackPosition)
		{
			ImgDepot["CutterKirbyBreak"]->Draw(hdc);
		}
		else
		{
			ImgDepot["CutterKirbyBreakBack"]->Draw(hdc);
		}
	}
}
void CutterKirbyRun::Leave()
{
}
void CutterKirbyRun::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyRun::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyRun::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyRun::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyRun::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyRun::GetRect()
{
	return Rect(2000,0,0,0);
}
void CutterKirbyRun::SetBossStage(const bool& b)
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
CutterKirbyJump::CutterKirbyJump()
: Rolling(false), update_dt(0), update_delay(20), MoveAcc(4)
, Stand(false), Wall(0), JumpEnd(false), Jump(false)
,JumpAcc(18), KeyPush(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 385;
	Zone[RightZone].left = Zone[RightZone].right - 385;
}
CutterKirbyJump::~CutterKirbyJump()
{
}
void CutterKirbyJump::Enter()
{
	ImgDepot["CutterKirbyJumpStart"]->SetRect(KirbyRect);
	ImgDepot["CutterKirbyJumpStartBack"]->SetRect(KirbyRect);

	AniDepot["CutterKirbyRolling"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyRollingBack"]->SetRect(KirbyRect);
}
void CutterKirbyJump::Input(DWORD)
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
		AniDepot["CutterKirbyRolling"]->reset();
		AniDepot["CutterKirbyRollingBack"]->reset();
		Rolling = false;
		JumpAcc = 18;
		Jump = false;
		pMachine->transition(_T("Float"));
	}
	if(InputDevice.OnClick('X'))
	{
		AniDepot["CutterKirbyRolling"]->reset();
		AniDepot["CutterKirbyRollingBack"]->reset();
		Rolling = false;
		JumpAcc = 18;
		Jump = false;
		pMachine->transition(_T("Shot"));
	}
}
void CutterKirbyJump::Update(DWORD tick)
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

	if(!Jump)
	{
		SndDepot["Jump"]->Play();
		Jump = true;
	}

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	// 애니메이션 업데이트
	ImgDepot["CutterKirbyJumpStart"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-27, KirbyRect.right+10, KirbyRect.bottom));
	ImgDepot["CutterKirbyJumpStartBack"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-27, KirbyRect.right+10, KirbyRect.bottom));

	AniDepot["CutterKirbyRolling"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-36, KirbyRect.right+10, KirbyRect.bottom));
	AniDepot["CutterKirbyRollingBack"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-36, KirbyRect.right+10, KirbyRect.bottom));
	if(Rolling)
	{
		AniDepot["CutterKirbyRolling"]->Update(tick);
		AniDepot["CutterKirbyRollingBack"]->Update(tick);
	}

	if(!(AniDepot["CutterKirbyRolling"]->IsPlaying()) || !(AniDepot["CutterKirbyRollingBack"]->IsPlaying()) && Rolling)
	{
		AniDepot["CutterKirbyRolling"]->reset();
		AniDepot["CutterKirbyRollingBack"]->reset();

		Rolling = false;
		JumpAcc = 18;
		Jump = false;
		pMachine->transition(_T("Landing"));
	}
}
void CutterKirbyJump::Draw(HDC hdc)
{
	if(!Rolling)
	{
		if(!BackPosition)
		{
			ImgDepot["CutterKirbyJumpStart"]->Draw(hdc);
		}
		else
		{
			ImgDepot["CutterKirbyJumpStartBack"]->Draw(hdc);
		}
	}
	if(Rolling)
	{
		if(!BackPosition)
		{
			AniDepot["CutterKirbyRolling"]->Draw(hdc);
		}
		else
		{
			AniDepot["CutterKirbyRollingBack"]->Draw(hdc);
		}
	}
}
void CutterKirbyJump::Leave()
{
}
void CutterKirbyJump::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyJump::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyJump::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyJump::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyJump::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyJump::GetRect()
{
	return Rect(2000,0,0,0);
}
void CutterKirbyJump::SetBossStage(const bool& b)
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
CutterKirbyLanding::CutterKirbyLanding()
: update_dt(0), update_delay(20), MoveAcc(4)
, Stand(false), Wall(0), Landing(false)
,JumpAcc(0), KeyPush(false), Land(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 385;
	Zone[RightZone].left = Zone[RightZone].right - 385;
}
CutterKirbyLanding::~CutterKirbyLanding()
{
}
void CutterKirbyLanding::Enter()
{
	AniDepot["CutterKirbyLanding"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyLandingBack"]->SetRect(KirbyRect);

	AniDepot["CutterKirbyJumpEnd"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyJumpEndBack"]->SetRect(KirbyRect);
}
void CutterKirbyLanding::Input(DWORD)
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
		AniDepot["CutterKirbyLanding"]->reset();
		AniDepot["CutterKirbyLandingBack"]->reset();
		Land = false;
		pMachine->transition(_T("Float"));
	}
	if(InputDevice.OnClick('X'))
	{
		JumpAcc = 0;
		Stand = false;
		Landing = false;
		AniDepot["CutterKirbyLanding"]->reset();
		AniDepot["CutterKirbyLandingBack"]->reset();
		Land = false;
		pMachine->transition(_T("Shot"));
	}
}
void CutterKirbyLanding::Update(DWORD tick)
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
		if(!Land)
		{
			SndDepot["Land"]->Play();
			Land = true;
		}
		Landing = true;
	}
	if(!(AniDepot["CutterKirbyLanding"]->IsPlaying()) && Landing)
	{
		JumpAcc = 0;
		Stand = false;
		Landing = false;
		AniDepot["CutterKirbyLanding"]->reset();
		AniDepot["CutterKirbyLandingBack"]->reset();
		Land = false;
		pMachine->transition(_T("Idle"));
	}

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	// 애니메이션 업데이트
	AniDepot["CutterKirbyLanding"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-6, KirbyRect.right+10, KirbyRect.bottom));
	AniDepot["CutterKirbyLandingBack"]->SetRect(Rect(KirbyRect.left-10, KirbyRect.top-6, KirbyRect.right+10, KirbyRect.bottom));

	AniDepot["CutterKirbyJumpEnd"]->SetRect(Rect(KirbyRect.left-4, KirbyRect.top-21, KirbyRect.right+6, KirbyRect.bottom));
	AniDepot["CutterKirbyJumpEndBack"]->SetRect(Rect(KirbyRect.left-6, KirbyRect.top-21, KirbyRect.right+4, KirbyRect.bottom));

	if(Landing)
	{
		AniDepot["CutterKirbyLanding"]->Update(tick);
		AniDepot["CutterKirbyLandingBack"]->Update(tick);
	}
	AniDepot["CutterKirbyJumpEnd"]->Update(tick);
	AniDepot["CutterKirbyJumpEndBack"]->Update(tick);
}
void CutterKirbyLanding::Draw(HDC hdc)
{
	if(!Landing)
	{
		if(!BackPosition)
		{
			AniDepot["CutterKirbyJumpEnd"]->Draw(hdc);
		}
		else
		{
			AniDepot["CutterKirbyJumpEndBack"]->Draw(hdc);
		}
	}
	else
	{
		if(!BackPosition)
		{
			AniDepot["CutterKirbyLanding"]->Draw(hdc);
		}
		else
		{
			AniDepot["CutterKirbyLandingBack"]->Draw(hdc);
		}
	}
}
void CutterKirbyLanding::Leave()
{
}
void CutterKirbyLanding::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyLanding::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyLanding::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyLanding::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyLanding::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyLanding::GetRect()
{
	return Rect(2000,0,0,0);
}
void CutterKirbyLanding::SetBossStage(const bool& b)
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
CutterKirbyFloat::CutterKirbyFloat()
: update_dt(0), update_delay(10), MoveAcc(4)
, Stand(false), Wall(0), Landing(false), FloatSound(false)
,JumpAcc(0), KeyPush(false), Float(false), KirbyUp(false)
,FloatAirSound(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 385;
	Zone[RightZone].left = Zone[RightZone].right - 385;
}
CutterKirbyFloat::~CutterKirbyFloat()
{
}
void CutterKirbyFloat::Enter()
{
	AniDepot["CutterKirbyFloatStart"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyFloatStartBack"]->SetRect(KirbyRect);

	AniDepot["CutterKirbyFloat"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyFloatBack"]->SetRect(KirbyRect);

	AniDepot["CutterKirbyFloatUp"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyFloatUpBack"]->SetRect(KirbyRect);

	AniDepot["CutterKirbyFloatEnd"]->SetRect(KirbyRect);
	AniDepot["CutterKirbyFloatEndBack"]->SetRect(KirbyRect);
}
void CutterKirbyFloat::Input(DWORD)
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
		if(!(AniDepot["CutterKirbyFloatStart"]->IsPlaying()) || !(AniDepot["CutterKirbyFloatStartBack"]->IsPlaying()))
		{
			KirbyUp = true;
			FloatSound = false;
		}
	}
	if(InputDevice.OnClick('X'))
	{
		if(!FloatAirSound)
		{
			SndDepot["FloatAir"]->Play();
			FloatAirSound = true;
		}
		MissileDepot.AirPush(KirbyPos, BackPosition);

		Landing = true;
	}
}
void CutterKirbyFloat::Update(DWORD tick)
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

			if(AniDepot["CutterKirbyFloatStart"]->IsPlaying() || AniDepot["CutterKirbyFloatStartBack"]->IsPlaying())
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


	if(!FloatSound)
	{
		SndDepot["Float"]->Play();
		FloatSound = true;
	}

	if(!(AniDepot["CutterKirbyFloatStart"]->IsPlaying()) || !(AniDepot["CutterKirbyFloatStartBack"]->IsPlaying()) && !KirbyUp && !Float)
	{
		Float = true;
	}
	if(Stand)
	{
		if(!FloatAirSound)
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

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	AniDepot["CutterKirbyFloatStart"]->SetRect(Rect(KirbyRect.left-4, KirbyRect.top - 33, KirbyRect.right+8, KirbyRect.bottom));
	AniDepot["CutterKirbyFloatStartBack"]->SetRect(Rect(KirbyRect.left-8, KirbyRect.top - 33, KirbyRect.right+4, KirbyRect.bottom));

	AniDepot["CutterKirbyFloat"]->SetRect(Rect(KirbyRect.left-8, KirbyRect.top - 39, KirbyRect.right+14, KirbyRect.bottom));
	AniDepot["CutterKirbyFloatBack"]->SetRect(Rect(KirbyRect.left-14, KirbyRect.top - 39, KirbyRect.right+8, KirbyRect.bottom));

	AniDepot["CutterKirbyFloatUp"]->SetRect(Rect(KirbyRect.left-8, KirbyRect.top - 39, KirbyRect.right+14, KirbyRect.bottom));
	AniDepot["CutterKirbyFloatUpBack"]->SetRect(Rect(KirbyRect.left-14, KirbyRect.top - 39, KirbyRect.right+8, KirbyRect.bottom));

	AniDepot["CutterKirbyFloatEnd"]->SetRect(Rect(KirbyRect.left-4, KirbyRect.top - 33, KirbyRect.right+8, KirbyRect.bottom));
	AniDepot["CutterKirbyFloatEndBack"]->SetRect(Rect(KirbyRect.left-8, KirbyRect.top - 33, KirbyRect.right+4, KirbyRect.bottom));

	if(!Float && !KirbyUp && !Stand && !Landing)
	{
		AniDepot["CutterKirbyFloatStart"]->Update(tick);
		AniDepot["CutterKirbyFloatStartBack"]->Update(tick);
	}
	if(Float && !Landing)
	{
		AniDepot["CutterKirbyFloat"]->Update(tick);
		AniDepot["CutterKirbyFloatBack"]->Update(tick);
	}
	if(KirbyUp && !Landing)
	{
		AniDepot["CutterKirbyFloatUp"]->Update(tick);
		AniDepot["CutterKirbyFloatUpBack"]->Update(tick);
	}
	if(Landing)
	{
		AniDepot["CutterKirbyFloatEnd"]->Update(tick);
		AniDepot["CutterKirbyFloatEndBack"]->Update(tick);
	}

	if(Landing && !(AniDepot["CutterKirbyFloatEnd"]->IsPlaying()) || !(AniDepot["CutterKirbyFloatEndBack"]->IsPlaying()))
	{
		AniDepot["CutterKirbyFloatStart"]->reset();
		AniDepot["CutterKirbyFloatStartBack"]->reset();
		AniDepot["CutterKirbyFloatUp"]->reset();
		AniDepot["CutterKirbyFloatUpBack"]->reset();
		AniDepot["CutterKirbyFloatEnd"]->reset();
		AniDepot["CutterKirbyFloatEndBack"]->reset();

		FloatAirSound = false;
		FloatSound = false;
		Landing = false;
		Stand = false;
		KirbyUp = false;
		Float = false;

		pMachine->transition(_T("Landing"));
	}
	if(!(AniDepot["CutterKirbyFloatUp"]->IsPlaying()) || !(AniDepot["CutterKirbyFloatUpBack"]->IsPlaying()) && KirbyUp)
	{
		KirbyUp = false;
		AniDepot["CutterKirbyFloatUp"]->reset();
		AniDepot["CutterKirbyFloatUpBack"]->reset();
		Float = true;
	}
}
void CutterKirbyFloat::Draw(HDC hdc)
{
	if(!Float && !KirbyUp && !Stand && !Landing)
	{
		if(!BackPosition)
		{
			AniDepot["CutterKirbyFloatStart"]->Draw(hdc);
		}
		else
		{
			AniDepot["CutterKirbyFloatStartBack"]->Draw(hdc);
		}
	}
	else if(Float && !Landing)
	{
		if(!BackPosition)
		{
			AniDepot["CutterKirbyFloat"]->Draw(hdc);
		}
		else
		{
			AniDepot["CutterKirbyFloatBack"]->Draw(hdc);
		}
	}
	else if(KirbyUp && !Landing)
	{
		if(!BackPosition)
		{
			AniDepot["CutterKirbyFloatUp"]->Draw(hdc);
		}
		else
		{
			AniDepot["CutterKirbyFloatUpBack"]->Draw(hdc);
		}
	}
	else if(Landing)
	{
		if(!BackPosition)
		{
			AniDepot["CutterKirbyFloatEnd"]->Draw(hdc);
		}
		else
		{
			AniDepot["CutterKirbyFloatEndBack"]->Draw(hdc);
		}
	}
}
void CutterKirbyFloat::Leave()
{
}
void CutterKirbyFloat::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyFloat::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyFloat::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyFloat::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyFloat::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyFloat::GetRect()
{
	return Rect(2000,0,0,0);
}
void CutterKirbyFloat::SetBossStage(const bool& b)
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
// 맞았을때 동작
/////////////////////////////////////////////////////////////
CutterKirbyHit::CutterKirbyHit()
: update_dt(0), MoveAcc(0), update_delay(20), JumpAcc(0)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20)
, Hit(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 385;
	Zone[RightZone].left = Zone[RightZone].right - 385;
}
CutterKirbyHit::~CutterKirbyHit()
{
}
void CutterKirbyHit::Enter()
{
}
void CutterKirbyHit::Input(DWORD tick)
{
	if(Wall == 1)
	{
		AniDepot["CutterKirbyHit"]->reset();
		AniDepot["CutterKirbyHitBack"]->reset();
		Hit = false;
		pMachine->transition(_T("Idle"));
	}
	if(Wall == 2)
	{
		AniDepot["CutterKirbyHit"]->reset();
		AniDepot["CutterKirbyHitBack"]->reset();
		Hit = false;
		pMachine->transition(_T("Idle"));
	}
}
void CutterKirbyHit::Update(DWORD tick)
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
					AniDepot["CutterKirbyHit"]->reset();
					AniDepot["CutterKirbyHitBack"]->reset();
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
					AniDepot["CutterKirbyHit"]->reset();
					AniDepot["CutterKirbyHitBack"]->reset();
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
					AniDepot["CutterKirbyHit"]->reset();
					AniDepot["CutterKirbyHitBack"]->reset();
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
					AniDepot["CutterKirbyHit"]->reset();
					AniDepot["CutterKirbyHitBack"]->reset();
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
	if(!Hit)
	{
		SndDepot["Hit"]->Play();
		Hit = true;
	}

	if(KirbyPos.x + 30 >= Zone[RightZone].right)
		KirbyPos.x = Zone[RightZone].right - 30;

	if (pMachine)
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	if(!(AniDepot["CutterKirbyHit"]->IsPlaying()) || !(AniDepot["CutterKirbyHitBack"]->IsPlaying()))
	{
		AniDepot["CutterKirbyHit"]->reset();
		AniDepot["CutterKirbyHitBack"]->reset();
		Hit = false;
		pMachine->transition(_T("Idle"));
	}

	AniDepot["CutterKirbyHit"]->SetRect(Rect(KirbyRect.left-4, KirbyRect.top-24, KirbyRect.right+8, KirbyRect.bottom));
	AniDepot["CutterKirbyHitBack"]->SetRect(Rect(KirbyRect.left-8, KirbyRect.top-24, KirbyRect.right+4, KirbyRect.bottom));

	AniDepot["CutterKirbyHit"]->Update(tick);
	AniDepot["CutterKirbyHitBack"]->Update(tick);
}
void CutterKirbyHit::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["CutterKirbyHit"]->Draw(hdc);
	}
	else
	{
		AniDepot["CutterKirbyHitBack"]->Draw(hdc);
	}
}
void CutterKirbyHit::Leave()
{
}
void CutterKirbyHit::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyHit::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyHit::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyHit::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyHit::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyHit::GetRect()
{
	return Rect(2000,0,0,0);
}
void CutterKirbyHit::SetBossStage(const bool& b)
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
// 커터 발사 동작
/////////////////////////////////////////////////////////////
CutterKirbyShot::CutterKirbyShot()
: update_dt(0), MoveAcc(0), update_delay(20)
, Stand(false), Wall(0), update_dt2(0), update_delay2(20)
, Shotcount(0)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 385;
	Zone[RightZone].left = Zone[RightZone].right - 385;
}
CutterKirbyShot::~CutterKirbyShot()
{
}
void CutterKirbyShot::Enter()
{
}
void CutterKirbyShot::Input(DWORD tick)
{

}
void CutterKirbyShot::Update(DWORD tick)
{

	if (pMachine)
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	AniDepot["CutterKirbyShot"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-14, KirbyRect.right+24, KirbyRect.bottom+4));
	AniDepot["CutterKirbyShotBack"]->SetRect(Rect(KirbyRect.left-24, KirbyRect.top-14, KirbyRect.right+12, KirbyRect.bottom+4));

	AniDepot["CutterKirbyShot"]->Update(tick);
	AniDepot["CutterKirbyShotBack"]->Update(tick);

	if(update_dt > 100)
	{
		if(Shotcount == 0)
		{
			MissileDepot.CutterPush(KirbyPos, BackPosition);
			Shotcount ++;
		}

		update_dt %= 100;
	}
	update_dt += tick;

	if(!(AniDepot["CutterKirbyShot"]->IsPlaying()) || !(AniDepot["CutterKirbyShotBack"]->IsPlaying()))
	{
		Shotcount = 0;
		Sound = false;
		AniDepot["CutterKirbyShot"]->reset();
		AniDepot["CutterKirbyShotBack"]->reset();
		pMachine->transition(_T("Idle"));
	}
}
void CutterKirbyShot::Draw(HDC hdc)
{
	if(!BackPosition)
	{
		AniDepot["CutterKirbyShot"]->Draw(hdc);
	}
	else
	{
		AniDepot["CutterKirbyShotBack"]->Draw(hdc);
	}
}
void CutterKirbyShot::Leave()
{
}
void CutterKirbyShot::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyShot::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyShot::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyShot::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyShot::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyShot::GetRect()
{
	return Rect(2000,0,0,0);
}
/////////////////////////////////////////////////////////////
// 죽었을때 동작
/////////////////////////////////////////////////////////////
CutterKirbyDead::CutterKirbyDead()
: update_dt(0), MoveAcc(0), update_delay(20), JumpAcc(30), update_dead(0), HitEnd(false)
, Stand(false), Wall(0), update_dt2(0), update_delay2(3500), Dead(false), Start(true), DieBGM(false)
{
	for(int i = 0; i < ZoneMax; i++)
	{
		Zone[i] = GameGlobal.rcClient;
	}
	Zone[LeftZone].right = Zone[LeftZone].left + 385;
	Zone[RightZone].left = Zone[RightZone].right - 385;
}
CutterKirbyDead::~CutterKirbyDead()
{
}
void CutterKirbyDead::Enter()
{
}
void CutterKirbyDead::Input(DWORD tick)
{
}
void CutterKirbyDead::Update(DWORD tick)
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

		if(update_dead > 1100)
			Start = false;

		update_dead += tick;
	}
	SndDepot["Stage1"]->Stop();
	SndDepot["Stage2"]->Stop();

	if (pMachine)
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

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
void CutterKirbyDead::Draw(HDC hdc)
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
void CutterKirbyDead::Leave()
{
}
void CutterKirbyDead::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyDead::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyDead::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyDead::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyDead::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyDead::GetRect()
{
	if(!Dead)
		return Rect(0,0,0,1900);
	else
	{
		return Rect(0,0,0,2000);
	}
}
void CutterKirbyDead::Reset()
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
// 별에 탄 동작
/////////////////////////////////////////////////////////////
CutterKirbyStarIn::CutterKirbyStarIn()
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
CutterKirbyStarIn::~CutterKirbyStarIn()
{
}
void CutterKirbyStarIn::Enter()
{
}
void CutterKirbyStarIn::Input(DWORD tick)
{

}
void CutterKirbyStarIn::Update(DWORD tick)
{
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
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

	AniDepot["KirbyStarIn"]->SetRect(Rect(KirbyRect.left-12, KirbyRect.top-54, KirbyRect.right+30, KirbyRect.bottom));
	AniDepot["KirbyStarIn"]->Update(tick);

}
void CutterKirbyStarIn::Draw(HDC hdc)
{
	AniDepot["KirbyStarIn"]->Draw(hdc);
}
void CutterKirbyStarIn::Leave()
{
}
void CutterKirbyStarIn::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyStarIn::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyStarIn::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyStarIn::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyStarIn::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyStarIn::GetRect()
{
	if(Phase != 4)
		return Rect(0,0,0,10000);
	else
		return Rect(0,0,0,20000);
}
/////////////////////////////////////////////////////////////
// 커비 댄스
/////////////////////////////////////////////////////////////
CutterKirbyDance::CutterKirbyDance()
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
CutterKirbyDance::~CutterKirbyDance()
{
}
void CutterKirbyDance::Enter()
{
}
void CutterKirbyDance::Input(DWORD tick)
{

}
void CutterKirbyDance::Update(DWORD tick)
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
				else if(KirbyPos.x < 410 && KirbyPos.x > 390)
				{
					Phase = 1;
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
		dynamic_cast<CutterKirby*>(pMachine)->Setposition(PlayerPos, KirbyPos, BackPosition);

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
void CutterKirbyDance::Draw(HDC hdc)
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
void CutterKirbyDance::Leave()
{
}
void CutterKirbyDance::SetPosition(const Point& ppt, const Point& kpt, const bool& back)
{
	PlayerPos = ppt;

	KirbyPos = kpt;

	BackPosition = back;

	KirbyRect.left = KirbyPos.x - KirbyWidth/2;
	KirbyRect.top = KirbyPos.y - KirbyHeight/2;
	KirbyRect.right = KirbyWidth + KirbyRect.left;
	KirbyRect.bottom = KirbyHeight + KirbyRect.top;
}
void CutterKirbyDance::GetState(const BYTE& wl)
{
	Wall = wl;
}
void CutterKirbyDance::GetStand(const bool& st, const bool& ub)
{
	Stand = st;
	UpBlock = ub;
}
void CutterKirbyDance::SetCharPoint(const Point& kpt)
{
	KirbyPos = kpt;
}
void CutterKirbyDance::AniEnter(Animation* fr, Animation* bk)
{
}
Rect CutterKirbyDance::GetRect()
{
	return Rect(0,0,0,0);
}