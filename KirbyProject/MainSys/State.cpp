#include "State.h"

HpState::HpState()
{
}
HpState::~HpState()
{
}
void HpState::Update(DWORD tick)
{
}
void HpState::Draw(HDC hdc)
{
	Rect tmp = GameGlobal.rcClient;

	tmp.top = GameGlobal.rcClient.bottom - 87;
	tmp.right = tmp.left + 273;

	KirbyHpBar = tmp;

	KirbyHpBar.left = KirbyHpBar.left + 95;
	KirbyHpBar.top = KirbyHpBar.top + 12;
	KirbyHpBar.bottom = KirbyHpBar.top + 25;
	KirbyHpBar.right = KirbyHpBar.left + KirbyHp;

	ImgDepot["KirbyState"]->SetRect(tmp);
	ImgDepot["KirbyHp"]->SetRect(KirbyHpBar);
	ImgDepot["KirbyState"]->Draw(hdc);
	ImgDepot["KirbyHp"]->Draw(hdc);
}
void HpState::SetHp(const char& hp)
{
	if(hp < 0)
		KirbyHp = 0;
	KirbyHp = (hp * 16);
}

/////////////////////////
// º¸½º ½ºÅÝ
/////////////////////////
BossHpState::BossHpState()
{
}
BossHpState::~BossHpState()
{
}
void BossHpState::Update(DWORD tick)
{
}
void BossHpState::Draw(HDC hdc)
{
	Rect tmp = GameGlobal.rcClient;

	tmp.left = tmp.right - (151*2);
	tmp.bottom = tmp.top + 80;

	BossHpBar = tmp;

	BossHpBar.left = BossHpBar.left + 16;
	BossHpBar.top = BossHpBar.top + 32;
	BossHpBar.bottom = BossHpBar.top + 34;
	BossHpBar.right = BossHpBar.left + BossHp;

	ImgDepot["BossState"]->SetRect(tmp);
	ImgDepot["BossHp"]->SetRect(BossHpBar);
	ImgDepot["BossState"]->Draw(hdc);
	ImgDepot["BossHp"]->Draw(hdc);
}
void BossHpState::SetHp(const char& hp)
{
	if(hp <= 0)
		BossHp = 0;

	BossHp = ((hp/2) * 10);
}