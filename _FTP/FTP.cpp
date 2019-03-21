#pragma once
#include "FTP.h"

void Excute(std::vector<std::vector<std::string> > _str) {

}

void _TextOut(HDC hdc, std::vector<std::vector<std::string> >  text)    //print text
{
	if (text[line].size() == 0)
	{
		return;
	}
	int i = 0;
	wchar_t* buf;
	conv(text, buf, i);
	TextOut(hdc, 0, 15, buf, i);
	delete[]buf;
}

void _TextOut(HDC hdc, std::string  text)    //print text
{
	if (text.size() == 0)
	{
		return;
	}
	CHECK;
	int i = 0;
	wchar_t* buf;
	conv(text, buf, i);
	TextOut(hdc, 0, 15, buf, i);
	delete[]buf;
}

void _TextOut(HDC hdc, const char* text)    //print text
{
	if (sizeof(text) == 0)
	{
		return;
	}
	int i = 0;
	wchar_t* buf;
	conv(text, buf, i);
	TextOut(hdc, 0, 15, buf, i);
	delete[]buf;
}


void conv(std::vector<std::vector<std::string> >  text, wchar_t*& buf, int& size) {
	std::string _str = std::accumulate(text[line].begin(), text[line].end(), std::string(""));
	buf = new wchar_t[_str.size()];
	mbstowcs(buf, _str.c_str(), _str.size());
	size = _str.size();
}

void conv(std::string  text, wchar_t*& buf, int& size) {
	buf = new wchar_t[text.size()];
	mbstowcs(buf, text.c_str(), text.size());
	size = text.size();
}

void conv(const char* text, wchar_t*& buf, int& size) {
	buf = new wchar_t[sizeof(text)];
	mbstowcs(buf, text, sizeof(text));
	size = sizeof(text);
}

void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[])	// char to LPCWSTR
{
	int nLen = (int)strlen(pstrSrc) + 1;
	mbstowcs(pwstrDest, pstrSrc, nLen);
}


void WCharToChar(const wchar_t* pwstrSrc, char pstrDest[])	// LPCWSTR to char
{
	int nLen = (int)wcslen(pwstrSrc);
	wcstombs(pstrDest, pwstrSrc, nLen + 1);
}


Caret::Caret() {}


void Caret::Update(std::vector<std::vector<std::string> >  text, int _index)
{
	if (str.size() > 0)
	{
		int i = 0;
		wchar_t* buf;
		conv(text, buf, i);
		GetTextExtentPoint(hdc, buf, i, &size);
		SetCaretPos(size.cx - ((i - _index) * 8), size.cy);
	}
}


BOOL cd(std::string path)
{
	std::string _path(CurrentLocation + "\\" + path);
	if (chdir(_path.c_str()) == 0)
	{
		return false;
	}
	CurrentLocation = path;
	return true;
}


BOOL ls()
{
	std::vector<std::string> ls = getfiles(CurrentLocation);

	for (int i = 0; i < ls.capacity(); i++)
	{
		if ((i % 4) == 0)
			std::cout << std::endl;
		std::cout << ls[i] << "  ";
	}
	// std::cout << "Exit" << std::endl;
	return true;
}


BOOL get(std::string fileName)
{
	return true;
}


std::vector<std::string> getfiles(const std::string &_path)
{
	std::vector<std::string> result;
	_finddata_t fd;
	long handle = _findfirst(".\\*.*", &fd);

	if (handle == -1)
	{
		return result;
	}

	int _result = 0;
	do
	{
		result.push_back(fd.name);
		_result = _findnext(handle, &fd);
	} while (_result != -1);

	_findclose(handle);

	return result;
}


std::vector<std::string> getfolder()
{
	std::vector<std::string> files = getfiles(CurrentLocation);
	std::vector<std::string> folderPath;
	char *temp = const_cast<char *>(CurrentLocation.c_str());
	for (int i = 0, index = 0; i < files.capacity(); i++)
	{

		if (files[i].size() < 100)
		{
			if (isFileOrDir(CurrentLocation.find("\\", CurrentLocation.size() - 2) != std::string::npos ? strcpy(temp, (CurrentLocation + files[i]).c_str()) : strcat(strcat(temp, "\\"), files[i].c_str())) == 0)
			{
				std::string _temp(temp);
				folderPath.push_back(_temp.replace(0, 3, ""));
			}
		}

	}
	return folderPath;
}


int isFileOrDir(char *s)
{
	_finddatai64_t c_file;
	intptr_t hFile;
	int result;

	if ((hFile = _findfirsti64(s, &c_file)) == -1L)
		result = -1;
	else if (c_file.attrib & _A_SUBDIR)
		result = 0;
	else
		result = 1;

	_findclose(hFile);

	return result;
}