#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "resource.h"
#include "Commctrl.h"
#include <cstdio>

CONST CHAR* g_LIST_BOX_ITEMS[] = {"This", "is", "my", "first", "List", "Box"};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
	HWND hEditBox = GetDlgItem(hwnd, IDC_EDIT1);
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
			SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

			for (int i = 0; i < sizeof(g_LIST_BOX_ITEMS) / sizeof(g_LIST_BOX_ITEMS[0]); i++)
			{
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_LIST_BOX_ITEMS[i]);
			}
			//https://learn.microsoft.com/en-us/windows/win32/controls/em-setcuebanner
			CHAR sz_buffer[] = {"Введите строку для добавления"};
			SendMessage(hEditBox, EM_SETCUEBANNER, FALSE, (LPARAM)sz_buffer);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			CONST INT SIZE = 256; //byte
			CHAR sz_buffer[SIZE]{}; //string zero
			SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_message[SIZE]{};
			sprintf(sz_message, "Вы выбрали пункт №%i со значением \"%s\"", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDC_ADD:
		{
			CONST INT SIZE = 256;

			CHAR sz_button_text[SIZE]{};
			HWND hAddButton = GetDlgItem(hwnd, IDC_ADD);
			SendMessage(hAddButton, WM_GETTEXT, SIZE, (LPARAM)sz_button_text);

			if (strcmp(sz_button_text, "Add") == 0) //0 - строки одинаковы
			{
				CHAR sz_buffer[SIZE]{};
				SendMessage(hEditBox, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strcmp(sz_buffer, "") != 0)
					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			}

			// Сначала убивается фокус, меняется название кнопки,
			// только после этого происходит переход в блок IDC_ADD

			else if (strcmp(sz_button_text, "Delete") == 0)
			{
				INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				SendMessage(hListBox, LB_DELETESTRING, i, 0);
				HWND hAddButton = GetDlgItem(hwnd, IDC_ADD);
				SendMessage(hAddButton, WM_SETTEXT, 0, (LPARAM)"Add");
			}

			
		}
		case IDC_LIST1:
			switch (HIWORD(wParam))
			{
			case LBN_SETFOCUS:
				{
					HWND hAddButton = GetDlgItem(hwnd, IDC_ADD);
					SendMessage(hAddButton, WM_SETTEXT, 0, (LPARAM)"Delete");
				}
				break;
			/*case LBN_KILLFOCUS:
				{
					HWND hAddButton = GetDlgItem(hwnd, IDC_ADD);
					SendMessage(hAddButton, WM_SETTEXT, 0, (LPARAM)"Add");
				}
				break;*/
			}
			
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