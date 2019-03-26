#pragma once
#include "FTP.h"

void Excute(std::vector<std::vector<std::string> > text) {
	std::string _str = std::accumulate(text[line].begin(), text[line].end(), std::string(""));
	std::cout << _str.c_str() << std::endl;
	std::stringstream ss(_str);

	std::vector<std::string> _cmd;
	copy(std::istream_iterator<std::string>(ss),
		std::istream_iterator<std::string>(),
		back_inserter(_cmd));
	
	if (_cmd[0].compare("cd") == 0 && _cmd[1].empty())
		/*cd(_cmd[1]);*/
		std::cout << "Suc" << std::endl;
}

void _TextOut(HDC hdc, std::vector<std::vector<std::string> >  text, std::string loc)    //print text
{
	if (text[line].size() == 0)
	{
		return;
	}
	wchar_t* buf;
	int i = 0;
	conv(text, loc, buf, i);
	TextOut(hdc, 0, 15, buf, i);
	delete[]buf;
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

void conv(std::vector<std::vector<std::string> >  text,std::string __str, wchar_t*& buf, int& size, std::string& cpy) {
	std::string _str = std::accumulate(text[line].begin(), text[line].end(), std::string(""));
	_str.push_back('\0');
	_str.insert(0, ">");
	_str.insert(0, __str.c_str());
	buf = new wchar_t[_str.size()];
	mbstowcs(buf, _str.c_str(), _str.size());
	size = _str.size();
	cpy = _str;
	//std::cout << _str.c_str() << std::endl;
}

void conv(std::vector<std::vector<std::string> >  text, std::string __str, wchar_t*& buf, int& size) {
	std::string _str = std::accumulate(text[line].begin(), text[line].end(), std::string(""));
	_str.push_back('\0');
	_str.insert(0, ">");
	_str.insert(0, __str.c_str());
	buf = new wchar_t[_str.size()];
	mbstowcs(buf, _str.c_str(), _str.size());
	size = _str.size();
	//std::cout << _str.c_str() << std::endl;
}

void conv(std::vector<std::vector<std::string> >  text, wchar_t*& buf, int& size) {
	std::string _str = std::accumulate(text[line].begin(), text[line].end(), std::string(""));
	_str.push_back('\0');
	buf = new wchar_t[_str.size()];
	mbstowcs(buf, _str.c_str(), _str.size());
	size = _str.size();
}

void conv(std::string  text, wchar_t*& buf, int& size) {
	text.push_back('\0');
	buf = new wchar_t[text.size()];
	mbstowcs(buf, text.c_str(), text.size());
	size = text.size();
}

void conv(const char* text, wchar_t*& buf, int& size) {
	buf = new wchar_t[sizeof(text)];
	mbstowcs(buf, text, sizeof(text));
	size = sizeof(text);
}

void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[])
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


void Caret::Update(std::vector<std::vector<std::string> >  text, std::string loc, int  _index)
{
	if (str.size() > 0)
	{
		wchar_t* buf;
		int i;
		std::string cpy, temp;
		conv(text, loc, buf, i, cpy);
		for (int i = 0; i  < _index + loc.size() + 1; i ++)
		{
			temp.push_back(cpy.at(i));
		}
		conv(temp, buf, i);
		GetTextExtentPoint(hdc, buf, i, &size);	
		if (_index != 0) {
			SetCaretPos((size.cx), size.cy);
			//std::cout << fo[_index - 1] << " : " << size.cx << " : "  << fo.size()<< std::endl;
		}
		else
			SetCaretPos(size.cx, size.cy);
		delete[] buf;
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

HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& _g_hWnd) {
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
	_g_hWnd = CreateWindow(TEXT("MyApp"), TEXT("Hi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT
		, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if( !_g_hWnd )
        return E_FAIL;

	ShowWindow(_g_hWnd, SW_SHOW);
	return S_OK;	
}

HRESULT InitDevice(HWND hWnd, LPDIRECT3DDEVICE9& pd3dDevice, LPDIRECT3D9& pD3D) {
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D == NULL)
	{
		CHECK_("g_pD3D");
		return E_FAIL;
	}


	D3DDISPLAYMODE d3ddm;

	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		CHECK_("g_pD3D Get");
		return E_FAIL;
	}


	HRESULT hr;

	if (FAILED(hr = pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		d3ddm.Format, D3DUSAGE_DEPTHSTENCIL,
		D3DRTYPE_SURFACE, D3DFMT_D16)))
	{
		if (hr == D3DERR_NOTAVAILABLE)
			CHECK_("g_pD3D CHECK");
			return E_FAIL;
	}


	D3DCAPS9 d3dCaps;

	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, &d3dCaps)))
	{
		CHECK_("g_pD3D Caps");
		return E_FAIL;
	}


	DWORD dwBehaviorFlags = 0;

	if (d3dCaps.VertexProcessingCaps != 0)
		dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;


	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));

	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		dwBehaviorFlags, &d3dpp, &pd3dDevice)))
	{
		CHECK_("Device");
		return E_FAIL;
	}

	return S_OK;
}

void Capture(LPDIRECT3DDEVICE9& pd3dDevice)
{
	int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	IDirect3DSurface9* pSurface;
	pd3dDevice->CreateOffscreenPlainSurface(width, height,
		D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &pSurface, NULL);
	pd3dDevice->GetFrontBufferData(0, pSurface);
	std::string str("asd.bmp"); wchar_t* buf; int i = 0;
	conv(str, buf, i);
	D3DXSaveSurfaceToFile(buf, D3DXIFF_BMP, pSurface, NULL, NULL);
	pSurface->Release();
	delete[] buf;
}

void render(LPDIRECT3DDEVICE9 pd3dDevice)
{
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_COLORVALUE(0.0f, 1.0f, 0.0f, 1.0f), 1.0f, 0);
	pd3dDevice->BeginScene();

	pd3dDevice->EndScene();

	pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void shutDown(LPDIRECT3DDEVICE9& pd3dDevice, LPDIRECT3D9& pD3D)
{
	if (pd3dDevice != NULL)
		pd3dDevice->Release();
	if (pD3D != NULL)
		pD3D->Release();
}