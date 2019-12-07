// Sapper.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Sapper.h"
#include "business/Game/GameConfigsEnum.h"
#include "business/Game/Game.h"
#include "view/BoardDrawer/BoardDrawer.h"
#include "view/ButtonDrawer_.h"
#include "Controllers/MouseButton/MouseButton.h"
#include "Controllers/MouseController.h"
#include "business/States/GameStatesEnum.h"

#define MAX_LOADSTRING 100
#define ID_EASY_BUTTON 3000 
#define ID_MEDIUM_BUTTON 3001
#define ID_HARD_BUTTON 3002

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
HWND hEasyBtn;
HWND hMediumBtn;
HWND hHardBtn;
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

Game* game;
ButtonDrawer_* buttonDrawer;
MouseController* mouseController;
BoardDrawer* boardDrawer;
GameConfigs* gameConfigs;
GameStatesEnum gameState;
GameDifficulty gameDifficulty;

int answer = 0;
bool playAgan = true;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SAPPER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAPPER));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAPPER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SAPPER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
	case WM_CREATE:
	{
		buttonDrawer = new ButtonDrawer_();
		mouseController = new MouseController();
		boardDrawer = new BoardDrawer();
		gameState = ChoosingDifficulty;

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
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

		RECT clientRect;
		HBRUSH hBrush = CreateSolidBrush(RGB(240, 240, 240));
		HGDIOBJ oldHBrush = SelectObject(hdc, hBrush);

		GetClientRect(hWnd, &clientRect);
		FillRect(hdc, &clientRect, hBrush);

		SelectObject(hdc, oldHBrush);
	
		switch (gameState)
		{
		case ChoosingDifficulty:
			buttonDrawer->Draw(hWnd, hdc);
			break;

		case Playing:
			boardDrawer->Draw(game->GetBoard(), hWnd, hdc, false);
			break;

		case Lost:
			boardDrawer->Draw(game->GetBoard(), hWnd, hdc, true);
			if (playAgan)
			{
				answer = MessageBox(hWnd, L"Хотите сыграть еще раз?", L"Вы проиграли", MB_YESNO || MB_ICONQUESTION);
				if (answer == IDOK)
				{
					delete game;
					gameState = ChoosingDifficulty;

					InvalidateRect(hWnd, NULL, true);
					UpdateWindow(hWnd);
				}
				else
				{
					playAgan = false;
				}
			}
			break;

		case Won:
			boardDrawer->Draw(game->GetBoard(), hWnd, hdc, true);
			if (playAgan)
			{
				answer = MessageBox(hWnd, L"Хотите сыграть еще раз?", L"Вы выиграли!", MB_YESNO || MB_ICONQUESTION);
				if (answer == IDOK)
				{
					delete game;
					gameState = ChoosingDifficulty;

					InvalidateRect(hWnd, NULL, true);
					UpdateWindow(hWnd);
				}
				else
				{
					playAgan = false;
				}
			}
			break;
		}

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_RBUTTONUP:

		POINT p;

		p.y = HIWORD(lParam);
		p.x = LOWORD(lParam);

		switch (gameState)
		{
		case Playing:
			mouseController->ProcessClick(hWnd, p, game, RButton, &gameState);
			break;
		}
		break;

	case WM_LBUTTONUP:
	{
		POINT p;
		p.y = HIWORD(lParam);
		p.x = LOWORD(lParam);

		switch (gameState)
		{
		case ChoosingDifficulty:

			gameDifficulty = mouseController->ProcessChossingDifficulty(hWnd, p);

			switch (gameDifficulty)
			{
			case easy:
				gameConfigs = new GameConfigs(easy);
				game = new Game(gameConfigs);

				gameState = Playing;

				delete gameConfigs;

				InvalidateRect(hWnd, NULL, true);
				UpdateWindow(hWnd);

				break;

			case medium:
				gameConfigs = new GameConfigs(medium);
				game = new Game(gameConfigs);

				gameState = Playing;

				delete gameConfigs;

				InvalidateRect(hWnd, NULL, true);
				UpdateWindow(hWnd);

				break;

			case hard:
				gameConfigs = new GameConfigs(hard);
				game = new Game(gameConfigs);

				gameState = Playing;

				delete gameConfigs;

				InvalidateRect(hWnd, NULL, true);
				UpdateWindow(hWnd);

				break;
			}
			break;

		case Playing:
			mouseController->ProcessClick(hWnd, p, game, LButton, &gameState);
			break;

		case Lost:
			break;

		case Won:
			break;
		}
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
