#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdio>

#define IDC_STATIC 1000		//1) создаем ResourceID для дочернего элемента
#define IDC_EDIT 1001
#define IDC_BUTTON 1002

CONST CHAR g_sz_WINDOW_CLASS[] = "Main Window"; //Имя класса окна

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна
	//1.1) создать и проинициализировать структуру WNDCLASSEX
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	//Sizes
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass); //cb - Count Bytes - кол. байт
	wClass.cbClsExtra = 0; //Class Extra Bytes
	wClass.cbWndExtra = 0; //Window Extra Bytes

	//Appearance
	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\tree.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\dog.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //Small icon
	//wClass.hCursor = LoadCursor(NULL, IDC_ARROW); //можно через LoadImage также загрузить курсор, даже анимированный
	//wClass.hCursor = (HCURSOR)LoadImage(hInstance, "CUR\\BlueCursor\\roundynormal.cur", IMAGE_CURSOR, 30, 30, LR_LOADFROMFILE);
	wClass.hCursor = (HCURSOR)LoadImage(hInstance, "CUR\\animated-minecraft\\Minecraft's Diamond Sword.ani", IMAGE_CURSOR, 30, 30, LR_LOADFROMFILE);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;

	//1.2) вызвать функцию RegisterClassEx()
	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2)Создание окна
	HWND hwnd = CreateWindowEx
	(
		NULL, //Window ExStyle
		g_sz_WINDOW_CLASS, //Window Class Name
		g_sz_WINDOW_CLASS, //Window Tytle
		WS_OVERLAPPED | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, //Window Style, для главного окна всегда WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT, CW_USEDEFAULT, //Coordinates
		CW_USEDEFAULT, CW_USEDEFAULT, //Window size
		NULL, //Parent - всегда NULL
		NULL, //hMenu: для главного окна это ResourceID главного меню,
		//для дочернего окна (кнопки и другие элементы) - это ID ресурса соответствующего элемента (кнопки, текстового поля и т.д.)
		//по этому ResourceID мы находим дочерний элемент окна при помощи функции GetDlgItem()
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow); //Задаёт режим отображения окна (развернуто на весь экран, свёрнуто в окно, свёрнуто в панель задач)
	UpdateWindow(hwnd); //Прорисовывает окно

	//3) Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message;

	return 0;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		CreateWindowEx
		(
			NULL,
			"Static",
			"Это static_text",
			WS_CHILD | WS_VISIBLE,	//для всех дочерних окон стиль обязательно будет WS_CHILD (этот как минимум) и WS_VISIBLE
			100, 10,
			200, 20,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx(
			NULL, "Edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 30,
			200, 20,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx(
			NULL, "Button", "OK",
			WS_CHILD | WS_VISIBLE,
			200, 55,
			100, 32,
			hwnd,
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL
		);
		break;
	case WM_MOVING:
	{
		CHAR sz_buffer[32]{};
		RECT* rect = (RECT*)lParam;
		sprintf(sz_buffer, "x: %d | y: %d", rect->left, rect->top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		SendMessage(GetDlgItem(hwnd, IDC_STATIC), WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;
	case WM_SIZING:
	{
		CHAR sz_buffer[32]{};
		RECT* rect = (RECT*)lParam;
		sprintf(sz_buffer, "Width: %d | Heigth: %d", rect->right - rect->left, rect->bottom - rect->top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		SendMessage(GetDlgItem(hwnd, IDC_STATIC), WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE]{};
				SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				SendMessage(GetDlgItem(hwnd, IDC_STATIC), WM_SETTEXT, 0, (LPARAM)sz_buffer);
				SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_CLOSE:DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}