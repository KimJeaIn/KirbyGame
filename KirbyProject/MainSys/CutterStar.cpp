#include "CutterStar.h"

CutterStar::CutterStar(const Point& pt, const bool& bk)
: Efficacy(10), update_dt(0), update_delay(30)
, JumpAcc(15), Back(!bk), StarPos(pt) 
, Stand(false), DelCount(0), End(false)
, Del(false), Sound(true), Drain(false)
, MoveAcc(0), Acc(0), MoveEnemie(0)
, BBox(NULL)
{	
	StarRect.left = StarPos.x- 70/2;
	StarRect.top = StarPos.y - 70/2;
	StarRect.right = StarRect.left + 70;
	StarRect.bottom = StarRect.top + 70;

	if(!Back)
	{
		StarPos.x += 40;
	}
	else
	{
		StarPos.x -= 40;
	}
	SquareBox* pBox = new SquareBox;

	pBox->SetRect(StarRect);

	BBox = pBox;
}
CutterStar::~CutterStar()
{
	if (BBox)
		delete BBox;
}
void CutterStar::Input(DWORD)
{
}

void CutterStar::Update(DWORD tick)
{
	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; i < count; i++)
		{
			if(!Drain)
			{
				if(!Back)
				{
					StarPos.x += 2;
				}
				else
				{
					StarPos.x -= 2;
				}
				JumpAcc -= 1;

				if(JumpAcc < -10)
					JumpAcc = -10;

				StarPos.y -= JumpAcc;

				DelCount++;
			}
			else
			{
				Acc++;

				MoveAcc += Acc;

				if(MoveAcc > 30)
					MoveAcc = 30;

				pos = pos + dir.normalize() * MoveAcc;

				StarPos.x = pos.x;
				StarPos.y = pos.y;
			}
		}

		update_dt %= update_delay;
	}
	update_dt += tick;

	if(Stand)
	{
		JumpAcc = 15;
		if(Sound)
		{
			SndDepot["BoundStar"]->Play();
			Sound = false;
		}
	}
	else
	{
		Sound = true;
	}
	if((Wall == 1 || Wall == 2) && !Drain)
	{
		Back = !Back;
	}

	if(DelCount > 500 && !Drain)
		End = true;

	if(!End)
		AniDepot["StarItem"]->Update(tick);
	else
		AniDepot["StarShotEnd"]->Update(tick);

	if(!AniDepot["StarShotEnd"]->IsPlaying())
		Del = true;

	if(Del)
		AniDepot["StarShotEnd"]->reset();
}
void CutterStar::Draw(HDC hdc)
{
	StarRect.left = StarPos.x- 70/2;
	StarRect.top = StarPos.y - 70/2;
	StarRect.right = StarRect.left + 70;
	StarRect.bottom = StarRect.top + 70;

	if (BBox)
	{
		dynamic_cast<SquareBox*>(BBox)->SetRect(StarRect);
		BBox->Draw(hdc);
	}

	if(!End)
	{
		AniDepot["StarItem"]->SetRect(StarRect);
		AniDepot["StarItem"]->Draw(hdc);
	}
	else
	{
		AniDepot["StarShotEnd"]->SetRect(StarRect);
		AniDepot["StarShotEnd"]->Draw(hdc);
	}
}

BYTE CutterStar::ReturnEff()
{
	return Efficacy;
}
Rect CutterStar::GetRect()
{
	return StarRect;
}
bool CutterStar::ReturnDel()
{
	return Del;
}
void CutterStar::SetState(const bool& st, const BYTE& wa)
{
	Stand = st;
	Wall = wa;
}
BoundaryBox* CutterStar::ReturnBBox() const
{
	return BBox;
}
bool CutterStar::GetBack()
{
	return Back;
}
void CutterStar::SetPoint(const Point& pt)
{
	StarPos.y = pt.y;
}
void CutterStar::SetDrain(const bool& dr, const Point& pt)
{
	origin = StarPos;
	pos = StarPos;

	Vector tmppt = pt;

	dir = tmppt - origin;

	KirbyPos = pt;

	Drain = dr;
}
void CutterStar::SetPlayerPos(const LONG& px)
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

	StarPos.x -= MoveEnemie;

	MoveEnemie = px;
}
void CutterStar::SetDel(const bool& de)
{
	Del = de;
}