#include "AirShot.h"

AirShot::AirShot(const Point& pt, const bool& bk)
: Hit(false), Del(false), AirPos(pt), Back(bk)
, update_delay(5), update_dt(0), AirShotEnd(false)
, MoveEnemie(0), BBox(NULL)
{
	if(!Back)
	{
		AirPos.x += 30;
	}
	else
	{
		AirPos.x -= 30;
	}
	SquareBox* pBox = new SquareBox;

	AirRect.left = AirPos.x- 57/2;
	AirRect.top = AirPos.y - 57/2;
	AirRect.right = AirRect.left + 57;
	AirRect.bottom = AirRect.top + 57;

	pBox->SetRect(AirRect);

	BBox = pBox;
}
AirShot::~AirShot()
{
	if (BBox)
		delete BBox;
}
void AirShot::Input(DWORD)
{
}
void AirShot::Update(DWORD tick)
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
					AirPos.x += 3;
				}
				else
				{
					AirPos.x -= 3;
				}
			}
			update_dt %= update_delay;
		}
		update_dt += tick;
	}

	AirRect.left = AirPos.x- 57/2;
	AirRect.top = AirPos.y - 57/2;
	AirRect.right = AirRect.left + 57;
	AirRect.bottom = AirRect.top + 57;

	if(!Back)
	{
		AniDepot["AirShot"]->Update(tick);
	}
	else
	{
		AniDepot["AirShotBack"]->Update(tick);
	}

	if(!(AniDepot["AirShot"]->IsPlaying()) || !(AniDepot["AirShotBack"]->IsPlaying()))
		Del = true;
}
void AirShot::Draw(HDC hdc)
{
	if(!Back)
	{
		if(!Del)
		{
			if (BBox)
			{
				dynamic_cast<SquareBox*>(BBox)->SetRect(AirRect);
				BBox->Draw(hdc);
			}
			AniDepot["AirShot"]->SetRect(AirRect);
			AniDepot["AirShot"]->Draw(hdc);
		}
	}
	else
	{
		if(!Del)
		{
			if (BBox)
			{
				dynamic_cast<SquareBox*>(BBox)->SetRect(AirRect);
				BBox->Draw(hdc);
			}
			AniDepot["AirShotBack"]->SetRect(AirRect);
			AniDepot["AirShotBack"]->Draw(hdc);
		}
	}
}
void AirShot::SetHit(const bool& h)
{
	Hit = h;
	if (BBox)
		BBox = NULL;
}
bool AirShot::GetDel() const
{
	return Del;
}
BoundaryBox* AirShot::ReturnBBox() const
{
	return BBox;
}
Rect AirShot::GetAirRect() const
{
	return AirRect;
}
void AirShot::SetPlayerPos(const LONG& px)
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

	AirPos.x -= MoveEnemie;

	MoveEnemie = px;
}