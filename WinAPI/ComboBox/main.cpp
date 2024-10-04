#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "resource.h"
#include <cstdio>

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
				INT i = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
				CONST INT SIZE = 256; //byte
				CHAR sz_buffer[SIZE]{}; //string zero
				SendMessage(hComboBox, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
				CHAR sz_message[SIZE]{};
				sprintf(sz_message, "Вы выбрали пункт №%i со значением \"%s\"", i, sz_buffer);
				//спецификатор %i - целое число
				//спецификатор %s - строка [printf ДОКИ]
				MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
			}
			break;	
		case IDC_CHECK1 && //не нашел документацию по чекбоксу:
		{
			HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
			SendMessage(hComboBox, CB_RESETCONTENT, 0, 0);
			//здесь через цикл комбобокс заполняется по порядку
		}
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
