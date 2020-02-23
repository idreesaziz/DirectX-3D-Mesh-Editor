#include "pch.h"
//#include "cWindow.h"
//
//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//void cWindow::CreateInstance(RECT rc, HINSTANCE hInstance, const char * windowTitle, int nCmdShow)
//{
//	WNDCLASSEX wc;
//	ZeroMemory(&wc, sizeof(WNDCLASSEX));
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = WndProc;
//	wc.hInstance = hInstance;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)0;
//	wc.lpszClassName = "WindowClass1";
//
//	// Registering the window class
//	RegisterClassEx(&wc);
//
//	// Creating the window
//	hWnd = CreateWindowEx(NULL,
//		"WindowClass1",
//		windowTitle,
//		WS_OVERLAPPEDWINDOW,
//		rc.left,
//		rc.top,
//		rc.right,
//		rc.bottom,
//		NULL,
//		NULL,
//		hInstance,
//		NULL);
//
//	// displaying the window
//	ShowWindow(hWnd, nCmdShow);
//
//}
//
//LRESULT cWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	//Interpreting the windows message
//	switch (message)
//	{
//		// Mouse events
//	case WM_LBUTTONDOWN:
//		if (Callback)Callback(Event::MOUSE_PRESSED, 1);
//		break;
//
//	case WM_RBUTTONDOWN:
//		if (Callback)Callback(Event::MOUSE_PRESSED, 2);
//		break;
//
//	case WM_LBUTTONUP:
//		if (Callback)Callback(Event::MOUSE_RELEASED, 1);
//		break;
//
//	case WM_RBUTTONUP:
//		if (Callback)Callback(Event::MOUSE_RELEASED, 2);
//		break;
//
//	case WM_MOUSEHWHEEL:
//		break;
//
//	case WM_MOUSEMOVE:
//		if (Callback)Callback(Event::MOUSE_MOVE, 0);
//		break;
//		//.....................................................
//
//
//	//Keyboard events
//	case WM_KEYDOWN:
//		if (Callback)Callback(Event::KEY_PRESSED, wParam);
//		break;
//
//	case WM_KEYUP:
//		if (Callback)Callback(Event::KEY_RELEASED, wParam);
//		break;
//		//.....................................................
//
//
//	//Window events
//	case WM_SIZE:
//		if (Callback)Callback(Event::WINDOW_RESIZE, 0);
//
//		break;
//
//	case WM_DESTROY:
//		if (Callback)Callback(Event::WINDOW_DESTROY, 0);
//		break;
//		//.....................................................
//
//		if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
//			return true;
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//}
//
//cWindow::cWindow()
//{
//}
//cWindow::~cWindow()
//{
//}