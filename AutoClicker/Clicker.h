#pragma once
#include <Windows.h>
#include "../Bind/Binds.h"
#include "../globals.hh"

namespace Clickers 
{
	void Clicker();
	void Jitter();
	DWORD WINAPI MyMouseLogger(LPVOID lpParm);
};

class c_Clicker
{
public:
	bool MouseDown = false;

	int MinCps = 7;
	int MaxCps = 14;

	bool Toggle = false;

	bool Jitter = false;
	int JitterStrengt = 1;

	bool OnlyMinecraftWindow = false;
	
	char Bind[255] = "Bind: C";

	SHORT BIND = 'C';

};

inline c_Clicker clicker;

