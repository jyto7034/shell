#pragma once
/*
Named by µ¿ÈÆ, ÅÂ±Õ
¾Æ¾ß¹Ì šœÄ«
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

#pragma comment(lib, "dxgi.lib")

#define CHECK std::cout<< "CHECK" << std::endl;
#define CHECK_(x) std::cout<< x << std::endl;
#define HBYTES(w, b)  ((((w) * (b) + 31) & ~31) / 8)
#define BUFSIZE 33177656
						// 14745656
						                   
#define LINE 0

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

void conv(std::vector<std::vector<std::string> >  text, std::string __str, wchar_t*& buf, int& size, std::string& cpy);
void conv(std::vector<std::vector<std::string> >  text, std::string __str, wchar_t*& buf, int& size);
void conv(std::vector<std::vector<std::string> >  text, wchar_t*& buf, int& size);
void conv(const char* text, wchar_t*& buf, int& size);
void conv(std::string text, wchar_t*& buf, int& size);

void _TextOut(HDC hdc, std::vector<std::vector<std::string> >  text, std::string _str);
void _TextOut(HDC hdc, std::vector<std::vector<std::string> >  text);
void _TextOut(HDC hdc, std::string  text);
void _TextOut(HDC hdc, const char* text);

void WCharToChar(const wchar_t* pwstrSrc, char pstrDest[]);
void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[]);
void Excute(std::vector<std::vector<std::string> > _str);

void shutDown(LPDIRECT3DDEVICE9& pd3dDevice, LPDIRECT3D9& pD3D);
void Capture(LPDIRECT3DDEVICE9& pd3dDevice);
void render(LPDIRECT3DDEVICE9 pd3dDevice);
void com(char*& a, char*& b, int size, std::string& out);


int isFileOrDir(char *s);


HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& g_hWnd);
HRESULT InitDevice(HWND hWnd, LPDIRECT3DDEVICE9& pd3dDevice, LPDIRECT3D9& pD3D);


std::vector<std::string> getfiles(const std::string &_path);
std::vector<std::string> getfolder();


BOOL get(std::string fileName);
BOOL cd(std::string path);
BOOL ls();


static LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
static LPDIRECT3D9       g_pD3D = NULL;
static HWND g_hWnd = NULL;
static HINSTANCE g_hInst;


static std::vector<std::vector<std::string> > str(50);
static PAINTSTRUCT ps;
static int index;
static SIZE size;


static std::string CurrentLocName;
static std::string CurrentLocation;
static std::vector<char> input;
static std::string cmd;


class Caret {
public:
	Caret();
	Caret(HDC _hdc) : hdc(_hdc) { };
	HDC hdc;
	void Update(std::vector<std::vector<std::string> >  text, std::string str, int _index);
};