#include <Windows.h>
#include "resource.h"
#include <cstdio>

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
		break;
	case WM_COMMAND:

		if ((LOWORD(wParam) == IDC_CHECK2 && HIWORD(wParam) == BN_CLICKED) || (LOWORD(wParam) == IDC_CHECK5 && HIWORD(wParam) == BN_CLICKED))
		{
			HWND hCheckAttentive = GetDlgItem(hwnd, IDC_CHECK2);
			HWND hCheckInattentive = GetDlgItem(hwnd, IDC_CHECK5);
			if (SendMessage(hCheckAttentive, BM_GETCHECK, 0, 0) == BST_CHECKED && SendMessage(hCheckInattentive, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				MessageBox(hwnd, "Студент не может быть одновременно внимательным и невнимательным", "Info", MB_OK | MB_ICONEXCLAMATION);
				SendMessage(hCheckAttentive, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(hCheckInattentive, BM_SETCHECK, BST_UNCHECKED, 0);
			}
		}
		if ((LOWORD(wParam) == IDC_CHECK3 && HIWORD(wParam) == BN_CLICKED) || (LOWORD(wParam) == IDC_CHECK6 && HIWORD(wParam) == BN_CLICKED))
		{
			HWND hCheckQuitter = GetDlgItem(hwnd, IDC_CHECK3);
			HWND hCheckNotQuitter = GetDlgItem(hwnd, IDC_CHECK6);
			if (SendMessage(hCheckQuitter, BM_GETCHECK, 0, 0) == BST_CHECKED && SendMessage(hCheckNotQuitter, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				MessageBox(hwnd, "Студент не может быть одновременно прогульщиком и не прогуливать занятия", "Info", MB_OK | MB_ICONEXCLAMATION);
				SendMessage(hCheckQuitter, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(hCheckNotQuitter, BM_SETCHECK, BST_UNCHECKED, 0);
			}
		}

		switch (LOWORD(wParam))
		{
		case ID_GENERATE:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_NAME);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			
			if (sz_buffer[0] == '\0' || sz_buffer[0] == ' ')MessageBox(hwnd, "Введите имя студента", "Error", MB_OK | MB_ICONERROR);
			else 
			{
				CHAR sz_name[SIZE]{};
				SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_name);
				CHAR sz_answer[SIZE]{};

				CHAR sz_temp[SIZE]{};
				if(SendMessage(GetDlgItem(hwnd, IDC_CHECK1), BM_GETCHECK, 0, 0) == BST_CHECKED)
					for (int i = 0; i < sizeof(sz_temp) / sizeof(sz_temp[0]); i++)
					{
						
					}

				sprintf(sz_answer, "Студент %s - %s", sz_name);
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_answer);
			}
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