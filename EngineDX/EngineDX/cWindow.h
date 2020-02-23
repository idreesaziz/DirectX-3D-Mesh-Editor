#pragma once
//
//enum class Event
//{
//	KEY_PRESSED,
//	KEY_RELEASED,
//	MOUSE_PRESSED,
//	MOUSE_RELEASED,
//	MOUSE_WHEEL_UP,
//	MOUSE_WHEEL_DOWN,
//	MOUSE_MOVE,
//	WINDOW_RESIZE,
//	WINDOW_DESTROY
//};
//
//class cWindow
//{
//private:
//	HWND hWnd;
//	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//	static void(*Callback)(Event e, unsigned int param);
//	POINT CurrentMousePosition;
//	POINT LastMousePosition;
//
//public:
//	void CreateInstance(
//		RECT rc,
//		HINSTANCE hInstance,
//		const char* windowTitle,
//		int nCmdShow);
//
//	cWindow();
//	~cWindow();
//};
//
//