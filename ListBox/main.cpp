#include<Windows.h>
#include"resource.h"
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

CONST CHAR* g_LIST_BOX_ITEMS[] = { "This", "is", "my", "first", "List", "Box" };

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR LpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_LIST_BOX_ITEMS) / sizeof(g_LIST_BOX_ITEMS[0]); i++)
		{
			SendMessage(hCombo, LB_ADDSTRING, 0, (LPARAM)g_LIST_BOX_ITEMS[i]);
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}