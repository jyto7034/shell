#pragma once
#include "Shell.h"

void convertor(wchar_t*& buf, const char* str) {
	buf = new wchar_t[strlen(str) + 1];
	mbstowcs(buf, str, strlen(str) + 1);
}

void Caret::Update(std::vector<std::vector<std::string> >&  text, std::string Location, int  _index, int  pindex_y, HWND hWnd)
{
	if (str.size() > 0)
	{
		wchar_t* buf;
		std::string _str = std::accumulate(text[0].begin(), text[0].end(), std::string(""));
		_str.push_back('\0');
		_str.insert(0, ">");
		_str.insert(0, Location.c_str());

		convertor(buf, _str.c_str());

		GetTextExtentPoint(hdc, buf, (_str.length() - 1 + _index + 4) / 2, &size);
		if (_index != 0) {
			SetCaretPos(size.cx, pindex_y * 16);
		}
		else
			SetCaretPos(size.cx, pindex_y * 16);
		delete[] buf;
	}
	return;
}


HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& g_hWnd) {
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDC_ICON);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("MyApp");

	RegisterClass(&wc);
	g_hInst = hInstance;
	g_hWnd = CreateWindow(TEXT("MyApp"), TEXT("Hi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT
		, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, SW_SHOW);
	return S_OK;
}


void Excute(std::vector<std::vector<std::string> > text, std::string _CurrentLocation, HWND& hWnd) {
	

	return;
}

void Cleanup() { 
	MsgQue.Releas();
	return; 
}

int isFileOrDir(char* s) { return true; }

std::vector<std::string> getfiles(std::string& _path) {
	std::vector<std::string> result;
	result.push_back(_path);
	result[0].append("\\*.*");
	_finddata_t fd;
	long handle = _findfirst(result[0].c_str(), &fd);

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

std::vector<std::string> getfolder() {
	std::vector<std::string> files = getfiles(CurrentLocation);
	std::vector<std::string> folderPath;
	char* temp = const_cast<char*>(CurrentLocation.c_str());
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

BOOL Sendkey(std::string cmd) { return true; }
BOOL get(std::string fileName) { return true; }
BOOL cd(std::string path) { return true; }
BOOL ls(std::string _CurrentLocation, HWND& hWnd) { return true; }

void _MsgQue::SetData(const char* str, int size) {
	this->len = size;
	wchar_t* buf;
	convertor(buf, const_cast<char*>(str));
	if (inited) {
		this->str = new wchar_t[size + 1];
		inited = true;
	}
	else {
		delete[] this->str;
		this->str = new wchar_t[size + 1];
	}
	wcscpy(this->str, buf);
	delete[] buf;
}

void _MsgQue::Releas() {
	std::cout << "Deleted : ";
	wprintf(this->str);
	std::cout << std::endl;
	delete[] this->str;
	this->len = 0;
}

#pragma region TextManager

void AddTextQue(HDC hdc, std::vector<std::vector<std::string> >  text, std::string loc)
{
	if (text[0].size() == 0)
		return;

 	std::string _str = std::accumulate(text[0].begin(), text[0].end(), std::string(""));
	_str.push_back('\0');
	_str.insert(0, ">");
	_str.insert(0, loc.c_str());

	MsgQue.SetData(_str.c_str(), strlen(_str.c_str()));
}

void TEXTOUT(HDC hdc, HWND hWnd, int pIndex_y) {
	if (MsgQue.len - (CurrentLocation.length()) == 1) {
		wcscpy(MsgQue.str, L"");
		wchar_t* buf;
		convertor(buf, CurrentLocation.c_str());
		TextOut(hdc, 0, pIndex_y * 16, buf, CurrentLocation.length());
		delete[] buf;
	}
	else
		TextOut(hdc, 0, pIndex_y * 16, MsgQue.str, MsgQue.len);
}

#pragma endregion