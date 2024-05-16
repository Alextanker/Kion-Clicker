#include "Clicker.h"
#include <future>

static bool toggled = false;
static int triggerval;
static bool click = false;
static bool DownLast = false;

HHOOK hMouseHook;

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;

	if (pMouseStruct != NULL && pMouseStruct->flags != LLMHF_INJECTED)
	{
		if (wParam == WM_LBUTTONDOWN)
		{
			clicker.MouseDown = true;
		}
		if (wParam == WM_LBUTTONUP)
		{
			clicker.MouseDown = false;
		}
		//printf("Mouse position X = %d  Mouse Position Y = %d\n", pMouseStruct->pt.x, pMouseStruct->pt.y);
	}
	return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

DWORD WINAPI Clickers::MyMouseLogger(LPVOID lpParm)
{
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
		Sleep(1);
	}

	UnhookWindowsHookEx(hMouseHook);
	return 0;
}


void GetRandomCps(int& cps_min, int& cps_max, int time, bool& work, int& cps)
{
	try
	{
		while (work)
		{
			cps = globals.randInt(cps_min, cps_max);
			SleepEx(time, !work);
			if (!globals.active)
			{
				break;
			}
		}
	}
	catch (...)
	{

	}
}

void Click(int cps)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dx = 0;
	input.mi.dy = 0;
	input.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
	input.mi.mouseData = 0;
	input.mi.dwExtraInfo = NULL;
	input.mi.time = 0;
	SendInput(1, &input, sizeof(INPUT));
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1000 / cps));
}

void Clickers::Clicker()
{
	bool firstClick = true;
	
	SetThreadPriority(std::this_thread::get_id, THREAD_PRIORITY_TIME_CRITICAL);

	bool randomWork = true;

	int randomCps = 0;

	auto randomThread = std::async(std::launch::async, [&]() { GetRandomCps(clicker.MinCps, clicker.MaxCps, 1000, randomWork, randomCps); });

	while (1)
	{
		if (clicker.Toggle)
		{
			bool keyDown = GetAsyncKeyState(clicker.BIND) & 1;

			if (keyDown && !DownLast)
			{
				toggled = true;
			}
			if (!keyDown && toggled)
			{
				DownLast = true;
			}
			if (keyDown && DownLast)
			{
				toggled = false;
			}
			if (!keyDown && !toggled)
			{
				DownLast = false;
			}


			if (!clicker.MouseDown)
			{
				firstClick = true;
			}

			if (clicker.MouseDown && toggled)
			{
				if ((GetForegroundWindow() == FindWindow(NULL, "Minecraft") || GetForegroundWindow() == FindWindow(NULL, "LWJGL")) || !clicker.OnlyMinecraftWindow)
				{
					if (firstClick)
					{
						Sleep(100);
						if (!clicker.MouseDown)
						{
							continue;
						}
					}
					Click(randomCps);
					firstClick = false;
				}
			}
		}
		Sleep(1);
	}
	randomWork = false;
	randomThread.wait();
}

void Clickers::Jitter()
{
	while (1)
	{
		if (toggled == true && clicker.Jitter == true && (clicker.MouseDown == true || click == true))
		{
			mouse_event(MOUSEEVENTF_MOVE, globals.randInt(clicker.JitterStrengt - (clicker.JitterStrengt * 2), clicker.JitterStrengt), globals.randInt(clicker.JitterStrengt - (clicker.JitterStrengt * 2), clicker.JitterStrengt), 0, 0);
		}
		Sleep(globals.randInt(10, 30));
	}
}