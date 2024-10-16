#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "resource.h"
#include <cstdio>
#include <float.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc";

// ћј—Ў“јЅ»–”≈ћќ—“№ ƒќ –”“»“№, button size прив€зать к изменению размера окна

CONST INT g_BUTTON_SIZE = 50;
CONST INT g_INTERVAL = 2;
CONST INT g_BUTTON_DOUBLE_SIZE = g_BUTTON_SIZE * 2 + g_INTERVAL;
CONST INT g_BUTTON_TRIPLE_SIZE = g_BUTTON_SIZE * 3 + g_INTERVAL * 2;
CONST INT g_START_X = 10;
CONST INT g_START_Y = 10;
CONST INT g_DISPLAY_WIDTH = g_BUTTON_SIZE * 5 + g_INTERVAL * 4;
CONST INT g_DISPLAY_HEIGHT = 25;
CONST INT g_BUTTON_START_X = g_START_X;
CONST INT g_BUTTON_START_Y = g_START_Y + g_DISPLAY_HEIGHT + g_INTERVAL;

CONST INT g_OPERATIONS_START_X = g_START_X + (g_BUTTON_SIZE + g_INTERVAL) * 3;
CONST INT g_OPERATIONS_START_Y = g_BUTTON_START_Y;
CONST CHAR g_OPERATIONS[] = "+-*/";

CONST INT g_CONTROL_BUTTONS_START_X = g_START_X + (g_BUTTON_SIZE + g_INTERVAL) * 4;
CONST INT g_CONTROL_BUTTONS_START_Y = g_BUTTON_START_Y;

BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) –егистраци€ класса окна
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	wClass.hIcon = (HICON)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\calc.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) —оздание окна
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW /*- WS_THICKFRAME*/ - WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_DISPLAY_WIDTH + g_BUTTON_START_X * 2 + 16, 
		g_DISPLAY_HEIGHT + (g_BUTTON_SIZE + g_INTERVAL) * 4 + g_START_Y * 2 + 16 + 23,
		NULL,
		NULL,
		hInstance,
		0
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) «апуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.message;
}
BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//static HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
	static DOUBLE a = DBL_MIN, b;	//операнды
	static INT operation;			//операци€
	static BOOL input;				//устанавливаетс€ при вводе числа
	static BOOL operation_input;	//устанавливаетс€ при вводе операции
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEditDisplay = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_RIGHT,
			g_START_X, g_START_Y,
			g_DISPLAY_WIDTH, g_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			0
		);

		CHAR sz_digit[2]{};
		int count = 1;
		for (int i = 6; i >= 0; i -= 3) //1 - 9 buttons
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = i + j + '1';
				//sprintf(sz_digit, "%d", count);
				CreateWindowEx
				(
					NULL, "Button", (LPSTR)sz_digit,
					WS_CHILD | WS_VISIBLE,
					g_BUTTON_START_X + (g_BUTTON_SIZE + g_INTERVAL) * j, 
					g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * (i / 3),
					g_BUTTON_SIZE, g_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1 + i + j),
					GetModuleHandle(NULL),
					NULL
				);
				count++;
			}
		}

		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE,
			g_BUTTON_START_X, g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 3,
			g_BUTTON_DOUBLE_SIZE, g_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			0
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE,
			g_BUTTON_START_X + g_BUTTON_DOUBLE_SIZE + g_INTERVAL, 
			g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 3,
			g_BUTTON_SIZE, g_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			0
		);

		CHAR sz_operation[2]{};
		for (int i = 0; i < 4; i++) //Operations
		{
			sz_operation[0] = g_OPERATIONS[i];
			DWORD resource = IDC_BUTTON_PLUS + i;
			CreateWindowEx
			(
				NULL, "Button", sz_operation,
				WS_CHILD | WS_VISIBLE,
				g_OPERATIONS_START_X, g_OPERATIONS_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * i,
				g_BUTTON_SIZE, g_BUTTON_SIZE,
				hwnd,
				HMENU(IDC_BUTTON_PLUS + i),
				GetModuleHandle(NULL),
				0
			);
		}

		//Constrols
		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE,
			g_CONTROL_BUTTONS_START_X, g_CONTROL_BUTTONS_START_Y,
			g_BUTTON_SIZE, g_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			0
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE,
			g_CONTROL_BUTTONS_START_X, g_CONTROL_BUTTONS_START_Y + g_BUTTON_SIZE + g_INTERVAL,
			g_BUTTON_SIZE, g_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL),
			0
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE,
			g_CONTROL_BUTTONS_START_X, g_CONTROL_BUTTONS_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 2,
			g_BUTTON_SIZE, g_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			0
		);
	}
		break;
	/*case WM_SIZING:
	{
		RECT* rect = (RECT*)lParam;
		if (wParam == WMSZ_RIGHT)
		{
			g_BUTTON_SIZE + 10;
		}
		if ((rect->right - rect->left) > g_DISPLAY_WIDTH)
		{
			g_BUTTON_SIZE += 10;
		}
	}*/
	break;
	case WM_COMMAND:
	{

		// ћј—Ў“јЅ»–”≈ћќ—“№ ƒќ –”“»“№, button size прив€зать к изменению размера окна
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		CONST INT SIZE = 256;
		CHAR sz_display[SIZE]{};
		CHAR sz_digit[2]{};
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam <= IDC_BUTTON_9))
		{
			if (input == FALSE && operation_input == TRUE)SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"");
			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + 48;
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (sz_display[0] == '0' && sz_display[1] != '.')sz_display[0] = 0;
			strcat(sz_display, sz_digit);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (strchr(sz_display, '.'))break;
			strcat(sz_display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}

		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (strlen(sz_display) == 1)sz_display[0] = '0';
			else sz_display[strlen(sz_display) - 1] = 0;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}

		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			a = b = DBL_MIN;
			operation = 0;
			input = operation_input = FALSE;
			sz_display[0] = '0';
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}

		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (a == DBL_MIN)a = strtod(sz_display, NULL);
			else b = strtod(sz_display, NULL);
			operation = LOWORD(wParam);
			input = FALSE;
			operation_input = TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (operation_input)b = strtod(sz_display, NULL);
			switch (operation)
			{
			case IDC_BUTTON_PLUS:	a += b;		break;
			case IDC_BUTTON_MINUS:	a -= b;		break;
			case IDC_BUTTON_ASTER:	a *= b;		break;
			case IDC_BUTTON_SLASH:	a /= b;		break;
			}
			operation_input = FALSE;
			sprintf(sz_display, "%g", a);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}