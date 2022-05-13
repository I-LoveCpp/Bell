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

#define edition "Bell 1.3.0"

SYSTEMTIME sys;
#define hour sys.wHour
#define minu sys.wMinute
#define sec sys.wSecond

#include "begin.rc"
#include "end.rc"
#include "exercise.rc"

int mode = 1;

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
	ofstream out("D:\\Data\\Bell\\Mode.Ceh", ios::binary);
	out << mode; 
} 

void init()
{
	SetConsoleTitle(edition);

	ifstream in("D:\\Data\\Bell\\Mode.Ceh", ios::binary);
	if (!in)
	{
		CreateDirectory("D:\\Data\\", NULL);
		SetFileAttributes("D:\\Data\\", FILE_ATTRIBUTE_HIDDEN);
		CreateDirectory("D:\\Data\\Bell\\", NULL);
		ofstream out("D:\\Data\\Bell\\Mode.Ceh", ios::binary);
		out << "1";
	}
	in >> mode;
	
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
		if (mode == 0)
		{
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
		}
		else
		{
			if (sec == 0)
			{
				if (hour == 8 && minu == 0) playsound("上课.mp3");
				if (hour == 8 && minu == 55) playsound("上课.mp3");
				if (hour == 9 && minu == 55) playsound("上课.mp3");
				if (hour == 13 && minu == 30) playsound("上课.mp3");
				if (hour == 14 && minu == 25) playsound("上课.mp3");
				if (hour == 15 && minu == 25) playsound("上课.mp3");
				if (hour == 16 && minu == 20) playsound("上课.mp3");

				if (hour == 8 && minu == 45) playsound("下课.mp3");
				if (hour == 9 && minu == 40) playsound("下课.mp3");
				if (hour == 10 && minu == 40) playsound("下课.mp3");
				if (hour == 14 && minu == 15) playsound("下课.mp3");
				if (hour == 15 && minu == 10) playsound("下课.mp3");
				if (hour == 16 && minu == 10) playsound("下课.mp3");
				if (hour == 17 && minu == 5) playsound("下课.mp3");
			}
			if (sec == 20)
			{
				if (hour == 9 && minu == 40) playsound("眼保健操.mp3");
				if (hour == 15 && minu == 10) playsound("眼保健操.mp3");
			}
		}
		Sleep(1);
	}
}

void Switch_Mode()
{
	while (1)
	{
		if (KEY_DOWN(VK_MENU) && KEY_DOWN('P'))
		{
			mode = (mode + 1) % 2;
			MessageBoxA(0, ((mode == 1) ? ("当前为新作息时间") : ("当前为旧作息时间")), edition, MB_OK);
			Sleep(100);
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
			if (KEY_DOWN('I'))
			{
				mciSendString("stop 上课.mp3", NULL, 0, NULL);
				mciSendString("stop 下课.mp3", NULL, 0, NULL);
				mciSendString("stop 眼保健操.mp3", NULL, 0, NULL);
			}
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
	thread task04(Switch_Mode);
	task01.join();
	task02.join();
	task04.join();
	return 0;
}
