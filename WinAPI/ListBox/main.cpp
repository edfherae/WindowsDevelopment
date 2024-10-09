#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "resource.h"
#include "Commctrl.h"
#include <cstdio>

CONST CHAR g_sz_BUTTON_ADD[] = "Add";
CONST CHAR g_sz_BUTTON_DELETE[] = "Delete";

CONST CHAR* g_LIST_BOX_ITEMS[] = {"This", "is", "my", "first", "List", "Box"};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcChange(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
	//HWND hEditBox = GetDlgItem(hwnd, IDC_EDIT1);
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
			//SendMessage(hEditBox, EM_SETCUEBANNER, FALSE, (LPARAM)sz_buffer);
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
		case IDC_LIST1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				//CONST INT SIZE = 256;
				//CHAR sz_buffer[SIZE]{};
				//INT i = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);
				//SendMessage((HWND)lParam, LB_GETTEXT, SIZE, (LPARAM)sz_buffer);
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_EDIT), hwnd, (DLGPROC)DlgProcChange, 0);
				//GetModuleHandle(NULL) - hInstance запущенной программы
			}
		}
		break;
		//case WM_LBUTTONDBLCLK:
		//	/*if (HIWORD(wParam) == LBN_SETFOCUS)
		//	{
		//		DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_EDIT), hwnd, (DLGPROC)DlgProcEdit, 0);
		//	}*/
		//	break;
		case IDC_BUTTON_ADD:
		{
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, (DLGPROC)DlgProcAdd, 0);
		}
			break;
		case IDC_BUTTON_DELETE:
		{
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
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

BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, IDC_EDIT1));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDOK:
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE]{};
				SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				HWND hParent = GetParent(hwnd); //получаем родительское окно
				HWND hListBox = GetDlgItem(hParent, IDC_LIST1);
				if (sz_buffer[0] == '\0' || sz_buffer[0] == ' ')MessageBox(hwnd, "Нельзя добавлять пустые строки", "Error", MB_OK | MB_ICONEXCLAMATION);
				else if (SendMessage(hListBox, LB_FINDSTRING, -1, (LPARAM)sz_buffer) == LB_ERR)
					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
				else MessageBox(hwnd, "Такое значение уже есть в списке", "Info", MB_OK | MB_ICONINFORMATION);

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

BOOL CALLBACK DlgProcChange(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"Изменить");
		SendMessage(GetDlgItem(hwnd, IDOK), WM_SETTEXT, 0, (LPARAM)"Сохранить");


		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE]{};
		HWND hParent = GetParent(hwnd);
		HWND hListBox = GetDlgItem(hParent, IDC_LIST1);
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_NAME);
		INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
		SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		SendMessage(hEdit, EM_SETSEL, 0, SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0));
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_NAME));
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_NAME);
			HWND hParent = GetParent(hwnd);
			HWND hListBox = GetDlgItem(hParent, IDC_LIST1);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			//SendMessage(hListBox, LB_SETITEMDATA, i, (LPARAM)sz_buffer);
			if (SendMessage(hListBox, LB_FINDSTRING, -1, (LPARAM)sz_buffer) == LB_ERR)
			{
				SendMessage(hListBox, LB_DELETESTRING, i, 0);
				SendMessage(hListBox, LB_INSERTSTRING, i, (LPARAM)sz_buffer);
				EndDialog(hwnd, 0);
			}
			else MessageBox(hwnd, "Такое значение уже есть в списке", "Info", MB_OK | MB_ICONEXCLAMATION);

		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}