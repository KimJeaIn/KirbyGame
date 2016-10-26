#pragma once

#include "../GameDev/GameDev.h"
#include "Kirby.h"
#include "CutterKirby.h"
#include "BlockManager.h"
#include "EnemiesManager.h"
#include "ItemManager.h"
#include <list>
#include <sstream>

enum Block1_id
{
	Block1_x_size = 255*3,
	Block1_y_size = 127*3,

	Block2_x_size = 142*3,
	Block2_y_size = 180*3,

	Block3_x_size = 159*3,
	Block3_y_size = 176*3,

	Block3_1_x_size = 159*3,
	Block3_1_y_size = 71*3,

	Block4_x_size = 330*3,
	Block4_y_size = 176*3,

	Block6_x_size = 184*3,
	Block6_y_size = 135*3,

	Block6_1_x_size = 134*3,
	Block6_1_y_size = 157*3,

	Block7_x_size = 42*3,
	Block7_y_size = 180*3,

	Block7_1_x_size = 260*3,
	Block7_1_y_size = 68*3,

	Block7_1_1_x_size = 260*3,
	Block7_1_1_y_size = 106*3,

	Block7_1_2_x_size = 47*3,
	Block7_1_2_y_size = 20*3,

	Block7_1_3_x_size = 46*3,
	Block7_1_3_y_size = 200*3,

	Block7_1_4_x_size = 36*3,
	Block7_1_4_y_size = 123*3,

	Block7_1_5_x_size = 36*3,
	Block7_1_5_y_size = 97*3,

	Block7_1_6_x_size = 165*3,
	Block7_1_6_y_size = 37*3,

	Block7_1_7_x_size = 165*3,
	Block7_1_7_y_size = 183*3,

	Block7_1_8_x_size = 65*3,
	Block7_1_8_y_size = 99*3,

	Block7_1_9_x_size = 65*3,
	Block7_1_9_y_size = 119*3,

	Block7_1_10_x_size = 137*3,
	Block7_1_10_y_size = 100*3,

	Block7_1_11_x_size = 136*3,
	Block7_1_11_y_size = 120*3,

	Block7_2_x_size = 889*3,
	Block7_2_y_size = 220*3,

	Block8_x_size = 98*3,
	Block8_y_size = 73*3,

	Block8_1_x_size = 131*3,
	Block8_1_y_size = 157*3,

	Block9_x_size = 78*3,
	Block9_y_size = 94*3,

	Block10_x_size = 86*3,
	Block10_y_size = 182*3,

	Block10_1_x_size = 86*3,
	Block10_1_y_size = 182*3,

	Block11_x_size = 119*3,
	Block11_y_size = 189*3,

	Block12_x_size = 250*3,
	Block12_y_size = 126*3,

	Block13_x_size = 218*3,
	Block13_y_size = 11*3,

	Block14_x_size = 80*3,
	Block14_y_size = 14*3,

	Block15_x_size = 415*3,
	Block15_y_size = 214*3,

};
class Stage1_1
{
public :
	Stage1_1();
	~Stage1_1();
	void Load(HWND);
	void Draw(HDC);
	void Update(DWORD);

	void SetPlayerPos(const Point& pt, const Point& kt);

	void SetDrainRect(const Rect& rc);

private :
	Image BackGround[2];
	Rect ClientRect;
	Point MoveMap;
	Point MoveBlock;
	Point PlayerPos;
	Point KirbyPos;

	bool Direction;
};