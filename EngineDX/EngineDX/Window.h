#pragma once

#define MOUSE1								1
#define MOUSE2								2
#define MOUSE3								3
// Key codes
#define KEY_BACKSPACE 						8 
#define KEY_TAB 							9 
#define KEY_ENTER 							13 
#define KEY_SHIFT 							16 
#define KEY_CTRL 							17 
#define KEY_ALT 							18 
#define KEY_BREAK 							19 
#define KEY_CAPSLOCK 						20 
#define KEY_ESCAPE 							27 
#define KEY_SPACE	 						32 
#define KEY_PAGE_UP 						33 
#define KEY_PAGE_DOWN 						34 
#define KEY_END 							35 
#define KEY_HOME 							36 
#define KEY_LEFT_ARROW 						37 
#define KEY_UP_ARROW 						38 
#define KEY_RIGHT_ARROW 					39 
#define KEY_DOWN_ARROW 						40 
#define KEY_INSERT 							45 
#define KEY_DELETE 							46 
#define KEY_0 								48 
#define KEY_1 								49 
#define KEY_2 								50 
#define KEY_3 								51 
#define KEY_4 								52 
#define KEY_5 								53 
#define KEY_6 								54 
#define KEY_7 								55 
#define KEY_8 								56 
#define KEY_9 								57 
#define KEY_A 								65 
#define KEY_B 								66 
#define KEY_C 								67 
#define KEY_D 								68
#define KEY_E 								69 
#define KEY_F 								70 
#define KEY_G 								71 
#define KEY_H 								72 
#define KEY_I 								73 
#define KEY_J 								74 
#define KEY_K 								75 
#define KEY_L 								76 
#define KEY_M 								77 
#define KEY_N 								78 
#define KEY_O 								79 
#define KEY_P 								80 
#define KEY_Q 								81 
#define KEY_R 								82 
#define KEY_S 								83 
#define KEY_T 								84 
#define KEY_U 								85 
#define KEY_V 								86 
#define KEY_W 								87 
#define KEY_X 								88 
#define KEY_Y 								89 
#define KEY_Z 								90 
#define KEY_LEFT_WINDOW 					91 
#define KEY_RIGHT_WINDOW	 				92 
#define KEY_SELECT	 						93 
#define KEY_MULTIPLY 						106 
#define KEY_ADD 							107 
#define KEY_SUBTRACT 						109 
#define KEY_DECIMAL		 					110 
#define KEY_DIVIDE 							111 
#define KEY_F1 								112 
#define KEY_F2 								113 
#define KEY_F3 								114 
#define KEY_F4 								115 
#define KEY_F5 								116 
#define KEY_F6 								117 
#define KEY_F7 								118 
#define KEY_F8 								119 
#define KEY_F9 								120 
#define KEY_F10 							121 
#define KEY_F11 							122 
#define KEY_F12 							123 
#define KEY_SEMICOLON 						186 
#define KEY_EQUAL	 						187 
#define KEY_COMMA 							188 
#define KEY_DASH 							189 
#define KEY_PERIOD 							190 
#define KEY_FORWARD_SLASH 					191 
#define KEY_OPEN_BRACKET 					219 
#define KEY_BACK_SLASH 						220
#define KEY_CLOSE_BRAKET 					221 
#define KEY_SINGLE_QUOTE 					222 

enum class EventType
{
	KEY_PRESSED,
	KEY_RELEASED,
	MOUSE_PRESSED,
	MOUSE_RELEASED,
	MOUSE_WHEEL_UP,
	MOUSE_WHEEL_DOWN,
	MOUSE_MOVE,
	WINDOW_RESIZE,
	WINDOW_DESTROY
};


// call int WINAPI WinMain before calling the initWindow method

class CWindow
{
private:
	HWND hWnd;
	MSG msg;
	unsigned int WindowHeight	= NULL;
	unsigned int WindowWidth	= NULL;
	bool FirstTick = true;
	std::chrono::system_clock::time_point CurrentTime;
	std::chrono::system_clock::time_point LastTime;
	std::chrono::duration<double> DeltaTime = (std::chrono::duration<double>)0;
	POINT CurrentMousePosition;
	POINT LastMousePosition;

public:
	void InitializeWindow(RECT rc,
		HINSTANCE hInstance,
		const char* WindowClassName,
		const char* windowTitle,
		int windowColor,
		int nCmdShow);

	// Setters
	void BeginTick(void (*ETick)());
	void SetWindowCallback(void(*destroyCallback)(EventType EType));
	void SetMouseCallback(void(*mouseCallback)(EventType EType));
	void SetKeyCallback(void(*keyCallback)(EventType EType));
	void CreateLogWindow();
	void UpdateDeltaTime();
	double GetDeltaTime();
	POINT GetDeltaMousePosition();
	

	//Getters
	unsigned int GetWindowHeight();
	unsigned int GetWindowWidth();
	const bool* GetKeys();
	const bool* GetMouse();
	RECT GetDesktopReoslution();
	HWND* GetHWindow();
	MSG* GetMsg();

	CWindow();
	~CWindow();
};


