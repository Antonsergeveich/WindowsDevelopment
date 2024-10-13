#include<Windows.h>
#include"Calc.h"
#include<WinUser.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc";

CONST INT g_BUTTON_SIZE = 75;
CONST INT g_INTERVAL = 2;
CONST INT g_BUTTON_DOUBLE_SIZE = g_BUTTON_SIZE * 2 + g_INTERVAL;
CONST INT g_START_X = 10;
CONST INT g_START_Y = 10;
CONST INT g_DISPLAY_WIDTH = g_BUTTON_SIZE * 5 + g_INTERVAL * 4;
CONST INT g_DISPLAY_HEIGHT = 25;
CONST INT g_BUTTON_START_X = g_START_X;
CONST INT g_BUTTON_START_Y = g_START_Y + g_DISPLAY_HEIGHT + g_INTERVAL;
CONST INT g_OPERATIONS_START_X = g_START_X + (g_BUTTON_SIZE + g_INTERVAL) * 3;
CONST INT g_OPERATIONS_START_Y = g_BUTTON_START_Y;
CONST INT g_CONTROL_BUTTONS_START_X = g_START_X + (g_BUTTON_SIZE + g_INTERVAL) * 4;
CONST INT g_CONTROL_BUTTONS_START_Y = g_BUTTON_START_Y;

CONST CHAR g_OPERATIONS[] = "*/-+";

BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(CALC_ICON));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
	
	case WM_CREATE:
	{
		HWND hEditDisplay = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_RIGHT,
			g_START_X, g_START_Y,
			g_DISPLAY_WIDTH, g_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);

		CHAR sz_digit[2]{};
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = i + j + 49;
				CreateWindowEx(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE,
					g_BUTTON_START_X + (g_BUTTON_SIZE + g_INTERVAL) * j, g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * (2 - i / 3),
					g_BUTTON_SIZE, g_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1 + i + j),
					GetModuleHandle(NULL),
					NULL
				);
				CreateWindowEx(
					NULL, "Button", ".",
					WS_CHILD | WS_VISIBLE,
					g_BUTTON_START_X + g_BUTTON_DOUBLE_SIZE + g_INTERVAL,
					g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 3,
					g_BUTTON_SIZE, g_BUTTON_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_POINT,
					GetModuleHandle(NULL),
					NULL
				);
				CHAR sz_operation[2]{};
				for (int i = 0; i < 4; i++)
				{
					sz_operation[0] = g_OPERATIONS[i];
					CreateWindowEx
					(
						NULL, "Button", sz_operation,
						WS_CHILD | WS_VISIBLE,
						g_OPERATIONS_START_X, g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * i,
						g_BUTTON_SIZE, g_BUTTON_SIZE,
						hwnd,
						(HMENU)IDC_BUTTON_PLUS + i,
						GetModuleHandle(NULL),
						NULL
					);
				}
				CreateWindowEx
				(
					NULL, "Button", "<-",
					WS_CHILD | WS_VISIBLE,
					g_CONTROL_BUTTONS_START_X, g_CONTROL_BUTTONS_START_Y,
					g_BUTTON_SIZE, g_BUTTON_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_BSP,
					GetModuleHandle(NULL),
					NULL
				);
				CreateWindowEx(
					NULL, "Button", "C",
					WS_CHILD | WS_VISIBLE,
					g_CONTROL_BUTTONS_START_X, g_CONTROL_BUTTONS_START_Y + g_BUTTON_SIZE + g_INTERVAL,
					g_BUTTON_SIZE, g_BUTTON_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_CLEAR,
					GetModuleHandle(NULL),
					NULL
				);
				CreateWindowEx
				(
					NULL, "Button", "=",
					WS_CHILD | WS_VISIBLE,
					g_CONTROL_BUTTONS_START_X, g_CONTROL_BUTTONS_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 2,
					g_BUTTON_SIZE, g_BUTTON_DOUBLE_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_EQUAL,
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE,
			g_BUTTON_START_X, g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 3,
			g_BUTTON_DOUBLE_SIZE, g_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
	}
	break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256;
		CHAR sz_display[SIZE]{};
		CHAR sz_digit[2]{};
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + 48;
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if ((sz_display[0]) == '0' && sz_display[1] != '.')sz_display[0] = 0;
			strcat(sz_display, sz_digit); //Функция strcat(dst, src) выполняет конкотенацию строк,
			//а именно, к строке dst (Destination -Получатель) добавляет содержимое строки src (Source - источник)
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (strchr(sz_display, '.'))break;
			strcat(sz_display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (strlen(sz_display) == 1)sz_display[0] = '0';
			else sz_display[strlen(sz_display) - 1] = 0;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			sz_display[0] = '0';
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	//wClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\calc.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\calc.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance,
		"CUR\\starcraft-original\\Normal Select.ani",
		IMAGE_CURSOR,
		LR_DEFAULTSIZE,
		LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,  //ExStayle
		g_sz_WINDOW_CLASS,   //Class name
		g_sz_WINDOW_CLASS,   //Window title
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME - WS_MAXIMIZEBOX, //Window style
		CW_USEDEFAULT, CW_USEDEFAULT,  //Position
		g_DISPLAY_WIDTH + g_BUTTON_START_X * 2 + 16,
		g_DISPLAY_HEIGHT + (g_BUTTON_SIZE + g_INTERVAL) * 4 + g_START_Y * 2 + 16 + 23,  //Size
		NULL, //Parent
		NULL, //Menu
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message;
}
