#include "pch.h"
#include "Window.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static bool Mouse[3] = { false };
static bool KeyDown[1024] = { false };
static int  Param = -1;

// Window callbacks
static void(*WindowCallback)(EventType EType) = nullptr;
static void(*MouseCallback)(EventType EType) = nullptr;
static void(*KeyCallback)(EventType EType) = nullptr;
static unsigned int w = NULL;
static unsigned int h = NULL;


void CWindow::UpdateDeltaTime()
{
	DeltaTime = CurrentTime - LastTime;
	LastTime = CurrentTime;
}

void CWindow::InitializeWindow(RECT rc,
	HINSTANCE hInstance,
	const char* WindowClassName,
	const char* windowTitle,
	int windowColor,
	int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)windowColor;
	wc.lpszClassName = WindowClassName;

	// Registering the window class
	RegisterClassEx(&wc);

	// Creating the window
	hWnd = CreateWindowEx(NULL,
		WindowClassName,
		windowTitle,
		WS_OVERLAPPEDWINDOW,
		rc.left,
		rc.top,
		rc.right,
		rc.bottom,
		NULL,
		NULL,
		hInstance,
		NULL);
	WindowWidth = rc.right;
	WindowHeight = rc.bottom;

	// displaying the window
	ShowWindow(hWnd, nCmdShow);

}

void CWindow::BeginTick(void(*ETick)())
{
	while (WM_QUIT != msg.message)
	{
		while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		GetCursorPos(&CurrentMousePosition);
		CurrentTime = std::chrono::system_clock::now();
		UpdateDeltaTime();

		ETick();
	}
}

// Setters...
void CWindow::SetWindowCallback(void(*winodwCallback)(EventType EType))
{
	if (winodwCallback)WindowCallback = winodwCallback;
}
void CWindow::SetMouseCallback(void(*mouseCallback)(EventType EType))
{
	if (mouseCallback)MouseCallback = mouseCallback;
}
void CWindow::SetKeyCallback(void(*keyCallback)(EventType EType))
{
	if (keyCallback)KeyCallback = keyCallback;
}

void CWindow::CreateLogWindow()
{

}

double CWindow::GetDeltaTime()
{
	return DeltaTime.count();
}

POINT CWindow::GetDeltaMousePosition()
{
	POINT DeltaPos = { CurrentMousePosition.x - LastMousePosition.x,
					  CurrentMousePosition.y - LastMousePosition.y };
	LastMousePosition = CurrentMousePosition;
	return DeltaPos;
}

// Getters
unsigned int CWindow::GetWindowHeight() { return h; }
unsigned int CWindow::GetWindowWidth() { return w; }

const bool * CWindow::GetKeys()
{
	return KeyDown;
}

const bool * CWindow::GetMouse()
{
	return Mouse;
}

RECT CWindow::GetDesktopReoslution()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	return desktop;
}
HWND* CWindow::GetHWindow() { return &hWnd; }
MSG* CWindow::GetMsg() { return &msg; }

CWindow::CWindow()
{
}


CWindow::~CWindow()
{
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//Interpreting the windows message
	switch (message)
	{
		// Mouse events
	case WM_LBUTTONDOWN:
		Mouse[MOUSE1] = true;
		if (MouseCallback)MouseCallback(EventType::MOUSE_PRESSED);
		break;

	case WM_RBUTTONDOWN:
		Mouse[MOUSE2] = true;
		if (MouseCallback)MouseCallback(EventType::MOUSE_PRESSED);
		break;

	case WM_LBUTTONUP:
		Mouse[MOUSE1] = false;
		break;

	case WM_RBUTTONUP:
		Mouse[MOUSE2] = false;
		break;

	case WM_MOUSEHWHEEL:
		break;

	case WM_MOUSEMOVE:
		if (MouseCallback) MouseCallback(EventType::MOUSE_MOVE);
		break;
		//.....................................................


		//Keyboard events
	case WM_KEYDOWN:
		KeyDown[wParam] = true;
		if (KeyCallback)KeyCallback(EventType::KEY_PRESSED);
		break;

	case WM_KEYUP:
		KeyDown[wParam] = false;
		if (KeyCallback)KeyCallback(EventType::KEY_RELEASED);
		break;
		//.....................................................


		//Window events
	case WM_SIZE:
	{
		RECT rc;
		GetWindowRect(hWnd, &rc);
		h = rc.bottom - rc.top;
		w = rc.right - rc.left;
		if (WindowCallback) WindowCallback(EventType::WINDOW_RESIZE);
	}
	break;

	case WM_DESTROY:
		if (WindowCallback)WindowCallback(EventType::WINDOW_DESTROY);
		break;
		//.....................................................
	}

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
	return DefWindowProc(hWnd, message, wParam, lParam);
}