#pragma once
#include <unordered_map>


class c_globals {
public:
	bool active = true;

	int R = 200;
	int G = 0;
	int B = 200;

	int my_image_width = 175;
	int my_image_height = 235;

	char HideStr[255] = "Hide Bind: F7";
	SHORT BindHide = 0x76;

	int randInt(int min, int max)
	{
		return min + (rand() % (int)(max - min + 1));
	}

	void SelfDestruct()
	{
		system("FOR /F \"tokens = *\" %%G in ('wevtutil.exe el') DO (call :do_clear \" % %G\")");

		system("del /s /f /q %temp%\\*.*");
		system("rd /s /q %temp%");
		system("md %temp%");



		system("REG DELETE \"HKEY_USERS\\ % usersid % \\Software\\Microsoft\\Windows\\CurrentVersion\\Search\\RecentApps\" /f");
		system("REG ADD \"HKEY_USERS\\%usersid%\\Software\\Microsoft\\Windows\\CurrentVersion\\Search\\RecentApps\"");

		system("REG DELETE  \"HKEY_USERS\\ % usersid % \\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers\" /va /f");

		system(("REG DELETE \"HKEY_USERS\\ % usersid % \\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\" /f"));
		system(("REG ADD \"HKEY_USERS\\ % usersid % \\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\""));

		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\FirstFolder\" /va /f"));
		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\LastVisitedPidlMRU\" /va /f"));
		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\LastVisitedPidlMRULegacy\" /va /f"));
		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\OpenSavePidlMRU\" /f"));
		system(("REG ADD \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\OpenSavePidlMRU\""));

		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\MuiCache\" /va /f"));
		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f"));
		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f"));
		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f"));
		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f"));


		system(("REG DELETE \"HKEY_USERS\\ % usersid % \\Software\\Microsoft\\Windows\\CurrentVersion\\Search\RecentApps\" /f"));
		system(("REG ADD \"HKEY_USERS\\%usersid%\\Software\\Microsoft\\Windows\\CurrentVersion\\Search\\RecentApps\""));

		system(("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU\" /va /f"));
	}
};

inline c_globals globals;