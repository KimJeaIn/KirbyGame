#include "DanceStar.h"

DanceStar::DanceStar(const Point& pt)
: StarPos(pt), Del(false), MoveEnemie(0)
, BBox(NULL)
{
	StarRect.left = StarPos.x- 48/2;
	StarRect.top = StarPos.y - 48/2;
	StarRect.right = StarRect.left + 48;
	StarRect.bottom = StarRect.top + 48;

	SquareBox* pBox = new SquareBox;

	pBox->SetRect(StarRect);

	BBox = pBox;
}
DanceStar::~DanceStar()
{
}

void DanceStar::Input(DWORD)
{
}
void DanceStar::Update(DWORD tick)
{
	if(!Del)
	{
		StarRect.left = StarPos.x- 48/2;
		StarRect.top = StarPos.y - 48/2;
		StarRect.right = StarRect.left + 48;
		StarRect.bottom = StarRect.top + 48;

		AniDepot["KirbyStar"]->SetRect(StarRect);
		AniDepot["KirbyStar"]->Update(tick);
	}
}
void DanceStar::Draw(HDC hdc)
{
	if(!Del)
	{
		AniDepot["KirbyStar"]->Draw(hdc);
	}
}

BYTE DanceStar::ReturnEff()
{
	return 200;
}
Rect DanceStar::GetRect()
{
	return StarRect;
}
bool DanceStar::GetBack()
{
	return true;
}
void DanceStar::SetPoint(const Point&)
{
}
bool DanceStar::ReturnDel()
{
	return Del;
}
void DanceStar::SetDrain(const bool&, const Point&)
{
}
void DanceStar::SetState(const bool& st, const BYTE& Wa)
{
}
void DanceStar::SetDel(const bool& de)
{
	Del = de;
}
BoundaryBox* DanceStar::ReturnBBox() const
{
	return BBox;
}
void DanceStar::SetPlayerPos(const LONG& px)
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