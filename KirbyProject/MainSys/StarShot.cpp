#include "StarShot.h"

StarShot::StarShot(const Point& pt, const bool& bk)
: Hit(false), Del(false), StarPos(pt), Back(bk)
, update_delay(5), update_dt(0), StarShotEnd(false)
, BBox(NULL)
{
	if(!Back)
	{
		StarPos.x += 40;
	}
	else
	{
		StarPos.x -= 40;
	}
	SquareBox* pBox = new SquareBox;

	StarRect.left = StarPos.x- 70/2;
	StarRect.top = StarPos.y - 70/2;
	StarRect.right = StarRect.left + 70;
	StarRect.bottom = StarRect.top + 70;

	pBox->SetRect(Rect(StarRect.left - 5, StarRect.top - 5, StarRect.right + 5, StarRect.bottom + 5));

	BBox = pBox;
}
StarShot::~StarShot()
{
	if (BBox)
		delete BBox;
}
void StarShot::Input(DWORD)
{
}
void StarShot::Update(DWORD tick)
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
					StarPos.x += 4;
				}
				else
				{
					StarPos.x -= 4;
				}
			}
			update_dt %= update_delay;
		}
		update_dt += tick;
	}

	StarRect.left = StarPos.x- 70/2;
	StarRect.top = StarPos.y - 70/2;
	StarRect.right = StarRect.left + 70;
	StarRect.bottom = StarRect.top + 70;

	if(!Hit)
		AniDepot["StarShot"]->Update(tick);
	else
	{
		if(!StarShotEnd)
		{
			SndDepot["StarShotEnd"]->Play();
			StarShotEnd = true;
		}
		AniDepot["StarShotEnd"]->Update(tick);
	}

	if(!(AniDepot["StarShotEnd"]->IsPlaying()))
		Del = true;
}
void StarShot::Draw(HDC hdc)
{
	if(!Del)
	{
		if (BBox)
		{
			dynamic_cast<SquareBox*>(BBox)->SetRect(Rect(StarRect.left - 5, StarRect.top - 5, StarRect.right + 5, StarRect.bottom + 5));
			BBox->Draw(hdc);
		}

		if(!Hit)
		{
			AniDepot["StarShot"]->SetRect(StarRect);
			AniDepot["StarShot"]->Draw(hdc);
		}
		else
		{
			AniDepot["StarShotEnd"]->SetRect(StarRect);
			AniDepot["StarShotEnd"]->Draw(hdc);
		}
	}
}
void StarShot::SetHit(const bool& h)
{
	Hit = h;
	if(BBox)
		BBox = NULL;
}
bool StarShot::GetDel() const
{
	return Del;
}
BoundaryBox* StarShot::ReturnBBox() const
{
	return BBox;
}
Rect StarShot::GetStarRect() const
{
	return StarRect;
}