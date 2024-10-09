#include <Windows.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "Main Window"; //��� ������ ����

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) ����������� ������ ����
	//1.1) ������� � ������������������� ��������� WNDCLASSEX
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	//Sizes
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass); //cb - Count Bytes - ���. ����
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

	//1.2) ������� ������� RegisterClassEx()
	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2)�������� ����
	HWND hwnd = CreateWindowEx
	(
		NULL, //Window ExStyle
		g_sz_WINDOW_CLASS, //Window Class Name
		g_sz_WINDOW_CLASS, //Window Tytle
		WS_OVERLAPPEDWINDOW, //Window Style, ��� �������� ���� ������ WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT, CW_USEDEFAULT, //Coordinates
		CW_USEDEFAULT, CW_USEDEFAULT, //Window size
		NULL, //Parent - ������ NULL
		NULL, //hMenu: ��� �������� ���� ��� ResourceID �������� ����,
		//��� ��������� ���� (������ � ������ ��������) - ��� ID ������� ���������������� �������� (������, ���������� ���� � �.�.)
		//�� ����� ResourceID �� ������� �������� ������� ���� ��� ������ ������� GetDlgItem()
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow); //����� ����� ����������� ���� (���������� �� ���� �����, ������� � ����, ������� � ������ �����)
	UpdateWindow(hwnd); //������������� ����

	//3) ������ ����� ���������
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