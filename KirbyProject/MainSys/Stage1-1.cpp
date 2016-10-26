#include "Stage1-1.h"

Stage1_1::Stage1_1()
	:Direction(true), MoveBlock(0, 0)
{
	PlayerPos = KirbyBase.RetrunKirbyPos();
}
Stage1_1::~Stage1_1()
{
}
void Stage1_1::Draw(HDC hdc)
{
	BackGround[0].SetDrawPoint(MoveMap.x);
	BackGround[0].Draw(hdc);

	if(MoveMap.x < 0)
	{
		BackGround[1].SetDrawPoint((BackGround[1].GetBmSize().cx) + MoveMap.x);
		BackGround[1].Draw(hdc);
	}
	else
	{
		BackGround[1].SetDrawPoint(-(BackGround[1].GetBmSize().cx) + MoveMap.x);
		BackGround[1].Draw(hdc);
	}

	BlockDepot.Draw(hdc);

	EnemiesDepot.Draw(hdc);
}
void Stage1_1::Update(DWORD tick)
{
	if(-MoveMap.x > (BackGround[1].GetBmSize().cx) || MoveMap.x > (BackGround[1].GetBmSize().cx))
		MoveMap.x = 0;

	if(PlayerPos.x < 0)
		MoveMap.x = 0;

	BlockDepot.Update(MoveBlock.x, MoveBlock.y);

	EnemiesDepot.Input(tick);
	EnemiesDepot.SetPlayerPos(PlayerPos.x);
	EnemiesDepot.SetKirbyPos(KirbyPos);
	EnemiesDepot.Update(tick);
}
void Stage1_1::Load(HWND hWnd)
{
// 적캐릭터 로드

	Enemies* Enemiestmp = new Enemies(Point(700,150));

	Enemiestmp->Load(1);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(1200,150));

	Enemiestmp->Load(1);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(2150,150));

	Enemiestmp->Load(1);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(2600,150));

	Enemiestmp->Load(1);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(2600,150));

	Enemiestmp->Load(3);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(3330,100));

	Enemiestmp->Load(2);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(3900,400));

	Enemiestmp->Load(2);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(4600,460));

	Enemiestmp->Load(1);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(5645,370));

	Enemiestmp->Load(2);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(6400,130));

	Enemiestmp->Load(2);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(6974,138));

	Enemiestmp->Load(2);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(7000,200));

	Enemiestmp->Load(3);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(7600,350));

	Enemiestmp->Load(3);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(8200,180));

	Enemiestmp->Load(1);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(8700,180));

	Enemiestmp->Load(3);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(8250,310));

	Enemiestmp->Load(1);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(8940,130));

	Enemiestmp->Load(2);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(9400,350));

	Enemiestmp->Load(3);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(9300,360));

	Enemiestmp->Load(2);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(9646,80));

	Enemiestmp->Load(1);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(10000,350));

	Enemiestmp->Load(3);

	EnemiesDepot.Push(Enemiestmp);

	Enemiestmp = new Enemies(Point(10600,310));

	Enemiestmp->Load(2);

	EnemiesDepot.Push(Enemiestmp);

	// 백그라운드 로드
	::GetClientRect(hWnd, &ClientRect);

	for(int i = 0; i < 2; i++)
	{
		BackGround[i].Load(_T("Resource//image//BackGrounds.bmp"));
		Rect tmpbm = ClientRect;
		Size tmpSize = BackGround[i].GetBmSize();
		tmpbm.right = tmpSize.cx;
		tmpbm.top = tmpbm.bottom - (tmpSize.cy);
		BackGround[i].SetRect(tmpbm);
	}

	// 블록1 로드

	Block* tmp = new Block;

	Rect tmpRc;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block1_y_size + 100;
	tmpRc.bottom = tmpRc.top + Block1_y_size;
	tmpRc.right = Block1_x_size;

	tmp->Load(_T("Resource//image//Block_1.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(25);

	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block4_y_size + 5;
	tmpRc.bottom = tmpRc.top + Block4_y_size;
	tmpRc.left = tmpRc.right + 1350;
	tmpRc.right = tmpRc.left + Block4_x_size;

	tmp->Load(_T("Resource//image//Block_4.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(285, 20, 20);
	BlockDepot.Push(tmp);


	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block6_y_size + 150;
	tmpRc.bottom = tmpRc.top + Block6_y_size;
	tmpRc.left = tmpRc.right + 180;
	tmpRc.right = tmpRc.left + Block6_x_size;

	tmp->Load(_T("Resource//image//Block_6.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(25, 20, 20);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block6_1_y_size - 150;
	tmpRc.bottom = tmpRc.top + Block6_1_y_size;
	tmpRc.left = tmpRc.right + 850;
	tmpRc.right = tmpRc.left + Block6_1_x_size;

	tmp->Load(_T("Resource//image//Block_6_1.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0, 10, 5, 45);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block3_y_size + 100;
	tmpRc.bottom = tmpRc.top + Block3_y_size;
	tmpRc.left = Block3_x_size + 100;
	tmpRc.right = tmpRc.left + Block3_x_size;

	tmp->Load(_T("Resource//image//Block_3.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(40, 30, 20);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block3_1_y_size - 430;
	tmpRc.bottom = tmpRc.top + Block3_1_y_size;
	tmpRc.left = Block3_1_x_size + 100;
	tmpRc.right = tmpRc.left + Block3_1_x_size;

	tmp->Load(_T("Resource//image//Block_3_1.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0, 30, 20, 38);
	BlockDepot.Push(tmp);
	

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_y_size - 235;
	tmpRc.bottom = tmpRc.top + Block7_1_y_size;
	tmpRc.left = tmpRc.right + 2760;
	tmpRc.right = tmpRc.left + Block7_1_x_size;

	tmp->Load(_T("Resource//image//Block_7_1.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(30);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_1_y_size + 83;
	tmpRc.bottom = tmpRc.top + Block7_1_1_y_size;
	tmpRc.left = tmpRc.right + 2760;
	tmpRc.right = tmpRc.left + Block7_1_1_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_1.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(135);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_y_size + 80;
	tmpRc.bottom = tmpRc.top + Block7_y_size;
	tmpRc.left = tmpRc.right + 2700 - (Block7_x_size/2);
	tmpRc.right = tmpRc.left + Block7_x_size;

	tmp->Load(_T("Resource//image//Block_7.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(51, 30);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_3_y_size + 83;
	tmpRc.bottom = tmpRc.top + Block7_1_3_y_size;
	tmpRc.left = tmpRc.right + 3485;
	tmpRc.right = tmpRc.left + Block7_1_3_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_3.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(417);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_2_y_size - 517;
	tmpRc.bottom = tmpRc.top + Block7_1_2_y_size;
	tmpRc.left = tmpRc.right + 3482;
	tmpRc.right = tmpRc.left + Block7_1_2_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_2.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_4_y_size - 207;
	tmpRc.bottom = tmpRc.top + Block7_1_4_y_size;
	tmpRc.left = tmpRc.right + 3623;
	tmpRc.right = tmpRc.left + Block7_1_4_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_4.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_5_y_size + 83;
	tmpRc.bottom = tmpRc.top + Block7_1_5_y_size;
	tmpRc.left = tmpRc.right + 3623;
	tmpRc.right = tmpRc.left + Block7_1_5_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_5.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(108);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_6_y_size - 462;
	tmpRc.bottom = tmpRc.top + Block7_1_6_y_size;
	tmpRc.left = tmpRc.right + 3731;
	tmpRc.right = tmpRc.left + Block7_1_6_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_6.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(10);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_7_y_size + 83;
	tmpRc.bottom = tmpRc.top + Block7_1_7_y_size;
	tmpRc.left = tmpRc.right + 3731;
	tmpRc.right = tmpRc.left + Block7_1_7_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_7.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(367);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_8_y_size - 275;
	tmpRc.bottom = tmpRc.top + Block7_1_8_y_size;
	tmpRc.left = tmpRc.right + 4226;
	tmpRc.right = tmpRc.left + Block7_1_8_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_8.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(10);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_9_y_size + 83;
	tmpRc.bottom = tmpRc.top + Block7_1_9_y_size;
	tmpRc.left = tmpRc.right + 4226;
	tmpRc.right = tmpRc.left + Block7_1_9_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_9.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(176);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_10_y_size - 275;
	tmpRc.bottom = tmpRc.top + Block7_1_10_y_size;
	tmpRc.left = tmpRc.right + 4420;
	tmpRc.right = tmpRc.left + Block7_1_10_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_10.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(13);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block7_1_11_y_size + 85;
	tmpRc.bottom = tmpRc.top + Block7_1_11_y_size;
	tmpRc.left = tmpRc.right + 4421;
	tmpRc.right = tmpRc.left + Block7_1_11_x_size;

	tmp->Load(_T("Resource//image//Block_7_1_11.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(95);
	BlockDepot.Push(tmp);

	//

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block8_y_size;
	tmpRc.bottom = tmpRc.top + Block8_y_size;
	tmpRc.left = tmpRc.right + 5000;
	tmpRc.right = tmpRc.left + Block8_x_size;

	tmp->Load(_T("Resource//image//Block_8.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(48);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block8_1_y_size + 250;
	tmpRc.bottom = tmpRc.top + Block8_1_y_size;
	tmpRc.left = tmpRc.right + 5590;
	tmpRc.right = tmpRc.left + Block8_1_x_size;

	tmp->Load(_T("Resource//image//Block_8_2.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(48);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block8_1_y_size;
	tmpRc.bottom = tmpRc.top + Block8_1_y_size;
	tmpRc.left = tmpRc.right + 5200;
	tmpRc.right = tmpRc.left + Block8_1_x_size;

	tmp->Load(_T("Resource//image//Block_8_1.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(48);
	BlockDepot.Push(tmp);

	/////////////////////////////////////////////////////
	// 추가된맵

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block10_y_size + 90;
	tmpRc.bottom = tmpRc.top + Block10_y_size;
	tmpRc.left = tmpRc.right + 6200;
	tmpRc.right = tmpRc.left + Block10_x_size;

	tmp->Load(_T("Resource//image//Block_10.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(45, 30, 15);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block10_1_y_size - 455;
	tmpRc.bottom = tmpRc.top + Block10_1_y_size;
	tmpRc.left = tmpRc.right + 6213;
	tmpRc.right = tmpRc.left + Block10_1_x_size;

	tmp->Load(_T("Resource//image//Block_10_1.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0, 15, 30, 45);
	BlockDepot.Push(tmp);

	
	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block10_1_y_size - 180;
	tmpRc.bottom = tmpRc.top + Block10_1_y_size;
	tmpRc.left = tmpRc.right + 6550;
	tmpRc.right = tmpRc.left + Block10_1_x_size;

	tmp->Load(_T("Resource//image//Block_10_1.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0, 15, 30, 45);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block12_y_size + 100;
	tmpRc.bottom = tmpRc.top + Block12_y_size;
	tmpRc.left = tmpRc.right + 7242;
	tmpRc.right = tmpRc.left + Block12_x_size;

	tmp->Load(_T("Resource//image//Block_12.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(35, 0, 20);
	BlockDepot.Push(tmp);


	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block11_y_size + 100;
	tmpRc.bottom = tmpRc.top + Block11_y_size;
	tmpRc.left = tmpRc.right + 6900;
	tmpRc.right = tmpRc.left + Block11_x_size;

	tmp->Load(_T("Resource//image//Block_11.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(45, 30, 15);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block13_y_size - 330;
	tmpRc.bottom = tmpRc.top + Block13_y_size;
	tmpRc.left = tmpRc.right + 7310;
	tmpRc.right = tmpRc.left + Block13_x_size;

	tmp->Load(_T("Resource//image//Block_13.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block14_y_size - 380;
	tmpRc.bottom = tmpRc.top + Block14_y_size;
	tmpRc.left = tmpRc.right + 8200;
	tmpRc.right = tmpRc.left + Block14_x_size;

	tmp->Load(_T("Resource//image//Block_14.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0, 10, 10);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block14_y_size - 150;
	tmpRc.bottom = tmpRc.top + Block14_y_size;
	tmpRc.left = tmpRc.right + 8600;
	tmpRc.right = tmpRc.left + Block14_x_size;

	tmp->Load(_T("Resource//image//Block_14.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0, 10, 10);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block14_y_size - 420;
	tmpRc.bottom = tmpRc.top + Block14_y_size;
	tmpRc.left = tmpRc.right + 8900;
	tmpRc.right = tmpRc.left + Block14_x_size;

	tmp->Load(_T("Resource//image//Block_14.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0, 10, 10);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block10_1_y_size - 100;
	tmpRc.bottom = tmpRc.top + Block10_1_y_size;
	tmpRc.left = tmpRc.right + 9400;
	tmpRc.right = tmpRc.left + Block10_1_x_size;

	tmp->Load(_T("Resource//image//Block_10_1.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(0, 15, 30, 45);
	BlockDepot.Push(tmp);

	tmp = new Block;

	tmpRc = ClientRect;
	tmpRc.top = tmpRc.height() - Block15_y_size+100;
	tmpRc.bottom = tmpRc.top + Block15_y_size;
	tmpRc.left = tmpRc.right + 9900;
	tmpRc.right = tmpRc.left + Block15_x_size;

	tmp->Load(_T("Resource//image//Block_15.bmp"));
	tmp->SetTransparent(RGB(0,0,0));
	tmp->SetRect(tmpRc);
	tmp->SetBBoxRect(tmpRc);
	tmp->SetShowBox();
	tmp->BoxGap(300, 25, 25);
	BlockDepot.Push(tmp);

	ItemDepot.KirbyStarPush(Point(11400, 200));
	ItemDepot.TomatoPush(Point(3450,400));
	ItemDepot.TomatoPush(Point(9333,330));
}
void Stage1_1::SetPlayerPos(const Point& pt, const Point& kt)
{
	if(PlayerPos.x < pt.x)
	{
		MoveBlock.x = pt.x - PlayerPos.x;
	}
	else if(PlayerPos.x > pt.x)
	{
		MoveBlock.x = -(PlayerPos.x - pt.x);
	}
	else
		MoveBlock.x = 0;

	if(PlayerPos.x < pt.x)
	{
		MoveMap.x -= 1;
	}
	else if(PlayerPos.x > pt.x)
	{
		MoveMap.x += 1;
	}

	PlayerPos = pt;
	KirbyPos = kt;
}
void Stage1_1::SetDrainRect(const Rect& rc)
{
	EnemiesDepot.SetDrainRect(rc);
}