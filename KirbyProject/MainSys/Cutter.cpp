#include "Cutter.h"

Cutter::Cutter(const Point& pt, const bool& bk)
: Hit(false), Del(false), CutterPos(pt), Back(bk), MoveEnemie(0)
, update_delay(5), update_dt(0), Turn(0), Return(false), Sound(false)
, BlockHit(false), BBox(NULL), update_dt2(0)
{
	if(!Back)
	{
		CutterPos.x += 20;
	}
	else
	{
		CutterPos.x -= 20;
	}
	SquareBox* pBox = new SquareBox;

	CutterRect.left = CutterPos.x- 84/2;
	CutterRect.top = CutterPos.y - 66/2;
	CutterRect.right = CutterRect.left + 84;
	CutterRect.bottom = CutterRect.top + 66;

	pBox->SetRect(CutterRect);

	BBox = pBox;
}
Cutter::~Cutter()
{
	if (BBox)
		delete BBox;
}
void Cutter::Input(DWORD tick)
{
	if(!BlockHit)
	{
		if(InputDevice[VK_UP])
		{
			CutterPos.y -= 3;
		}
		else if(InputDevice[VK_DOWN])
		{
			CutterPos.y += 3;
		}
	}
}
void Cutter::Update(DWORD tick)
{
	if(update_dt > update_delay)
	{
		int count = update_dt/update_delay;
		for(int i = 0; count > i; i++)
		{
			if(!BlockHit)
			{
				if(!Back)
				{
					CutterPos.x += 4;
				}
				else
				{
					CutterPos.x -= 4;
				}

				Turn++;

				if(Turn > 50 && !Return)
				{
					Back = !Back;
					Return = true;
				}
			}
			else
			{
				if(!Back)
				{
					CutterPos.x -= 2;
				}
				else
				{
					CutterPos.x += 2;
				}

				CutterPos.y += 1;
			}
		}
		update_dt %= update_delay;
	}
	update_dt += tick;

	Rect tmp;

	if(!Sound && ::IntersectRect(&tmp, &GameGlobal.rcClient, &CutterRect))
	{
		SndDepot["Cutter"]->Play();
		Sound = true;
	}

	CutterRect.left = CutterPos.x- 84/2;
	CutterRect.top = CutterPos.y - 66/2;
	CutterRect.right = CutterRect.left + 84;
	CutterRect.bottom = CutterRect.top + 66;

	AniDepot["CutterShot"]->Update(tick);

	if(BlockHit)
	{
		AniDepot["CutterShotEnd"]->Update(tick);
		if(!AniDepot["CutterShotEnd"]->IsPlaying())
		{
			AniDepot["CutterShotEnd"]->reset();
			BlockHit = false;
			Del = true;
		}
	}

	if(Hit)
	{
		Del = true;
	}
}
void Cutter::Draw(HDC hdc)
{
	if(!Del)
	{
		if (BBox)
		{
			dynamic_cast<SquareBox*>(BBox)->SetRect(CutterRect);
			BBox->Draw(hdc);
		}
		if(!Hit && !BlockHit)
		{
			AniDepot["CutterShot"]->SetRect(CutterRect);
			AniDepot["CutterShot"]->Draw(hdc);
		}
		else if(BlockHit)
		{
			AniDepot["CutterShotEnd"]->SetRect(CutterRect);
			AniDepot["CutterShotEnd"]->Draw(hdc);
		}
	}
}
void Cutter::SetHit(const bool& h)
{
	Hit = h;
	if (BBox)
		BBox = NULL;
}
void Cutter::SetBlockHit(const bool& h)
{
	BlockHit = h;
	if (BBox)
		BBox = NULL;
}
bool Cutter::GetDel() const
{
	return Del;
}
BoundaryBox* Cutter::ReturnBBox() const
{
	return BBox;
}
Rect Cutter::GetCutterRect() const
{
	return CutterRect;
}
LONG Cutter::GetTurn() const
{
	return Turn;
}
bool Cutter::GetBack() const
{
	return Back;
}
void Cutter::SetPlayerPos(const LONG& px)
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

	CutterPos.x -= MoveEnemie;

	MoveEnemie = px;
}