#include "MainSystem.h"
Mainsys::Mainsys()
: GameOver(false), Title(true), One(true)
, Stage1(NULL), Stage1BGM_dt(0), GameOverBGM(false)
, KirbyType(0), CutterChange(false), ChangeSound(false)
, SoundOne(false), Stage(1), Stage2(NULL), GameEnd(false)
, EndAni(false), BossDie(false), GameEnd_dt(0)
{
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	dwStyle = dwStyle & ~WS_THICKFRAME; 
	dwStyle = dwStyle & ~WS_MINIMIZEBOX;
	dwStyle = dwStyle & ~WS_MAXIMIZEBOX;

	SetWindowStyle(dwStyle);
	SetWindowSize(800, 600);	
}
void Mainsys::Enter()
{
	SndLoader(_T("Resource//Effect.sound"));
	ImgLoader(_T("Resource//Title.image"));
	AniLoader(_T("Resource//Title.animation"));
	ImgLoader(_T("Resource//Kirby.image"));
	AniLoader(_T("Resource//Kirby.animation"));
	SndLoader(_T("Resource//BGM.sound"));
	AniLoader(_T("Resource//Effect.animation"));
	AniLoader(_T("Resource//Enemies.animation"));
	ImgLoader(_T("Resource//CutterKirby.image"));
	AniLoader(_T("Resource//CutterKirby.animation"));

	Stage1 = new Stage1_1;

	Stage1->Load(hMainWnd);
	CutterKirbyBase.Load(rcClient);
	KirbyBase.Load(rcClient);
	BossBase.Load();
}
void Mainsys::Leave()
{
}
void Mainsys::Input(DWORD tick)
{

	if(!Title || !GameOver)
	{
		if(KirbyType == 0 && !CutterChange)
			KirbyBase.Input(tick);
		else if(KirbyType == 1 && !CutterChange)
		{
			CutterKirbyBase.Input(tick);
			MissileDepot.Input(tick);
		}
	}
	if(InputDevice.OnClick(VK_RETURN) && Title)
	{
		SndDepot["TitleBGM"]->Stop();
		KirbyBase.SetReset(false);
		CutterKirbyBase.SetReset(false);
		Title = false;
		SndDepot["Stage1"]->Play();
	}

	if(InputDevice.OnClick(VK_RETURN) && GameOver)
	{
		Stage1BGM_dt = 0;
		KirbyBase.SetReset(true);
		KirbyBase.KirbyReset();
		CutterKirbyBase.SetReset(true);
		CutterKirbyBase.KirbyReset();
		KirbyType = 0;
		Title = true;
		GameOver = false;
		One = true;
		GameOverBGM = false;
		Stage = 1;
		ItemDepot.Reset();
		BossBase.Reset();
		SndDepot["GameOverBGM"]->Stop();
	}
	if(InputDevice.OnClick(VK_RETURN) && EndAni)
	{
		Stage1BGM_dt = 0;
		KirbyBase.SetReset(true);
		KirbyBase.KirbyReset();
		CutterKirbyBase.SetReset(true);
		CutterKirbyBase.KirbyReset();
		KirbyType = 0;
		Title = true;
		GameOver = false;
		EndAni = false;
		One = true;
		GameOverBGM = false;
		BossDie = false;
		Stage = 1;
		ItemDepot.Reset();
		BossBase.Reset();
		SndDepot["End"]->Stop();
	}
}
void Mainsys::Update(DWORD tick)
{
	if(BossBase.ReturnHP() <= 0 && !BossDie)
	{
		GameEnd = true;
		BossDie = true;
		KirbyType = 0;
	}
	if(GameEnd)
	{
		if(KirbyBase.ReturnDrainRect().left == 5555)
		{
			EndAni = true;

			SndDepot["End"]->Play();

			GameEnd_dt = 0;
			GameEnd = false;
		}
	}

	if(CutterKirbyBase.ReturnType())
	{
		KirbyType = 0;
		CutterKirbyBase.SetRerease();
	}
	if(KirbyBase.ReturnStageChange() && Stage == 1)
	{
		Stage = 2;
		SafeDelete(Stage2);

		EnemiesDepot.Clear();
		BlockDepot.Clear();

		Stage2 = new Stage1_2;

		Stage2->Load(hMainWnd);
	}

	if(KirbyBase.ReturnDead())
	{
		KirbyType = 0;
	}

	GameOver = KirbyBase.ReturnEnd();

	if(Title && One)
	{
		if(Stage1 != NULL)
		{
			SafeDelete(Stage1);

			EnemiesDepot.Clear();
			BlockDepot.Clear();

			Stage1 = new Stage1_1;

			Stage1->Load(hMainWnd);
		}
		One = false;
	}
	if(!Title && !GameOver && !EndAni)
	{
		if(KirbyBase.ReturnType() == 2)
			CutterChange = true;

		if(CutterChange)
		{
			ImgDepot["Dark"]->SetRect(GameGlobal.rcClient);

			if(!ChangeSound)
			{
				SndDepot["Change"]->Play();
				ChangeSound = true;
			}
			Rect tmp;

			tmp.left = KirbyBase.RetrunKirbyPos().x - 87/2;
			tmp.top = KirbyBase.RetrunKirbyPos().y - 120/2;
			tmp.right = tmp.left + 87;
			tmp.bottom = tmp.top + 90;

			AniDepot["CutterKirbyChange"]->SetRect(tmp);
			AniDepot["CutterKirbyChange"]->Update(tick);

			if(!AniDepot["CutterKirbyChange"]->IsPlaying())
			{
				AniDepot["CutterKirbyChange"]->reset();
				CutterChange = false;
				ChangeSound = false;

				KirbyBase.TypeReset();

				KirbyType = 1;
			}
		}

		if(Stage == 1)
		{
			if(SndDepot["Stage1"]->IsPlaying())
			{
				if(Stage1BGM_dt > 56100)
				{
					SndDepot["Stage1"]->Stop();
					Stage1BGM_dt = 0;
				}
				Stage1BGM_dt += tick;
			}

			if(!(SndDepot["Stage1"]->IsPlaying()) && !(SndDepot["Stage2"]->IsPlaying()))
			{
				SndDepot["Stage2"]->Play();
				SoundOne = true;
			}
		}

		if(KirbyType == 0 && !CutterChange)
		{
			KirbyBase.Update(tick);
			CutterKirbyBase.Update(tick);
			CutterKirbyBase.Setposition(KirbyBase.RetrunPlayerPos(), KirbyBase.RetrunKirbyPos(), KirbyBase.ReturnBack());
			CutterKirbyBase.CutterCho();
		}
		else if(KirbyType == 1 && !CutterChange)
		{
			CutterKirbyBase.Update(tick);
			KirbyBase.Update(tick);
			KirbyBase.Setposition(CutterKirbyBase.RetrunPlayerPos(), CutterKirbyBase.RetrunKirbyPos(), CutterKirbyBase.ReturnBack());
		}
		
		if(!(KirbyBase.ReturnDead()) && !CutterChange)
		{
			MissileDepot.SetStage(Stage);
			ItemDepot.Update(tick);
			KirbyHpS.SetHp(KirbyBase.ReturnHP());
			if(Stage == 1)
			{
				Stage1->SetDrainRect(KirbyBase.ReturnDrainRect());
				Stage1->Update(tick);
				Stage1->SetPlayerPos(KirbyBase.RetrunPlayerPos(), KirbyBase.RetrunKirbyPos());
			}
			else if(Stage == 2)
			{
				BossHpS.SetHp(BossBase.ReturnHP());
				Stage2->Update(tick);
				BossBase.Input(tick);
				BossBase.Update(tick);
			}
			MissileDepot.Update(tick);
		}
	}
	else if(Title)
	{
		if(!(SndDepot["TitleBGM"]->IsPlaying()))
			SndDepot["TitleBGM"]->Play();

		AniDepot["Title"]->Update(tick);
		AniDepot["Title"]->ResetAni(tick, 5000);
	}
	else if(EndAni)
	{
		AniDepot["GameEnd"]->Update(tick);
	}
}
void Mainsys::Draw(DWORD)
{
	backbuffer << RGB(255,255,255);

	if(!Title && !GameOver && !EndAni)
	{
		if(Stage == 1)
		{
			Stage1->Draw(backbuffer);
		}
		else if(Stage == 2)
		{
			Stage2->Draw(backbuffer);
			BossBase.Draw(backbuffer);
			BossHpS.Draw(backbuffer);
		}

		if(CutterChange)
		{
			ImgDepot["Dark"]->Draw(backbuffer);

			AniDepot["CutterKirbyChange"]->Draw(backbuffer);
		}
		MissileDepot.Draw(backbuffer);

		if(KirbyType == 0 && !CutterChange)
			KirbyBase.Draw(backbuffer);
		else if(KirbyType == 1)
			CutterKirbyBase.Draw(backbuffer);

		ItemDepot.Draw(backbuffer);
		KirbyHpS.Draw(backbuffer);
	}
	else if(Title)
	{
		Rect tmp = GameGlobal.rcClient;
		ImgDepot["TitleBack"]->SetRect(tmp);
		ImgDepot["TitleBack"]->Draw(backbuffer);

		tmp.left = (GameGlobal.rcClient.width()/2) - 380;
		tmp.top = GameGlobal.rcClient.top+50;
		tmp.right = tmp.left + 760;
		tmp.bottom = tmp.top + 500;
		ImgDepot["TitleStd"]->SetRect(tmp);
		ImgDepot["TitleStd"]->Draw(backbuffer);

		AniDepot["Title"]->SetRect(tmp);
		AniDepot["Title"]->Draw(backbuffer);
	}
	else if(GameOver)
	{
		if(!(SndDepot["GameOverBGM"]->IsPlaying()) && !GameOverBGM)
		{
			SndDepot["BossBattle"]->Stop();
			SndDepot["GameOverBGM"]->Play();
			GameOverBGM = true;
		}

		ImgDepot["GameOver"]->SetRect(GameGlobal.rcClient);
		ImgDepot["GameOver"]->Draw(backbuffer);
	}
	else if(EndAni)
	{
		AniDepot["GameEnd"]->SetRect(GameGlobal.rcClient);
		AniDepot["GameEnd"]->Draw(backbuffer);
	}

	backbuffer.Draw();
}