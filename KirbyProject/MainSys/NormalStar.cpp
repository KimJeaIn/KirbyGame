#include "NormalStar.h"

NormalStar::NormalStar(const Point& pt, const bool& bk)
: Efficacy(50), update_dt(0), update_delay(30)
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
NormalStar::~NormalStar()
{
	if (BBox)
		delete BBox;
}
void NormalStar::Input(DWORD)
{
}

void NormalStar::Update(DWORD tick)
{
	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; i < count; i++)
		{
			if(!Drain)
			{
				if(!Stand)
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
				}

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
		JumpAcc = 0;
		if(Sound)
		{
			SndDepot["BoundStar"]->Play();
			Sound = false;
		}
	}

	if(DelCount > 100 && !Drain)
		End = true;

	if(!End)
		AniDepot["StarItem2"]->Update(tick);
	else
		AniDepot["StarShotEnd"]->Update(tick);

	if(!AniDepot["StarShotEnd"]->IsPlaying())
		Del = true;

	if(Del)
		AniDepot["StarShotEnd"]->reset();
}
void NormalStar::Draw(HDC hdc)
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
		AniDepot["StarItem2"]->SetRect(StarRect);
		AniDepot["StarItem2"]->Draw(hdc);
	}
	else
	{
		AniDepot["StarShotEnd"]->SetRect(StarRect);
		AniDepot["StarShotEnd"]->Draw(hdc);
	}
}

BYTE NormalStar::ReturnEff()
{
	return Efficacy;
}
Rect NormalStar::GetRect()
{
	return StarRect;
}
bool NormalStar::ReturnDel()
{
	return Del;
}
void NormalStar::SetState(const bool& st, const BYTE& wa)
{
	Stand = st;
	Wall = wa;
}
BoundaryBox* NormalStar::ReturnBBox() const
{
	return BBox;
}
bool NormalStar::GetBack()
{
	return Back;
}
void NormalStar::SetPoint(const Point& pt)
{
	StarPos.y = pt.y;
}
void NormalStar::SetDrain(const bool& dr, const Point& pt)
{
	origin = StarPos;
	pos = StarPos;

	Vector tmppt = pt;

	dir = tmppt - origin;

	KirbyPos = pt;

	Drain = dr;
}
void NormalStar::SetPlayerPos(const LONG& px)
{
	
}
void NormalStar::SetDel(const bool& de)
{
	Del = de;
}