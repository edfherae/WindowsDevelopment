#include <Windows.h>
#include <Windowsx.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//hInstance - ��������� ����������� *.exe-����� ����� ���������
	//hPrevInst - �� ������������
	//LPSTR - Long Pointer To String
	//lpCmdLine - CommandLine (��������� ������ � ����������� ������� ����������)
	//nCmdShow  - ����� ����������� ���� (���������� �� ���� �����, c������� �� ������ ����� � �.�.)
	//��������: n..., lp... ��� ���������� �������
	//			n - Number
	//			lp - Long Pointer
	//			h - HINSTANCE

	/*MessageBox
	(
		NULL, 
		"Hello C++\nagain", "Window title", 
		MB_CANCELTRYCONTINUE | MB_HELP | MB_DEFBUTTON3 | 
		MB_ICONINFORMATION |
		MB_SYSTEMMODAL
	); */
	//wchar_t = 2 �, ������ ������� � ��������� unicode
	//properties - anvanced - character set - use miltibyte character set
	//properties - linker - system - subsystem - windows
	// 
	//DialogBox()

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0); 

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//hwnd - Handler to Window. ���������� ��� ���������� ���� - ��� �����, ��� ������ �������� ����� ���������� � ����
	//uMsg - Message. ���������, ������� ������������ ����
	//wParam, lParam - ��������� ���������, � ������� ��������� ���� ����� ����������.
	//HWND hLoginPlaceholder = GetDlgItem(hwnd, IDC_LOGIN_PLACEHOLDER);
	//BringWindowToTop(hLoginPlaceholder);
	switch (uMsg)
	{
	case WM_INITDIALOG: //��� ��������� ������������ ���� ��� ��� ������������� ����
		break;
	case WM_COMMAND: //������������ ������� ������ � ������ �������� ������������
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN :
			{
				HWND hLoginPlaceholder = GetDlgItem(hwnd, IDC_LOGIN_PLACEHOLDER);
				
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				//SetDlgItemTextW(hEditLogin, IDC_EDIT_LOGIN, (LPCWSTR)"������� ��� ������������"); //�� �����, ��� �������� ��������� ���������� ����

				//bool temp = SetDlgItemInt(hLoginPlaceholder, IDC_LOGIN_PLACEHOLDER, 1, false); //�� �����, ��� �������� ��������� ���������� ����
				//LPSTR temp_s = WM_GETTEXT;
				//LPSTR temp_s1 = 0; //NULL
				//GetWindowTextA(hEditLogin, temp_s1, 256);
				//LPSTR temp_s2 = 0; //NULL
				//GetWindowTextA(hLoginPlaceholder, temp_s2, 256);
				//WS_VISIBLE = false;
				//bool temp2 = IsWindowVisible(hLoginPlaceholder);

				ShowWindow(hLoginPlaceholder, SW_HIDE);
				//if (IsWindowVisible(hLoginPlaceholder) == 0)

				//BringWindowToTop(hLoginPlaceholder); //�� ��������, ���� ����� - ��� �� ����
				//SetWindowPos(hLoginPlaceholder, HWND_TOP, GET_X_LPARAM()GetWindowRect);

				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				//if (WM_GETTEXT == 0)
				if (sz_buffer[0] == NULL)
				{
					//SetDlgItemTextA(hLoginPlaceholder, IDC_LOGIN_PLACEHOLDER, "������� ��� ������������");

					ShowWindow(hLoginPlaceholder, SW_SHOW); //���������, ������ �� ��������  �������� transparent 
					BringWindowToTop(hLoginPlaceholder); //���� ����� ���������� �������, �� ������ � z-������� ���� ���� Edit. ��� ������� �� �������� ������-��
				}
			}
			break;
		case IDC_BUTTON_COPY: 
			{
				//1) ������ �����
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {}; //sz - String Zero (NULL Terminated Line - C-string)

				//2) �������� ����������� ��������� ����� (���������� � ���� ����� ������ ����� ����������)
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

				//3) ��������� ���������� ���� "Login" � �����
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

				//4) ���������� ���������� ����� � ��������� ���� Password
				SendMessage(hEditPassword, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
			}
			break;

		case IDOK: MessageBox(hwnd, "���� ������ ������ ��", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: //������������ ��� ������� ������ "������� �"
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;

}