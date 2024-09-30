#include <Windows.h>
#include <Windowsx.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//hInstance - экземпляр запущенного *.exe-файла нашей программы
	//hPrevInst - НЕ используется
	//LPSTR - Long Pointer To String
	//lpCmdLine - CommandLine (командная строка с параметрами запуска приложения)
	//nCmdShow  - режим отображения окна (развернуто на весь экран, cвернуто на панель задач и т.д.)
	//Префиксы: n..., lp... это Венгерская нотация
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
	//wchar_t = 2 б, хранит символы в кодировке unicode
	//properties - anvanced - character set - use miltibyte character set
	//properties - linker - system - subsystem - windows
	// 
	//DialogBox()

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0); 

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//hwnd - Handler to Window. Обработчик или дескриптор окна - это число, при помощи которого можно обратиться к окну
	//uMsg - Message. Сообщение, которое отправляется окну
	//wParam, lParam - параметры сообщения, у каждого сообщения свой набор параметров.
	//HWND hLoginPlaceholder = GetDlgItem(hwnd, IDC_LOGIN_PLACEHOLDER);
	//BringWindowToTop(hLoginPlaceholder);
	switch (uMsg)
	{
	case WM_INITDIALOG: //это сообщение отправляется один раз при инициализации окна
		break;
	case WM_COMMAND: //обрабатывает нажатие кнопок и другие действия пользователя
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN :
			{
				HWND hLoginPlaceholder = GetDlgItem(hwnd, IDC_LOGIN_PLACEHOLDER);
				
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				//SetDlgItemTextW(hEditLogin, IDC_EDIT_LOGIN, (LPCWSTR)"Введите имя пользователя"); //не нашел, как изменить видимость текстового окна

				//bool temp = SetDlgItemInt(hLoginPlaceholder, IDC_LOGIN_PLACEHOLDER, 1, false); //не нашел, как изменить видимость текстового окна
				//LPSTR temp_s = WM_GETTEXT;
				//LPSTR temp_s1 = 0; //NULL
				//GetWindowTextA(hEditLogin, temp_s1, 256);
				//LPSTR temp_s2 = 0; //NULL
				//GetWindowTextA(hLoginPlaceholder, temp_s2, 256);
				//WS_VISIBLE = false;
				//bool temp2 = IsWindowVisible(hLoginPlaceholder);

				ShowWindow(hLoginPlaceholder, SW_HIDE);
				//if (IsWindowVisible(hLoginPlaceholder) == 0)

				//BringWindowToTop(hLoginPlaceholder); //не работает, хотя текст - это же окно
				//SetWindowPos(hLoginPlaceholder, HWND_TOP, GET_X_LPARAM()GetWindowRect);

				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				//if (WM_GETTEXT == 0)
				if (sz_buffer[0] == NULL)
				{
					//SetDlgItemTextA(hLoginPlaceholder, IDC_LOGIN_PLACEHOLDER, "Введите имя пользователя");

					ShowWindow(hLoginPlaceholder, SW_SHOW); //непонятно, почему не работает  свойство transparent 
					BringWindowToTop(hLoginPlaceholder); //окно снова становится видимым, но уходит в z-порядке ниже окна Edit. Эта функция не раюотает почему-то
				}
			}
			break;
		case IDC_BUTTON_COPY: 
			{
				//1) создаём буфер
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {}; //sz - String Zero (NULL Terminated Line - C-string)

				//2) Получаем обработчики текстовых полей (обратиться к окну можно только через обработчик)
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

				//3) Считываем содержимое поля "Login" в буфер
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

				//4) Записываем полученный текст в текстовое поле Password
				SendMessage(hEditPassword, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
			}
			break;

		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: //отправляется при нажатии кнопки "Закрыть Х"
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;

}