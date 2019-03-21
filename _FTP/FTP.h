#pragma once
/*
Master Sex
Named by µ¿ÈÆ, ÅÂ±Õ
¾Æ¾ß¹Ì šœÄ«
 */

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

#define CHECK std::cout<< "CHECK" << std::endl;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

void conv(std::vector<std::vector<std::string> >  text, wchar_t*& buf, int& size);
void conv(std::string text, wchar_t*& buf, int& size);
void conv(const char* text, wchar_t*& buf, int& size);

void _TextOut(HDC hdc, std::vector<std::vector<std::string> >  text);
void _TextOut(HDC hdc, std::string  text);
void _TextOut(HDC hdc, const char* text);

void WCharToChar(const wchar_t* pwstrSrc, char pstrDest[]);
void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[]);
void Excute(std::vector<std::vector<std::string> > _str);

int isFileOrDir(char *s);

BOOL get(std::string fileName);
BOOL cd(std::string path);
BOOL ls();

std::vector<std::string> getfiles(const std::string &_path);
std::vector<std::string> getfolder();


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
	void Update(std::vector<std::vector<std::string> >  text, int _index);
};