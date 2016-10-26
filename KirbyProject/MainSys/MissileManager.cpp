#include "MissileManager.h"
#include "CutterKirby.h"

MissileManager::MissileManager()
: HitSound(false), Stage(1)
{
}
MissileManager::~MissileManager()
{
	std::list<StarShot*>::iterator it;
	for (it = StarDepot.begin(); it != StarDepot.end(); )
	{
		SafeDelete(*it);
		it = StarDepot.erase(it);
	}
	std::list<AirShot*>::iterator jt;
	for (jt = AirDepot.begin(); jt != AirDepot.end(); )
	{
		SafeDelete(*jt);
		jt = AirDepot.erase(jt);
	}
	std::list<EnemiesCutter*>::iterator et;
	for (et = ECutterDepot.begin(); et != ECutterDepot.end(); )
	{
		SafeDelete(*et);
		et = ECutterDepot.erase(et);
	}
	std::list<Cutter*>::iterator ft;
	for (ft = CutterDepot.begin(); ft != CutterDepot.end(); )
	{
		SafeDelete(*ft);
		ft = CutterDepot.erase(ft);
	}
}
void MissileManager::IceShotPush(const Point& pt, const bool& bk)
{
	IceShot* tmp = new IceShot(pt, bk);

	IceDepot.push_back(tmp);
}
void MissileManager::RageIceShotPush(const Point& pt, const bool& bk)
{
	RageIceShot* tmp = new RageIceShot(pt, bk);

	RageIceDepot.push_back(tmp);
}

void MissileManager::StarPush(const Point& pt, const bool& bk)
{
	StarShot* tmp = new StarShot(pt, bk);

	StarDepot.push_back(tmp);
}
void MissileManager::AirPush(const Point& pt, const bool& bk)
{
	AirShot* tmp = new AirShot(pt, bk);

	AirDepot.push_back(tmp);
}
void MissileManager::ECutterPush(const Point& pt, const bool& bk)
{
	EnemiesCutter* tmp = new EnemiesCutter(pt, bk);

	ECutterDepot.push_back(tmp);
}
void MissileManager::CutterPush(const Point& pt, const bool& bk)
{
	Cutter* tmp = new Cutter(pt, bk);

	CutterDepot.push_back(tmp);
}
void MissileManager::Input(DWORD tick)
{
	std::list<Cutter*>::iterator st;
	for (st = CutterDepot.begin(); st != CutterDepot.end(); st++)
	{
		(*st)->Input(tick);
	}
}
void MissileManager::Update(DWORD tick)
{
	//KirbyBase.Update(tick);
	//BlockDepot.Update(0,0);
	//EnemiesDepot.Update(tick);
	//////////////////////////////////////////////////////////////
	//// 별 발사 업데이트
	//////////////////////////////////////////////////////////////
	{
		std::list<StarShot*>::iterator st;
		for (st = StarDepot.begin(); st != StarDepot.end(); st++)
		{
			(*st)->Update(tick);
		}

		if(Stage == 2)
		{
			std::list<StarShot*>::iterator bt;
			for (bt = StarDepot.begin(); bt != StarDepot.end(); bt++)
			{
				if((*bt)->ReturnBBox())
				{
					BYTE tmp = (*bt)->ReturnBBox()->BoxIsCollide(BossBase.getBBox(), KirbyBase.ReturnBack());
					if(tmp != 4)
					{
						(*bt)->SetHit(true);
						BossBase.GetStarHit(true);
					}
				}
			}
		}

		std::list<Enemies*> eList = EnemiesDepot.getList();
		std::list<Enemies*>::iterator et;
		for (et = eList.begin(); et != eList.end(); et++)
		{
			std::list<StarShot*>::iterator jt;
			for (jt = StarDepot.begin(); jt != StarDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide((*et)->getBBox(), KirbyBase.ReturnBack());
					if(tmp != 4)
					{
						(*jt)->SetHit(true);
						(*et)->GetStarHit(true, !(KirbyBase.ReturnBack()));
					}
				}
			}
		}

		std::list<Block*> bList = BlockDepot.getList();
		std::list<Block*>::iterator it;
		for (it = bList.begin(); it != bList.end(); it++)
		{
			std::list<StarShot*>::iterator jt;
			for (jt = StarDepot.begin(); jt != StarDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide((*it)->getBBox(), KirbyBase.ReturnBack());
					if(tmp == 1 || tmp == 2)
						(*jt)->SetHit(true);
				}
			}
		}
		std::list<StarShot*>::iterator jt;
		for (jt = StarDepot.begin(); jt != StarDepot.end(); )
		{
			if((*jt)->GetDel())
			{
				SafeDelete(*jt);

				jt = StarDepot.erase(jt);

				AniDepot["StarShotEnd"]->reset();
			}
			else
				jt++;
		}
	}
	//////////////////////////////////////////////////////////////
	//// 공기 발사 업데이트
	//////////////////////////////////////////////////////////////
	{
		std::list<AirShot*>::iterator st;
		for (st = AirDepot.begin(); st != AirDepot.end(); st++)
		{
			(*st)->SetPlayerPos(KirbyBase.RetrunPlayerPos().x);
			(*st)->Update(tick);
		}

		std::list<Enemies*> eList = EnemiesDepot.getList();
		std::list<Enemies*>::iterator et;
		for (et = eList.begin(); et != eList.end(); et++)
		{
			std::list<AirShot*>::iterator jt;
			for (jt = AirDepot.begin(); jt != AirDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide((*et)->getBBox(), KirbyBase.ReturnBack());
					if(tmp != 4)
					{
						(*jt)->SetHit(true);
						(*et)->GetAirHit(true, !(KirbyBase.ReturnBack()));
					}
				}
			}
		}

		std::list<Block*> bList = BlockDepot.getList();
		std::list<Block*>::iterator it;
		for (it = bList.begin(); it != bList.end(); it++)
		{
			std::list<AirShot*>::iterator jt;
			for (jt = AirDepot.begin(); jt != AirDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide((*it)->getBBox(), KirbyBase.ReturnBack());
					if(tmp == 1 || tmp == 2)
						(*jt)->SetHit(true);
				}
			}
		}
		std::list<AirShot*>::iterator jt;
		for (jt = AirDepot.begin(); jt != AirDepot.end(); )
		{
			if((*jt)->GetDel())
			{
				SafeDelete(*jt);

				jt = AirDepot.erase(jt);

				AniDepot["AirShot"]->reset();
				AniDepot["AirShotBack"]->reset();
			}
			else
				jt++;
		}
	}
	//////////////////////////////////////////////////////////////
	//// 적 커터 발사 업데이트
	//////////////////////////////////////////////////////////////
	{
		std::list<EnemiesCutter*>::iterator st;
		for (st = ECutterDepot.begin(); st != ECutterDepot.end(); st++)
		{
			(*st)->SetPlayerPos(KirbyBase.RetrunPlayerPos().x);
			(*st)->Update(tick);
		}

		{
			std::list<EnemiesCutter*>::iterator jt;
			for (jt = ECutterDepot.begin(); jt != ECutterDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide(KirbyBase.GetBBox(), (*jt)->GetBack());
					if(tmp != 4)
					{
						(*jt)->SetHit(true);
						KirbyBase.SetMissileHit((*jt)->GetBack());
						CutterKirbyBase.SetMissileHit((*jt)->GetBack());
					}
				}
			}
		}

		std::list<Enemies*> eList = EnemiesDepot.getList();
		std::list<Enemies*>::iterator et;
		for (et = eList.begin(); et != eList.end(); et++)
		{
			std::list<EnemiesCutter*>::iterator jt;
			for (jt = ECutterDepot.begin(); jt != ECutterDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide((*et)->getBBox(), (*jt)->GetBack());
					if((tmp == 1 || tmp == 2) && (*jt)->GetTurn() > 100)
					{
						(*jt)->SetHit(true);
					}
				}
			}
		}

		std::list<Block*> bList = BlockDepot.getList();
		std::list<Block*>::iterator it;
		for (it = bList.begin(); it != bList.end(); it++)
		{
			std::list<EnemiesCutter*>::iterator jt;
			for (jt = ECutterDepot.begin(); jt != ECutterDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide((*it)->getBBox(), (*jt)->GetBack());
					if(tmp == 1 || tmp == 2)
						(*jt)->SetHit(true);
				}
			}
		}
		std::list<EnemiesCutter*>::iterator jt;
		for (jt = ECutterDepot.begin(); jt != ECutterDepot.end(); )
		{
			if((*jt)->GetDel())
			{
				SafeDelete(*jt);

				jt = ECutterDepot.erase(jt);
			}
			else
				jt++;
		}
	}
	//////////////////////////////////////////////////////////////
	//// 커터 발사 업데이트
	//////////////////////////////////////////////////////////////
	{
		std::list<Cutter*>::iterator st;
		for (st = CutterDepot.begin(); st != CutterDepot.end(); st++)
		{
			(*st)->SetPlayerPos(KirbyBase.RetrunPlayerPos().x);
			(*st)->Update(tick);
		}

		{
			std::list<Cutter*>::iterator jt;
			for (jt = CutterDepot.begin(); jt != CutterDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide(KirbyBase.GetBBox(), (*jt)->GetBack());
					if(tmp != 4 && (*jt)->GetTurn() > 50)
					{
						(*jt)->SetHit(true);
					}
				}
			}
		}

		if(Stage == 2)
		{
			std::list<Cutter*>::iterator bt;
			for (bt = CutterDepot.begin(); bt != CutterDepot.end(); bt++)
			{
				if((*bt)->ReturnBBox())
				{
					BYTE tmp = (*bt)->ReturnBBox()->BoxIsCollide(BossBase.getBBox(), (*bt)->GetBack());
					Rect tmprc;
					IntersectRect(&tmprc, &BossBase.GetBBoxRect(), &(*bt)->GetCutterRect());

					if(tmp != 4)
					{
						if(!HitSound)
						{
							SndDepot["CutterHit"]->Play();
							HitSound = true;
						}
						AniDepot["CutterEffect"]->reset();
						AniDepot["CutterEffect"]->SetRect(Rect(tmprc.left, tmprc.top, tmprc.left + 51, tmprc.top + 48));

						if(tmprc.left == 0)
							AniDepot["CutterEffect"]->SetRect(Rect(1000,1000,1000,1000));

						(*bt)->SetHit(true);
						BossBase.SetCutterHit(true);

						HitSound = false;
					}
				}
			}
		}

		std::list<Enemies*> eList = EnemiesDepot.getList();
		std::list<Enemies*>::iterator et;
		for (et = eList.begin(); et != eList.end(); et++)
		{
			std::list<Cutter*>::iterator jt;
			for (jt = CutterDepot.begin(); jt != CutterDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide((*et)->getBBox(), (*jt)->GetBack());
					Rect tmprc;
					IntersectRect(&tmprc, &(*et)->GetRect(), &(*jt)->GetCutterRect());

					if(tmp != 4)
					{
						if(!HitSound)
						{
							SndDepot["CutterHit"]->Play();
							HitSound = true;
						}
						AniDepot["CutterEffect"]->reset();
						AniDepot["CutterEffect"]->SetRect(Rect(tmprc.left, tmprc.top, tmprc.left + 51, tmprc.top + 48));

						if(tmprc.left == 0)
							AniDepot["CutterEffect"]->SetRect(Rect(1000,1000,1000,1000));

						(*jt)->SetHit(true);
						(*et)->GetAirHit(true, !(KirbyBase.ReturnBack()));

						HitSound = false;
					}
				}
			}
		}
		AniDepot["CutterEffect"]->Update(tick);

		std::list<Block*> bList = BlockDepot.getList();
		std::list<Block*>::iterator it;
		for (it = bList.begin(); it != bList.end(); it++)
		{
			std::list<Cutter*>::iterator jt;
			for (jt = CutterDepot.begin(); jt != CutterDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide((*it)->getBBox(), (*jt)->GetBack());
					if(tmp == 1 || tmp == 2)
						(*jt)->SetBlockHit(true);
					else if((tmp == 3 && InputDevice[VK_UP]) || ((tmp == 0 && InputDevice[VK_DOWN])))
						(*jt)->SetBlockHit(true);
				}
			}
		}
		std::list<Cutter*>::iterator jt;
		for (jt = CutterDepot.begin(); jt != CutterDepot.end(); )
		{
			if((*jt)->GetDel())
			{
				SafeDelete(*jt);

				jt = CutterDepot.erase(jt);
			}
			else
				jt++;
		}
	}
	//////////////////////////////////////////////////////////////
	//// 적 얼음 발사 업데이트
	//////////////////////////////////////////////////////////////
	{

		std::list<IceShot*>::iterator st;
		for (st = IceDepot.begin(); st != IceDepot.end(); st++)
		{
			(*st)->Update(tick);
		}

		{
			std::list<IceShot*>::iterator jt;
			for (jt = IceDepot.begin(); jt != IceDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide(KirbyBase.GetBBox(), !(*jt)->GetBack());
					if(tmp != 4)
					{
						KirbyBase.SetMissileHit((*jt)->GetBack());
						CutterKirbyBase.SetMissileHit((*jt)->GetBack());
					}
				}
			}
		}

		std::list<IceShot*>::iterator jt;
		for (jt = IceDepot.begin(); jt != IceDepot.end(); )
		{
			if((*jt)->GetDel())
			{
				SafeDelete(*jt);

				jt = IceDepot.erase(jt);
			}
			else
				jt++;
		}
	}
	//////////////////////////////////////////////////////////////
	//// 분노 적 얼음 발사 업데이트
	//////////////////////////////////////////////////////////////
	{

		std::list<RageIceShot*>::iterator st;
		for (st = RageIceDepot.begin(); st != RageIceDepot.end(); st++)
		{
			(*st)->Update(tick);
		}

		{
			std::list<RageIceShot*>::iterator jt;
			for (jt = RageIceDepot.begin(); jt != RageIceDepot.end(); jt++)
			{
				if((*jt)->ReturnBBox())
				{
					BYTE tmp = (*jt)->ReturnBBox()->BoxIsCollide(KirbyBase.GetBBox(), !(*jt)->GetBack());
					if(tmp != 4)
					{
						KirbyBase.SetMissileHit((*jt)->GetBack());
						CutterKirbyBase.SetMissileHit((*jt)->GetBack());
					}
				}
			}
		}

		std::list<RageIceShot*>::iterator jt;
		for (jt = RageIceDepot.begin(); jt != RageIceDepot.end(); )
		{
			if((*jt)->GetDel())
			{
				SafeDelete(*jt);

				jt = RageIceDepot.erase(jt);
			}
			else
				jt++;
		}
	}
}
void MissileManager::Draw(HDC hdc)
{
	// 별 그리기
	std::list<StarShot*>::iterator it;
	for (it = StarDepot.begin(); it != StarDepot.end();)
	{
		(*it)->Draw(hdc);

		Rect tmp;
		if (!(::IntersectRect(&tmp, &GameGlobal.rcClient, &((*it)->GetStarRect()))))
		{
			SafeDelete(*it);
			it = StarDepot.erase(it);
		}
		else
			it++;
	}
	// 공기 그리기
	std::list<AirShot*>::iterator jt;
	for (jt = AirDepot.begin(); jt != AirDepot.end();)
	{
		(*jt)->Draw(hdc);

		Rect tmp;
		if (!(::IntersectRect(&tmp, &GameGlobal.rcClient, &((*jt)->GetAirRect()))))
		{
			SafeDelete(*jt);
			jt = AirDepot.erase(jt);
		}
		else
			jt++;
	}
	// 적 커터 그리기
	std::list<EnemiesCutter*>::iterator et;
	for (et = ECutterDepot.begin(); et != ECutterDepot.end(); et++)
	{
		(*et)->Draw(hdc);
	}
	// 커터 그리기
	std::list<Cutter*>::iterator ft;
	for (ft = CutterDepot.begin(); ft != CutterDepot.end();)
	{
		(*ft)->Draw(hdc);

		Rect tmp;
		if (!(::IntersectRect(&tmp, &GameGlobal.rcClient, &((*ft)->GetCutterRect()))))
		{
			SafeDelete(*ft);
			ft = CutterDepot.erase(ft);
		}
		else
			ft++;
	}
	// 얼음 그리기
	std::list<IceShot*>::iterator ct;
	for (ct = IceDepot.begin(); ct != IceDepot.end();)
	{
		(*ct)->Draw(hdc);

		Rect tmp;
		if (!(::IntersectRect(&tmp, &GameGlobal.rcClient, &((*ct)->GetIceRect()))))
		{
			SafeDelete(*ct);
			ct = IceDepot.erase(ct);
		}
		else
			ct++;
	}
	std::list<RageIceShot*>::iterator rt;
	for (rt = RageIceDepot.begin(); rt != RageIceDepot.end();)
	{
		(*rt)->Draw(hdc);

		Rect tmp;
		if (!(::IntersectRect(&tmp, &GameGlobal.rcClient, &((*rt)->GetIceRect()))))
		{
			SafeDelete(*rt);
			rt = RageIceDepot.erase(rt);
		}
		else
			rt++;
	}
	if(AniDepot["CutterEffect"]->getRect().left != 0)
		AniDepot["CutterEffect"]->Draw(hdc);
}
void MissileManager::SetStage(const BYTE& s)
{
	Stage = s;
}