#pragma once
/*
Named by ����, �±�
�ƾ߹� ��ī
 */

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dcompiler.h>
#include <gdiplus.h>
#include <strsafe.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>
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

#pragma comment(lib, "dxgi.lib")

#define CHECK std::cout<< "CHECK" << std::endl;
#define CHECK_(x) std::cout<< x << std::endl;
#define CT(x) std::cout<< x << std::endl;
#define CT(x, y) std::cout<< x << " : " << y << std::endl;
#define WIDTHBYTES(bits)

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void conv(std::vector<std::vector<std::string> >  text, std::string __str, wchar_t*& buf, int& size, std::string& cpy);
void conv(std::vector<std::vector<std::string> >  text, std::string __str, wchar_t*& buf, int& size);
void conv(std::vector<std::vector<std::string> >  text, wchar_t*& buf, int& size);
void conv(std::string text, wchar_t*& buf, int& size);
void conv(const char* text, wchar_t*& buf, int& size);

void _TextOut(HDC hdc, std::vector<std::vector<std::string> >  text, std::string _str);
void _TextOut(HDC hdc, std::vector<std::vector<std::string> >  text);
void _TextOut(HDC hdc, std::string  text);
void _TextOut(HDC hdc, const char* text);

void WCharToChar(const wchar_t* pwstrSrc, char pstrDest[]);
void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[]);
void Excute(std::vector<std::vector<std::string> > _str);
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& g_hWnd);
HRESULT InitDevice(HWND hWnd, LPDIRECT3DDEVICE9& pd3dDevice);

void Capture();
void render();
void shutDown();

int isFileOrDir(char *s);

BOOL get(std::string fileName);
BOOL cd(std::string path);
BOOL ls();

std::vector<std::string> getfiles(const std::string &_path);
std::vector<std::string> getfolder();

static HWND g_hWnd = NULL;
static HINSTANCE g_hInst;
static LPDIRECT3D9       g_pD3D = NULL;
static LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

static std::vector<std::vector<std::string> > str(50);
static int line = 0;
static PAINTSTRUCT ps;
static SIZE size;
static int index;
static std::string Seleted;

static std::string CurrentLocation;
static std::string CurrentLocName;
static std::vector<char> input;
static std::string cmd;

class Caret {
public:
	Caret();
	Caret(HDC _hdc) : hdc(_hdc) { };
	HDC hdc;
	void Update(std::vector<std::vector<std::string> >  text, std::string str, int _index);
};