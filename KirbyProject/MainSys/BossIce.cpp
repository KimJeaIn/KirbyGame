#include "BossIce.h"

IceShot::IceShot(const Point& pt, const bool& bk)
: Hit(false), Del(false), IcePos(pt), Back(!bk)
, update_delay(30), update_dt(0), IceShotEnd(false)
, BBox(NULL), Size(30), Setting(0)
{
	if(!Back)
	{
		IcePos.x += 70;
	}
	else
	{
		IcePos.x -= 70;
	}
	SquareBox* pBox = new SquareBox;

	IceRect.left = IcePos.x;
	IceRect.bottom = IcePos.y;
	IceRect.right = IceRect.left + Size;
	IceRect.top = IceRect.bottom - Size;

	pBox->SetRect(IceRect);

	BBox = pBox;
}
IceShot::~IceShot()
{
	if (BBox)
		delete BBox;
}
void IceShot::Input(DWORD)
{
}
void IceShot::Update(DWORD tick)
{
	if(!Hit)
	{
		if(update_dt > update_delay)
		{
			int count = update_dt/update_delay;
			for(int i = 0; count > i; i++)
			{
				if(Setting < 44)
				{
					Setting++;
				}
				else
				{
					if(!Back)
					{
						IcePos.x += 8;
					}
					else
					{
						IcePos.x -= 8;
					}
				}
			}
			update_dt %= update_delay;
		}
		update_dt += tick;
	}
	if(Setting%5 == 1)
	{
		Size += 3;
	}

	if(IcePos.x - Size < 0 && Back)
	{
		Hit = true;
	}
	else if(IcePos.x + Size > GameGlobal.rcClient.right && !Back)
	{
		Hit = true;
	}

	if(!Back)
	{
		IceRect.left = IcePos.x;
		IceRect.bottom = IcePos.y;
		IceRect.right = IceRect.left + Size;
		IceRect.top = IceRect.bottom - Size;
	}
	else
	{
		IceRect.right = IcePos.x;
		IceRect.bottom = IcePos.y;
		IceRect.left = IceRect.right - Size;
		IceRect.top = IceRect.bottom - Size;
	}

	if(Hit && !Del)
	{
		if(!IceShotEnd)
		{
			SndDepot["StarShotEnd"]->Play();
			IceShotEnd = true;
		}
		AniDepot["StarShotEnd"]->Update(tick);
	}
	else
	{
		AniDepot["IceBlock"]->Update(tick);
	}

	if(!(AniDepot["StarShotEnd"]->IsPlaying()))
	{
		AniDepot["StarShotEnd"]->reset();
		Del = true;
	}
}
void IceShot::Draw(HDC hdc)
{
	if(!Del)
	{
		if (BBox)
		{
			dynamic_cast<SquareBox*>(BBox)->SetRect(IceRect);
			BBox->Draw(hdc);
		}

		if(!Hit)
		{
			AniDepot["IceBlock"]->SetRect(IceRect);
			AniDepot["IceBlock"]->Draw(hdc);
		}
		else
		{
			AniDepot["StarShotEnd"]->SetRect(IceRect);
			AniDepot["StarShotEnd"]->Draw(hdc);
		}
	}
}
void IceShot::SetHit(const bool& h)
{
	if(BBox)
		BBox = NULL;
}
bool IceShot::GetDel() const
{
	return Del;
}
BoundaryBox* IceShot::ReturnBBox() const
{
	return BBox;
}
Rect IceShot::GetIceRect() const
{
	return IceRect;
}
bool IceShot::GetBack() const
{
	return Back;
}




///////////////////////////////////
// 분노시 얼음발사
///////////////////////////////////

RageIceShot::RageIceShot(const Point& pt, const bool& bk)
: Hit(false), Del(false), IcePos(pt), Back(!bk)
, update_delay(15), update_dt(0), IceShotEnd(false)
, BBox(NULL), Size(30), Setting(0)
{
	if(!Back)
	{
		IcePos.x += 70;
	}
	else
	{
		IcePos.x -= 70;
	}
	SquareBox* pBox = new SquareBox;

	IceRect.left = IcePos.x;
	IceRect.bottom = IcePos.y;
	IceRect.right = IceRect.left + Size;
	IceRect.top = IceRect.bottom - Size;

	pBox->SetRect(IceRect);

	BBox = pBox;
}
RageIceShot::~RageIceShot()
{
	if (BBox)
		delete BBox;
}
void RageIceShot::Input(DWORD)
{
}
void RageIceShot::Update(DWORD tick)
{
	if(!Hit)
	{
		if(update_dt > update_delay)
		{
			int count = update_dt/update_delay;
			for(int i = 0; count > i; i++)
			{
				if(Setting < 44)
				{
					Setting++;
				}
				else
				{
					if(!Back)
					{
						IcePos.x += 8;
					}
					else
					{
						IcePos.x -= 8;
					}
				}
			}
			update_dt %= update_delay;
		}
		update_dt += tick;
	}
	if(Setting%5 == 1)
	{
		Size += 9;
	}

	if(IcePos.x - Size < 0 && Back)
	{
		Hit = true;
	}
	else if(IcePos.x + Size > GameGlobal.rcClient.right && !Back)
	{
		Hit = true;
	}

	if(!Back)
	{
		IceRect.left = IcePos.x;
		IceRect.bottom = IcePos.y;
		IceRect.right = IceRect.left + Size;
		IceRect.top = IceRect.bottom - Size;
	}
	else
	{
		IceRect.right = IcePos.x;
		IceRect.bottom = IcePos.y;
		IceRect.left = IceRect.right - Size;
		IceRect.top = IceRect.bottom - Size;
	}

	if(Hit && !Del)
	{
		if(!IceShotEnd)
		{
			SndDepot["StarShotEnd"]->Play();
			IceShotEnd = true;
		}
		AniDepot["StarShotEnd"]->Update(tick);
	}
	else
	{
		AniDepot["IceBlock"]->Update(tick);
	}

	if(!(AniDepot["StarShotEnd"]->IsPlaying()))
	{
		AniDepot["StarShotEnd"]->reset();
		Del = true;
	}
}
void RageIceShot::Draw(HDC hdc)
{
	if(!Del)
	{
		if (BBox)
		{
			dynamic_cast<SquareBox*>(BBox)->SetRect(IceRect);
			BBox->Draw(hdc);
		}

		if(!Hit)
		{
			AniDepot["IceBlock"]->SetRect(IceRect);
			AniDepot["IceBlock"]->Draw(hdc);
		}
		else
		{
			AniDepot["StarShotEnd"]->SetRect(IceRect);
			AniDepot["StarShotEnd"]->Draw(hdc);
		}
	}
}
void RageIceShot::SetHit(const bool& h)
{
	if(BBox)
		BBox = NULL;
}
bool RageIceShot::GetDel() const
{
	return Del;
}
BoundaryBox* RageIceShot::ReturnBBox() const
{
	return BBox;
}
Rect RageIceShot::GetIceRect() const
{
	return IceRect;
}
bool RageIceShot::GetBack() const
{
	return Back;
}