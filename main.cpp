#include <fstream>
#include <string>
#include <ctime>
#include <thread>
#include <windows.h>
#include <tchar.h>

#pragma comment(lib,"winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

using namespace std;

#define edition "Bell 1.1"

SYSTEMTIME sys;
#define hour sys.wHour
#define minu sys.wMinute
#define sec sys.wSecond

#include "begin.rc"
#include "end.rc"
#include "exercise.rc"

void playsound(string Music)
{
	Music = "play " + Music;
	mciSendString(Music.c_str(), NULL, 0, NULL);
}

void delete_file()
{
	DeleteFile(_T("上课.mp3"));
	DeleteFile(_T("下课.mp3"));
	DeleteFile(_T("眼保健操.mp3"));
} 

void init()
{
	SetConsoleTitle(edition);
	
	ofstream out1("begin.base64", ios::binary);
	SetFileAttributes("begin.base64", FILE_ATTRIBUTE_HIDDEN);
	out1 << begi;
	out1.close();
	ofstream out2("end.base64", ios::binary);
	SetFileAttributes("end.base64", FILE_ATTRIBUTE_HIDDEN);
	out2 << en;
	out2.close();
	ofstream out3("exercise.base64", ios::binary);
	SetFileAttributes("exercise.base64", FILE_ATTRIBUTE_HIDDEN);
	out3 << exercise;
	out3.close();
	
	system("@certutil -decode begin.base64 上课.mp3");
	system("@certutil -decode end.base64 下课.mp3");
	system("@certutil -decode exercise.base64 眼保健操.mp3");
	SetFileAttributes("上课.mp3", FILE_ATTRIBUTE_HIDDEN);
	DeleteFile(_T("begin.base64"));
	SetFileAttributes("下课.mp3", FILE_ATTRIBUTE_HIDDEN);
	DeleteFile(_T("end.base64"));
	SetFileAttributes("眼保健操.mp3", FILE_ATTRIBUTE_HIDDEN);
	DeleteFile(_T("exercise.base64"));
	
	atexit(delete_file); 
}

void Auto_Play()
{
	while (1)
	{
		GetLocalTime(&sys);
		if (sec == 0)
		{
			if (hour == 8 && minu == 0) playsound("上课.mp3");
			if (hour == 8 && minu == 55) playsound("上课.mp3");
			if (hour == 10 && minu == 20) playsound("上课.mp3");
			if (hour == 11 && minu == 15) playsound("上课.mp3");
			if (hour == 13 && minu == 30) playsound("上课.mp3");
			if (hour == 14 && minu == 25) playsound("上课.mp3");
			if (hour == 15 && minu == 25) playsound("上课.mp3");
			if (hour == 16 && minu == 30) playsound("上课.mp3");

			if (hour == 8 && minu == 45) playsound("下课.mp3");
			if (hour == 9 && minu == 40) playsound("下课.mp3");
			if (hour == 11 && minu == 5) playsound("下课.mp3");
			if (hour == 12 && minu == 0) playsound("下课.mp3");
			if (hour == 14 && minu == 15) playsound("下课.mp3");
			if (hour == 15 && minu == 10) playsound("下课.mp3");
			if (hour == 16 && minu == 10) playsound("下课.mp3");
			if (hour == 17 && minu == 30) playsound("下课.mp3");
		}
		if (sec == 20)
		{
			if (hour == 9 && minu == 40) playsound("眼保健操.mp3");
			if (hour == 15 && minu == 10) playsound("眼保健操.mp3");
		}
		Sleep(1);
	}
}

void Manual_Play()
{
	while (1)
	{
		if (KEY_DOWN(VK_MENU))
		{
			if (KEY_DOWN('J')) playsound("上课.mp3");
			if (KEY_DOWN('K')) playsound("下课.mp3");
			if (KEY_DOWN('L')) playsound("眼保健操.mp3");
		}
		Sleep(1);
	}
}

int main()
{
	init();
	thread task01(Auto_Play);
	thread task02(Manual_Play);
	thread task03([]() noexcept {if (MessageBoxA(0, "点击 \"确定\" 来退出本程序", edition, MB_OK) == 1) exit(0); });
	task01.join();
	task02.join();
	return 0;
}
