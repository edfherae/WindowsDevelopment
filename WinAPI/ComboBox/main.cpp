#include <Windows.h>
#include "resource.h"

CONST CHAR* g_COMBO_BOX_ITEMS[] = { "This", "is", "my", "First", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
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
			HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
			SendMessage(hwnd, WM_SETICON, 0,(LPARAM)hIcon);

			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			for (int i = 0; i < sizeof(g_COMBO_BOX_ITEMS) / sizeof(g_COMBO_BOX_ITEMS[0]); i++)
			{
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_COMBO_BOX_ITEMS[i]);
			}
			SendMessage(hCombo, CB_SETCURSEL, 0, 0);
			//CB_SETCURSEL - ComboBox Set Current Selection
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
				HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
				INT index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
				CONST CHAR buffer[100]{};
				SendMessage(hComboBox, CB_GETLBTEXT, 100, (LPARAM)buffer);
				CONST CHAR* sum_buffer[100] = { "Вы выбрали пункт ", (LPCSTR)index, " со значением ", buffer };
				MessageBox(hwnd, sum_buffer[0] + "", "Info", MB_OK | MB_ICONINFORMATION);
			}
			break;	
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
