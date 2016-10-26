#include "EnemiesCutter.h"

EnemiesCutter::EnemiesCutter(const Point& pt, const bool& bk)
: Hit(false), Del(false), CutterPos(pt), Back(bk), MoveEnemie(0)
, update_delay(5), update_dt(0), Turn(0), Return(false), Sound(false)
, BBox(NULL)
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

	CutterRect.left = CutterPos.x- 75/2;
	CutterRect.top = CutterPos.y - 48/2;
	CutterRect.right = CutterRect.left + 75;
	CutterRect.bottom = CutterRect.top + 48;

	pBox->SetRect(CutterRect);

	BBox = pBox;
}
EnemiesCutter::~EnemiesCutter()
{
	if (BBox)
		delete BBox;
}
void EnemiesCutter::Input(DWORD)
{
}
void EnemiesCutter::Update(DWORD tick)
{
	if(!Hit)
	{
		if(update_dt > update_delay)
		{
			int count = update_dt/update_delay;
			for(int i = 0; count > i; i++)
			{
				if(!Back)
				{
					CutterPos.x += 2;
				}
				else
				{
					CutterPos.x -= 2;
				}

				Turn++;

				if(Turn > 100 && !Return)
				{
					Back = !Back;
					Return = true;
				}
				if(Turn > 300)
					Hit = true;
			}
			update_dt %= update_delay;
		}
		update_dt += tick;
	}
	
	Rect tmp;

	if(!Sound && ::IntersectRect(&tmp, &GameGlobal.rcClient, &CutterRect))
	{
		SndDepot["ECutter"]->Play();
		Sound = true;
	}

	CutterRect.left = CutterPos.x- 75/2;
	CutterRect.top = CutterPos.y - 48/2;
	CutterRect.right = CutterRect.left + 75;
	CutterRect.bottom = CutterRect.top + 48;

	AniDepot["ECutterShot"]->Update(tick);

	if(Hit)
		Del = true;
}
void EnemiesCutter::Draw(HDC hdc)
{
	if(!Del)
	{
		if (BBox)
		{
			dynamic_cast<SquareBox*>(BBox)->SetRect(CutterRect);
			BBox->Draw(hdc);
		}
		AniDepot["ECutterShot"]->SetRect(CutterRect);
		AniDepot["ECutterShot"]->Draw(hdc);
	}
}
void EnemiesCutter::SetHit(const bool& h)
{
	Hit = h;
	if (BBox)
		BBox = NULL;
}
bool EnemiesCutter::GetDel() const
{
	return Del;
}
BoundaryBox* EnemiesCutter::ReturnBBox() const
{
	return BBox;
}
Rect EnemiesCutter::GetCutterRect() const
{
	return CutterRect;
}
LONG EnemiesCutter::GetTurn() const
{
	return Turn;
}
bool EnemiesCutter::GetBack() const
{
	return Back;
}
void EnemiesCutter::SetPlayerPos(const LONG& px)
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