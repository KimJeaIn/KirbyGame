#include "BitmapManager.h"

BitmapManager::BitmapManager()
{
}
BitmapManager::~BitmapManager()
{
	_release();
}
void BitmapManager::_release()
{
	for (Iter it = depot.begin();
		it != depot.end();)
	{
		::DeleteObject(it->second);
		it = depot.erase(it);
	}
}
