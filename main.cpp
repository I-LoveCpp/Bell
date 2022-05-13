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
	DeleteFile(_T("�Ͽ�.mp3"));
	DeleteFile(_T("�¿�.mp3"));
	DeleteFile(_T("�۱�����.mp3"));
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
	
	system("@certutil -decode begin.base64 �Ͽ�.mp3");
	system("@certutil -decode end.base64 �¿�.mp3");
	system("@certutil -decode exercise.base64 �۱�����.mp3");
	SetFileAttributes("�Ͽ�.mp3", FILE_ATTRIBUTE_HIDDEN);
	DeleteFile(_T("begin.base64"));
	SetFileAttributes("�¿�.mp3", FILE_ATTRIBUTE_HIDDEN);
	DeleteFile(_T("end.base64"));
	SetFileAttributes("�۱�����.mp3", FILE_ATTRIBUTE_HIDDEN);
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
				if (hour == 8 && minu == 0) playsound("�Ͽ�.mp3");
				if (hour == 8 && minu == 55) playsound("�Ͽ�.mp3");
				if (hour == 10 && minu == 20) playsound("�Ͽ�.mp3");
				if (hour == 11 && minu == 15) playsound("�Ͽ�.mp3");
				if (hour == 13 && minu == 30) playsound("�Ͽ�.mp3");
				if (hour == 14 && minu == 25) playsound("�Ͽ�.mp3");
				if (hour == 15 && minu == 25) playsound("�Ͽ�.mp3");
				if (hour == 16 && minu == 30) playsound("�Ͽ�.mp3");

				if (hour == 8 && minu == 45) playsound("�¿�.mp3");
				if (hour == 9 && minu == 40) playsound("�¿�.mp3");
				if (hour == 11 && minu == 5) playsound("�¿�.mp3");
				if (hour == 12 && minu == 0) playsound("�¿�.mp3");
				if (hour == 14 && minu == 15) playsound("�¿�.mp3");
				if (hour == 15 && minu == 10) playsound("�¿�.mp3");
				if (hour == 16 && minu == 10) playsound("�¿�.mp3");
				if (hour == 17 && minu == 30) playsound("�¿�.mp3");
			}
			if (sec == 20)
			{
				if (hour == 9 && minu == 40) playsound("�۱�����.mp3");
				if (hour == 15 && minu == 10) playsound("�۱�����.mp3");
			}
		}
		else
		{
			if (sec == 0)
			{
				if (hour == 8 && minu == 0) playsound("�Ͽ�.mp3");
				if (hour == 8 && minu == 55) playsound("�Ͽ�.mp3");
				if (hour == 9 && minu == 55) playsound("�Ͽ�.mp3");
				if (hour == 13 && minu == 30) playsound("�Ͽ�.mp3");
				if (hour == 14 && minu == 25) playsound("�Ͽ�.mp3");
				if (hour == 15 && minu == 25) playsound("�Ͽ�.mp3");
				if (hour == 16 && minu == 20) playsound("�Ͽ�.mp3");

				if (hour == 8 && minu == 45) playsound("�¿�.mp3");
				if (hour == 9 && minu == 40) playsound("�¿�.mp3");
				if (hour == 10 && minu == 40) playsound("�¿�.mp3");
				if (hour == 14 && minu == 15) playsound("�¿�.mp3");
				if (hour == 15 && minu == 10) playsound("�¿�.mp3");
				if (hour == 16 && minu == 10) playsound("�¿�.mp3");
				if (hour == 17 && minu == 5) playsound("�¿�.mp3");
			}
			if (sec == 20)
			{
				if (hour == 9 && minu == 40) playsound("�۱�����.mp3");
				if (hour == 15 && minu == 10) playsound("�۱�����.mp3");
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
			MessageBoxA(0, ((mode == 1) ? ("��ǰΪ����Ϣʱ��") : ("��ǰΪ����Ϣʱ��")), edition, MB_OK);
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
			if (KEY_DOWN('J')) playsound("�Ͽ�.mp3");
			if (KEY_DOWN('K')) playsound("�¿�.mp3");
			if (KEY_DOWN('L')) playsound("�۱�����.mp3");
			if (KEY_DOWN('I'))
			{
				mciSendString("stop �Ͽ�.mp3", NULL, 0, NULL);
				mciSendString("stop �¿�.mp3", NULL, 0, NULL);
				mciSendString("stop �۱�����.mp3", NULL, 0, NULL);
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
	thread task03([]() noexcept {if (MessageBoxA(0, "��� \"ȷ��\" ���˳�������", edition, MB_OK) == 1) exit(0); });
	thread task04(Switch_Mode);
	task01.join();
	task02.join();
	task04.join();
	return 0;
}
