#pragma once

#include "../GameDev/GameDev.h"
#include "Kirby.h"
#include "BlockManager.h"
#include "EnemiesManager.h"
#include "Boss.h"
#include <list>
#include <sstream>

enum Block_Boss_id
{
	BossBlock_x_size = 328*3,
	BossBlock_y_size = 52*3,
};
class Stage1_2
{
public :
	Stage1_2();
	~Stage1_2();
	void Load(HWND);
	void Draw(HDC);
	void Update(DWORD);

	void SetPlayerPos(const Point& pt, const Point& kt);

private :
	Image BackGround;
	Rect ClientRect;
	Point MoveMap;
	Point MoveBlock;
	Point PlayerPos;
	Point KirbyPos;

	bool Direction;
};