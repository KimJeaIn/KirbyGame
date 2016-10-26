#include "Stage1-2.h"

Stage1_2::Stage1_2()
	:Direction(true), MoveBlock(0, 0)
{
	PlayerPos = KirbyBase.RetrunKirbyPos();
}
Stage1_2::~Stage1_2()
{
}
void Stage1_2::Draw(HDC hdc)
{
	BackGround.SetDrawPoint(MoveMap.x);
	BackGround.Draw(hdc);

	BlockDepot.Draw(hdc);
	EnemiesDepot.Draw(hdc);
}
void Stage1_2::Update(DWORD tick)
{
	BlockDepot.Update(MoveBlock.x, MoveBlock.y);
}
void Stage1_2::Load(HWND hWnd)
{
	// 적캐릭터 로드

	SndDepot["Stage1"]->Stop();
	SndDepot["Stage2"]->Stop();

	if(!(SndDepot["BossBattle"]->IsPlaying()))
		SndDepot["BossBattle"]->Play();

	BlockDepot.Clear();

	// 백그라운드 로드
	::GetClientRect(hWnd, &ClientRect);

	BackGround.Load(_T("Resource//image//Boss_BackGrounds.bmp"));
	Rect tmpbm = ClientRect;
	Size tmpSize = BackGround.GetBmSize();
	tmpbm.right = tmpSize.cx*3;
	tmpbm.top = tmpbm.bottom - (tmpSize.cy*3);
	BackGround.SetRect(tmpbm);

	// 블록1 로드

	Block* tmp = new Block;

	Rect tmpRc;

	tmp = new Block;
	
	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - BossBlock_y_size;
	tmpRc.bottom = tmpRc.top + BossBlock_y_size;
	tmpRc.right = BossBlock_x_size;

	tmp->Load(_T("Resource//image//Boss_Block.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0);

	BlockDepot.Push(tmp);
}
void Stage1_2::SetPlayerPos(const Point& pt, const Point& kt)
{
	PlayerPos = pt;
	KirbyPos = kt;
}