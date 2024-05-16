#include "Binds.h"
#pragma warning(disable : 4996)

using namespace std;

void Binding::stream2hex(const std::string str, std::string& hexstr, bool capital)
{
	hexstr.resize(str.size() * 2);
	const size_t a = capital ? 'A' - 1 : 'a' - 1;

	for (size_t i = 0, c = str[0] & 0xFF; i < hexstr.size(); c = str[i / 2] & 0xFF)
	{
		hexstr[i++] = c > 0x9F ? (c / 16 - 9) | a : c / 16 | '0';
		hexstr[i++] = (c & 0xF) > 9 ? (c % 16 - 9) | a : c % 16 | '0';
	}
}

int Binding::StringToBind(char* input)
{
	string binds;

	int bind;

	stream2hex(input, binds);

	istringstream ss(binds);
	ss >> hex >> bind;

	if (bind >= 97)
	{
		int value = bind - 32;
		bind = value;
	}
	return bind;
}

void Binding::Bind(SHORT& bind, bool& toggle, bool& DownLast)
{
	bool keyDown = GetAsyncKeyState(bind) & 0x8000;

	if (keyDown && !DownLast)
	{
		toggle = true;
	}
	if (!keyDown && toggle)
	{
		DownLast = true;
	}
	if (keyDown && DownLast)
	{
		toggle = false;
	}
	if (!keyDown && !toggle)
	{
		DownLast = false;
	}
}

SHORT Binding::GetKeyCode()
{
	bool CheakKey = false;
	SHORT Key = 0;
	while (!CheakKey)
	{
		for (SHORT i = 5; i < 255; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				CheakKey = true;
				Key = i;
			}
		}
		Sleep(1);
	}
	return Key;
}

std::string Binding::VirtualKeyCodeToString(UCHAR virtualKey)
{
	UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

	CHAR szName[128];
	int result = 0;
	switch (virtualKey)
	{
	case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
	case VK_RCONTROL: case VK_RMENU:
	case VK_LWIN: case VK_RWIN: case VK_APPS:
	case VK_PRIOR: case VK_NEXT:
	case VK_END: case VK_HOME:
	case VK_INSERT: case VK_DELETE:
	case VK_DIVIDE:
	case VK_NUMLOCK:
		scanCode |= KF_EXTENDED;
	default:
		result = GetKeyNameTextA(scanCode << 16, szName, 128);
	}

	if (result == 0)
		StringToChar("key code " + std::to_string(virtualKey), szName);
	return szName;
}

void Binding::StringToChar(std::string string, char ch[255])
{
	strcpy(ch, string.c_str());
}


void Binding::AutoBind(CHAR* szName, std::string prefix, SHORT &Key)
{
	Binding::StringToChar("Press any key...", szName);
	Key = GetKeyCode();
	Binding::StringToChar(prefix + Binding::VirtualKeyCodeToString(Key), szName);

}