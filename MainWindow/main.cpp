#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<string>

#define IDC_STATIC  1000 //1) Создаём ResourceID для дочернего элемента
#define IDC_EDIT    1001
#define IDC_BUTTON  1002

CONST CHAR g_sz_WINDOW_CLASS[] = "Main Window"; // Имя класса окна.

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	// 1.1 Создать и проинециализировать структуру WNDCLASSEX:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);// cb - Count Bytes
	wClass.cbClsExtra = 0;// Class Extra Bytes
	wClass.cbWndExtra = 0;// Window Extra Bytes

	//Appearance:
	//wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  //Small icon
	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\chip.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\photo.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	//wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance,
		"CUR\\starcraft-original\\Busy.ani",
		IMAGE_CURSOR,
		LR_DEFAULTSIZE,
		LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);

	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;

	// 1.2 Вызвать функцию RegisterClassEx(....):
	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2)Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL, //Window ExStyle
		g_sz_WINDOW_CLASS, //Window Class Name
		g_sz_WINDOW_CLASS,  // Window Title
		WS_OVERLAPPED | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, //Window Style
		CW_USEDEFAULT, CW_USEDEFAULT, // Coordinates
		CW_USEDEFAULT, CW_USEDEFAULT, // Window size
		NULL, //Parent
		NULL, //hMenu: Для главного окна это ResourceID главного меню,
		//для дочернего окна (кнопки и другие элементы)
		//  - это ResourceID - ресурса соответствующего элемента
		// По этому ResourceID мы находим дочерний элемент окна при помощи функции GetDlgItem()
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); // Задает режим отображения окна (развернуто на весь экран, свернуто
	UpdateWindow(hwnd);//Отправляет сообщение. Прорисовывает окно.
	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		CreateWindowEx
		(
			NULL, "Static",
			"Это static_text, детка",
			WS_CHILD | WS_VISIBLE,  //Для всех дочерних окон стиль обязательно будет WS_CHILD (это как минимум)
			100, 10,
			200, 20,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx(
			NULL, "Edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 30,
			200, 20,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx(
			NULL, "Button", "Применить",
			WS_CHILD | WS_VISIBLE,
			200, 55, 
			100, 32,
			hwnd,
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL
		);
			break;
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CONST INT SIZE = 256;
		CHAR buffer[SIZE]{};
		sprintf
		(
			buffer, "%s   Position: %i x %i, Size: %i x %i",
			g_sz_WINDOW_CLASS,
			rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			HWND hStatic = GetDlgItem(hwnd, IDC_STATIC);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_CLOSE:DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}
