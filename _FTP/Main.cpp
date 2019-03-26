#include"FTP.h"

int APIENTRY WinMain(HINSTANCE hIns, HINSTANCE PrevIns, LPSTR cmd, int cmdShow)
{
	SetProcessDPIAware();
	if (FAILED(InitWindow(hIns, cmdShow, g_hWnd)))
		return 0;

	if (FAILED(InitDevice(g_hWnd, g_pd3dDevice, g_pD3D)))
		return 0;

	//if (g_pd3dDevice == NULL) {
	//	getch();
	//	return 0;
	//}

	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, g_hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			render(g_pd3dDevice);
		}
	}

	shutDown(g_pd3dDevice, g_pD3D);

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
		Capture(g_pd3dDevice);
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);

	default:
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
