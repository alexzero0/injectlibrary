// GUI_INJECT_x86.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "GUI_INJECT_x86.h"


#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;													// текущий экземпляр
const CHAR szTitle[MAX_LOADSTRING] = "GUI_INJECT_x86";            // Текст строки заголовка
const CHAR szWindowClass[MAX_LOADSTRING] = "ZD(ghl)_INJ";         // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void StartInject(char* FDll,char* FGame, HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_GUIINJECTX86, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUIINJECTX86));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}
//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUIINJECTX86));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEA(IDC_GUIINJECTX86);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExA(&wcex);
}
//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowA(szWindowClass, szTitle, WS_SYSMENU|WS_MINIMIZEBOX,//WS_OVERLAPPEDWINDOW
       CW_USEDEFAULT, 
	   CW_USEDEFAULT,
	   340, 
	   130, 
	   nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
   SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdt1, hEdt2; // дескрипторы полей редактирования
	static HWND hBINJ; // дескриптор кнопки
	static HWND hStat1, hStat2; // дескриптор статического текста
	TCHAR FDll[MAX_LOADSTRING];
	TCHAR FGame[MAX_LOADSTRING];
	//HINSTANCE hInst;


    switch (message)
    {
    case WM_COMMAND:    
		if (lParam == (LPARAM)hBINJ)
		{
			GetWindowText(hEdt1, FDll, MAX_LOADSTRING);
			GetWindowText(hEdt2, FGame, MAX_LOADSTRING);
			StartInject(FDll, FGame, hWnd);
			//MessageBox(hWnd, str, "Test", MB_OK);
		}
		{
			int wmId = LOWORD(wParam);
			// Разобрать выбор в меню:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CREATE:
		//hInst = ((LPCREATESTRUCT)lParam)->hInstance;//340//130

		hStat1 = CreateWindowExW(0,L"static", L"Какой файл инжектим:", WS_CHILD | WS_VISIBLE,
			3, 0, 155, 20, hWnd, 0, hInst, NULL);
		ShowWindow(hStat1, SW_SHOWNORMAL);

		hEdt1 = CreateWindowExW(0, L"edit", L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 3, 20, 155, 20,
			hWnd, 0, hInst, NULL);
		ShowWindow(hEdt1, SW_SHOWNORMAL);

		hStat2 = CreateWindowExW(0, L"static", L"Куда файл инжектим:", WS_CHILD | WS_VISIBLE,
			165, 0, 155, 20, hWnd, 0, hInst, NULL);
		ShowWindow(hStat2, SW_SHOWNORMAL);

		hEdt2 = CreateWindowExW(0, L"edit", L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 165, 20, 155, 20,
			hWnd, 0, hInst, NULL);
		ShowWindow(hEdt2, SW_SHOWNORMAL);

		hBINJ = CreateWindowExW(0,L"button", L"INJECT",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			3, 43, 318, 25, hWnd, 0, hInst, NULL);
		ShowWindow(hBINJ, SW_SHOWNORMAL);

		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void StartInject(char* FDll, char* FGame, HWND hWnd)
{
	DWORD pID = NULL;
	char path[4096];
	pID = GetProcessByName(FGame);
	for (int i = 0; i<5; i++, Sleep(1000))
	{
		if (pID == 0)
			pID = GetProcessByName(FGame);
		if (pID != 0) break;
	}
	if (pID == 0)
	{
		MessageBox(hWnd, "Eror PID", "Inject", MB_OK);
		return;
	}
	for (int j = 0; j < 5; j++, Sleep(1000))
	{
		GetFullPathName(FDll, sizeof(path), path, NULL);
		if (FileExist(path)) { break; }
	}

	if (Inject(pID, path))
	{
		MessageBox(hWnd, "Dll in Programm", "Inject", MB_OK);
		return;
	}
	else
	{
		MessageBox(hWnd, "Eror Inject", "Inject", MB_OK);
		return;
	}
}