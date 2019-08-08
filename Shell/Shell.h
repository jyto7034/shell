#pragma once
#include <strsafe.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include <direct.h>
#include <io.h>
#include <numeric>
#include <atlbase.h>
#include <comdef.h>
#include <time.h>
#include <memory>

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& g_hWnd);

void Excute(std::vector<std::vector<std::string> > text, std::string _CurrentLocation, HWND& hWnd);
void Cleanup();
int isFileOrDir(char* s);

void AddTextQue(HDC hdc, std::vector<std::vector<std::string> >  text, std::string loc);
void TEXTOUT(HDC hdc, HWND hWnd, int pIndex_y);

std::vector<std::string> getfiles(std::string& _path);
std::vector<std::string> getfolder();

BOOL Sendkey(std::string cmd);
BOOL get(std::string fileName);
BOOL cd(std::string path);
BOOL ls(std::string _CurrentLocation, HWND& hWnd);

void convertor(wchar_t*& buf, const char* str);

class Caret {
public:
	Caret(HDC _hdc) : hdc(_hdc) { };
	HDC hdc;
	void Update(std::vector<std::vector<std::string> >&  text, std::string str, int _index, int  pindex_y, HWND hWnd);
};

class _MsgQue {
public:
	_MsgQue() : len(0), inited(false), str(NULL) {}
	void SetData(const char* str, int size);
	void Releas();

	//void operator=(const _MsgQue& msg) {
	//	wchar_t* buf = new wchar_t[this->len];
	//	wcscpy(buf, msg.str);
	//	this->len = msg.len;
	//}

	int len;
	wchar_t* str;
	bool inited;
};

static HWND g_hWnd = NULL;
static HINSTANCE g_hInst;

static std::vector<std::vector<std::string> > str(50);
static PAINTSTRUCT ps;
static int index_y;
static int index;
static int height;
static int width;
static SIZE size;

//static std::vector<_MsgQue> MsgQue;
static _MsgQue MsgQue;
static std::string CurrentLocation = "C:\\";
static std::string cmd;

static BOOL ToServer;
static BOOL Remote;

static RECT WindowSize;