#include <Windows.h>

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
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //Small icon
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
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
		WS_OVERLAPPEDWINDOW, //Window Style, для главного окла всегда WS_OVERLAPPEDWINDOW
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
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_CLOSE:DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}