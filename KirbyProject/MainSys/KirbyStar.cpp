#include "KirbyStar.h"

KirbyStar::KirbyStar(const Point& pt)
: StarPos(pt), Del(false), MoveEnemie(0)
, BBox(NULL)
{
	StarRect.left = StarPos.x- 96/2;
	StarRect.top = StarPos.y - 96/2;
	StarRect.right = StarRect.left + 96;
	StarRect.bottom = StarRect.top + 96;

	SquareBox* pBox = new SquareBox;

	pBox->SetRect(StarRect);

	BBox = pBox;
}
KirbyStar::~KirbyStar()
{
}

void KirbyStar::Input(DWORD)
{
}
void KirbyStar::Update(DWORD tick)
{
	if(!Del)
	{
		StarRect.left = StarPos.x- 96/2;
		StarRect.top = StarPos.y - 96/2;
		StarRect.right = StarRect.left + 96;
		StarRect.bottom = StarRect.top + 96;

		AniDepot["KirbyStar"]->SetRect(StarRect);
		AniDepot["KirbyStar"]->Update(tick);
	}
}
void KirbyStar::Draw(HDC hdc)
{
	if(!Del)
	{
		AniDepot["KirbyStar"]->Draw(hdc);
	}
}

BYTE KirbyStar::ReturnEff()
{
	return 100;
}
Rect KirbyStar::GetRect()
{
	return StarRect;
}
bool KirbyStar::GetBack()
{
	return true;
}
void KirbyStar::SetPoint(const Point&)
{
}
bool KirbyStar::ReturnDel()
{
	return Del;
}
void KirbyStar::SetDrain(const bool&, const Point&)
{
}
void KirbyStar::SetState(const bool& st, const BYTE& Wa)
{
}
void KirbyStar::SetDel(const bool& de)
{
	Del = de;
}
BoundaryBox* KirbyStar::ReturnBBox() const
{
	return BBox;
}
void KirbyStar::SetPlayerPos(const LONG& px)
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