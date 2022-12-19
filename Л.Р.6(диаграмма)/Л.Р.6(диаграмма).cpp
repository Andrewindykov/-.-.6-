// Л.Р.6(диаграмма).cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Л.Р.6(диаграмма).h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int a[10] = { 1,4,3,-4,5,-10,-6,7,-8,9 }; //Собственно массив исходный
int size = 10; // егойный размерр
int x = 100; int y = 200;   // Начало вывода 1го графика
int x1 = 350; int y1 = 200;  // Начало вывода 2го графика
int w = 20;  // ширина столбикофф
int max = a[0]; // переменные для наибольшего
int min = a[0]; // и наименьшего значений

int min_i = 0; int max_i = 0; // и запихаем сюдой

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.


    for (int i = 0; i < size; i++)
    {
        if (a[i] > max) {
            max = a[i];
            max_i = i;

        }
        if (a[i] < min) {
            min = a[i];
            min_i = i;
        }

    }








    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY6));

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
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY6);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      800 /*CW_USEDEFAULT */ , 200, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
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
            
            HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
            HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
            HBRUSH minBrush = CreateSolidBrush(RGB(100, 100, 128));
            HBRUSH maxBrush = CreateSolidBrush(RGB(50, 200, 30));
            HBRUSH mmBrush = CreateSolidBrush(RGB(250, 165, 0));
           // int min_i = 0; int max_i = 0; заберём отседова
            for (int i = 0; i < size; i++)
            {
                if (a[i] == max) {
                    SelectObject(hdc, maxBrush);
                }
                if (a[i] == min) {
                    SelectObject(hdc, minBrush);
                }
                if (a[i] < 0 && a[i] != min) {
                    SelectObject(hdc, blueBrush);
                }
                if (a[i] > 0 && a[i] != max) {
                    SelectObject(hdc, redBrush);
                }
                if (i > min_i and i < max_i) {
                    if (a[i] % 2 == 0) {
                        SelectObject(hdc, mmBrush);
                    }

                }
                Rectangle(hdc, x, y, x + w, y - a[i] * w); // отрисовка левых столбиков
                x += w;

            }


            for (int i = 0; i < size; i++)
            {
                if (a[i] == max) {
                    SelectObject(hdc, maxBrush);
                }
                if (a[i] == min) {
                    SelectObject(hdc, minBrush);
                }
                if (a[i] < 0 && a[i] != min) {
                    SelectObject(hdc, blueBrush);
                }
                if (a[i] > 0 && a[i] != max) {
                    SelectObject(hdc, redBrush);
                }
                if (i > min_i and i < max_i) {
                    if (a[i] % 2 != 0) {
                        SelectObject(hdc, redBrush);
                    }
                    if (a[i] % 2 == 0) {
                        a[i] = 0;
                        x1 += w * (-1);
                    }

                }
                Rectangle(hdc, x1, y1, x1 + w, y1 - a[i] * w); // отрисовка правых столбцов
                x1 += w;


            }

            /*MoveToEx(hdc, 100, 400, NULL);
            LineTo(hdc, 100, 40);*/

            MoveToEx(hdc, 100, 200, NULL); //левые оськи
            LineTo(hdc, 345, 200);
            LineTo(hdc, 340, 195);
            LineTo(hdc, 340, 205);
            LineTo(hdc, 345, 200);
            MoveToEx(hdc, 100, 200, NULL);
            LineTo(hdc, 100, 300);
            LineTo(hdc, 100, 60);
            LineTo(hdc, 105, 65);
            LineTo(hdc, 95, 65);
            LineTo(hdc, 100, 60);
            

            MoveToEx(hdc, 350, 200, NULL); //правые
            LineTo(hdc, 600, 200);
            LineTo(hdc, 595, 195);
            LineTo(hdc, 595, 205);
            LineTo(hdc, 600, 200);
            MoveToEx(hdc, 350, 200, NULL);
            LineTo(hdc, 350, 300);
            LineTo(hdc, 350, 60);
            LineTo(hdc, 355, 65);
            LineTo(hdc, 345, 65);
            LineTo(hdc, 350, 60);

            EndPaint(hWnd, &ps);
        }
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
