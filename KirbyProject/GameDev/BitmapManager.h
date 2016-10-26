#pragma once

#include <Windows.h>
#include <tchar.h>
#include "BaseType.h"
#include "Manager.hpp"
#include "Utility.hpp"
#include <string>

class BitmapManager : public Manager<HBITMAP__, std::wstring>, public singleton<BitmapManager>
{
	friend class singleton<BitmapManager>;

	typedef Manager<HBITMAP__, std::wstring>::Iter Iter;
private :
	BitmapManager();
	~BitmapManager();
private :
	virtual void _release();

};

#define BitmapDepot BitmapManager::getReference()