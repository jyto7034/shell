#include"FTP.h"

int APIENTRY WinMain(HINSTANCE hIns, HINSTANCE PrevIns, LPSTR cmd, int cmdShow)
{
	HWND hWnd;
	WNDCLASS wc;
	MSG msg;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hIns;
	wc.hIcon = LoadIcon(NULL, IDC_ICON);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("MyApp");

	RegisterClass(&wc);

	hWnd = CreateWindow(TEXT("MyApp"), TEXT("Hi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT
		, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hIns, NULL);

	ShowWindow(hWnd, SW_SHOW);
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hWnd);
	Caret cr(hdc);
	switch (iMsg)
	{
	case WM_CREATE:
	{
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		AllocConsole();
		freopen("CONOUT$", "wb", stdout);
		CurrentLocation = "C:\\";
		index = 0;
		break;
	}

	case WM_KEYDOWN:
	{
		if (wParam == VK_LEFT) {
			index -= 1;
			//std::cout << index << std::endl;
		}
		if (wParam == VK_RIGHT) {
			index += 1;
			//std::cout << index << std::endl;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}

	case WM_CHAR:
	{
		if (wParam == VK_BACK) {
			if (str.size() > 0 && index != 0) {
				str[line].erase(str[line].begin() + index - 1, str[line].begin() + index);
				index -= 1;
			}
			break;
		}
		if (wParam == VK_RETURN) {
			Excute(str);
		}
		else {
			char temp = wParam;
			std::string s; s.push_back(temp);
			str[line].push_back(s);
			//std::cout << index << std::endl;
			index++;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, TRANSPARENT);
		_TextOut(hdc, str, CurrentLocation);
		cr.Update(str, CurrentLocation, index);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);

	default:
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}