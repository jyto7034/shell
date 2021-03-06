﻿#include "Shell.h"

int APIENTRY WinMain(HINSTANCE hIns, HINSTANCE PrevIns, LPSTR cmd, int cmdShow)
{
	if (FAILED(InitWindow(hIns, cmdShow, g_hWnd)))
		return 0;

	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, g_hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
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
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, TRANSPARENT);
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
			std::cout << index << std::endl;
		}
		if (wParam == VK_RIGHT) {
			index += 1;
			std::cout << index << std::endl;
		}
		GetClientRect(g_hWnd, &WindowSize);
		//ValidateRect(hWnd, &WindowSize);
		//std::cout << " KEYDOWN " <<WindowSize.bottom -  << std::endl;
		//ValidateRect(hWnd, new RECT{ WindowSize.left, WindowSize.top / 2, WindowSize.right, WindowSize.bottom / 2 });
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}

	case WM_CHAR:
	{
		if (wParam == VK_BACK) {
			if (str.size() > 0 && index != 0) {
				str[	0].erase(str[0].begin() + index - 1, str[0].begin() + index);
				#pragma region Debug
				//for (int i = 0; i < str[0].size(); i++) {
				//	std::cout << str[0][i];
				//}
#pragma endregion
				index -= 1;
			}
			break;
		}
		if (wParam == VK_RETURN) {
			Excute(str, CurrentLocation, hWnd);
			index_y++;
		}
		else {
			std::string s; s.push_back((char)wParam);
			str[0].push_back(s);
			index++;
			#pragma region Debug
			//for (int i = 0; i < str[0].size(); i++) {
			//	std::cout << str[0][i];
			//}
			//std::cout << std::endl;
#pragma endregion
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		AddTextQue(hdc, str, CurrentLocation);
		TEXTOUT(hdc, hWnd, index_y);
		cr.Update(str, CurrentLocation, index, index_y, hWnd);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY: {
		Cleanup();
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;
	}

	default:
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}