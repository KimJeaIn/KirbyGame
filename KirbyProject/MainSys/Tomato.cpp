#include "Tomato.h"

Tomato::Tomato(const Point& pt)
: TomatoPos(pt), Del(false), MoveEnemie(0)
, BBox(NULL)
{
	TomatoRect.left = TomatoPos.x- 60/2;
	TomatoRect.top = TomatoPos.y - 58/2;
	TomatoRect.right = TomatoRect.left + 60;
	TomatoRect.bottom = TomatoRect.top + 58;

	SquareBox* pBox = new SquareBox;

	pBox->SetRect(TomatoRect);

	BBox = pBox;
}
Tomato::~Tomato()
{
}

void Tomato::Input(DWORD)
{
}
void Tomato::Update(DWORD tick)
{
	if(!Del)
	{
		TomatoRect.left = TomatoPos.x- 60/2;
		TomatoRect.top = TomatoPos.y - 58/2;
		TomatoRect.right = TomatoRect.left + 60;
		TomatoRect.bottom = TomatoRect.top + 58;
	}
}
void Tomato::Draw(HDC hdc)
{
	if(!Del)
	{
		ImgDepot["Tomato"]->SetRect(TomatoRect);
		ImgDepot["Tomato"]->Draw(hdc);
	}
}

BYTE Tomato::ReturnEff()
{
	return 70;
}
Rect Tomato::GetRect()
{
	return TomatoRect;
}
bool Tomato::GetBack()
{
	return true;
}
void Tomato::SetPoint(const Point&)
{
}
bool Tomato::ReturnDel()
{
	return Del;
}
void Tomato::SetDrain(const bool&, const Point&)
{
}
void Tomato::SetState(const bool& st, const BYTE& Wa)
{
}
void Tomato::SetDel(const bool& de)
{
	Del = de;
}
BoundaryBox* Tomato::ReturnBBox() const
{
	return BBox;
}
void Tomato::SetPlayerPos(const LONG& px)
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

	TomatoPos.x -= MoveEnemie;

	MoveEnemie = px;
}