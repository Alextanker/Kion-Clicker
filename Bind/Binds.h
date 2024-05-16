#pragma once
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <WinUser.h>
#include <thread>
#include <future>

namespace Binding
{
	int StringToBind(char* binds);
	void stream2hex(const std::string str, std::string& hexstr, bool capital = false);
	void Bind(SHORT& bind, bool& toggle, bool& DownLast);
	SHORT GetKeyCode();
	std::string VirtualKeyCodeToString(UCHAR virtualKey);
	void StringToChar(std::string string, char ch[255]);
	void AutoBind(CHAR* szName, std::string prefix, SHORT &Key);
};

class c_Binds
{
public:
	bool BindCheaking = false;
};

inline c_Binds binds;