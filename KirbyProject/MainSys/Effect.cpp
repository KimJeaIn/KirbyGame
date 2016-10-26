#include "Effect.h"

Effect::Effect()
:update_dt(0), update_delay(20), count(0)
{
	//srand((unsigned)time(NULL));
	//Air.Load(_T("Resource//image//Kirby_base.bmp"), Rect(548,368,555,374));
	//Air.SetTransparent(RGB(207,176,255));
}
Effect::~Effect()
{
}
void Effect::Enter()
{
	
}
void Effect::Update(DWORD tick, const Point& pt)
{
	//if (update_dt > update_delay)
	//{
	//	pos = pos + dir.normalize() * 10;

	//	if (count > rand()%10 + 5)
	//	{
	//		SetTargetPosition(pt);
	//		count = 0;
	//	}
	//	LONG rsize = rand()%21 + 10;

	//	Rect tmp(pos, Size(rsize,rsize - 3));

	//	Air.SetRect(tmp);

	//	count++;

	//	update_dt -= update_delay;
	//}

	//update_dt += tick;

	AniDepot["DrainEffect"]->Update(tick);
	AniDepot["DrainEffectBack"]->Update(tick);
}
void Effect::Draw(HDC hdc)
{
	/*Air.Draw(hdc);*/
	if(!Back)
		AniDepot["DrainEffect"]->Draw(hdc);
	else
		AniDepot["DrainEffectBack"]->Draw(hdc);
}
void Effect::SetPosition(const Rect& rc, const bool& bk)
{
	Back = bk;
	Rect tmp = rc;
	Vector pt;

	if(Back)
	{
		tmp.right = tmp.left + 120;

		pt.x = float(rand()%120 + tmp.left);
		pt.y = float(rand()%tmp.height() + tmp.top);
	}
	else
	{
		tmp.left = tmp.right - 120;

		pt.x = float(rand()%120 + tmp.left);
		pt.y = float(rand()%tmp.height() + tmp.top);
	}
	AniDepot["DrainEffect"]->SetRect(rc);
	AniDepot["DrainEffectBack"]->SetRect(rc);

	origin = pt;
	pos = pt;
}
void Effect::SetTargetPosition(const Vector& pt)
{
	dir = pt - origin;

	pos = origin;
}