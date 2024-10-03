#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пользователя";

// Процедура окна:
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdSHow)
{
	//hInstance - экземпляр запущенного *.exe-файла нашей программы
	//hPrevInst - НЕ используется
	//LPSTR - Long Pointer To String
	//lpCmdLine - CommandLine (командная строка с параметрами запуска приложения)
	//nCmdShow - режим отображения окна (развёрнуто на весь экран, свёрнуто на панель задач)
	//Префиксы: n...., lp... это Венгерская нотация
	//          n - Number
	//          lp - Long Pointer
	//          h - HINSTANCE

	//MessageBox
	//(
	//	NULL,
	//	"Hello Windows!\nThis is MessegeBox", 
	//	"Window title", 
	//	MB_CANCELTRYCONTINUE | MB_HELP | MB_DEFBUTTON3 |
	//	MB_ICONINFORMATION |
	//	//MB_SYSTEMMODAL
	//	//MB_DEFAULT_DESKTOP_ONLY |
	//	MB_TOPMOST |
	//	MB_RIGHT
	//); 
	//https://learn.microsoft.com/ru-ru/dotnet/api/system.windows.forms.messagebox?view=windowsdesktop-6.0
	//MessegeBox: MB_ICONWARNING , MB_ICONERROR, MB_ICONINFORMATION
	//wchar_t progect->propertis->Advanced->Character Set->Use Multi-Byte Character Set
	// LNK1120 1 unresolved external: Project -> Properties -> Linker -> System -> SubSystem -> Windows (/SUBSYSTEM:WINDOWS)
	//Модальным называется окно которое блокирует родительское окно

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0); //преобразование(DLGPROC) - для того чтобы не подчёркивало DlgProc, либо X86.

	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//hwnd - Handler to Window. Обработчик или дискриптор окна - это число при помощи которого можно обратиться к окну.
	//uMsg - Messege. Сообщение которое отправляется окну.
	//wParam, lParam - это параметры сообщения, у каждого сообщения свой набор параметров.
	//В процедуру окна максимально можно передать четыри параметра сообщения за один вызов.

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//Это сообщение отправляется один раз при инициализации окна
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
	}
		break;
	case WM_COMMAND:    //Обрабатывает нажатие кнопок и другие действия пользователя
		//ResourseID - самое обычное число типа INT
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage((HWND)lParam, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if (strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				if (strcmp(sz_buffer, "") == 0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
			}
			//EN_ - Edit Notofication
		}
		break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//sz - String Zero (NULL Terminated Line - C -string)
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:      //Отправляется при нажатии кнопки закрыть 'X'
		EndDialog(hwnd, 0); //Для того чтобы окно закрывалось крестиком
		//C:\Users\Pro>taskkill /f /im WinAPI.exe (закрыть окно через консоль)
		break;
	}
	return FALSE;
}
