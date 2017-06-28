#include "stdafx.h"
#include "draw.h"

#include<vector>
#include<queue>

#define MAX_LOADSTRING 100
#define TMR_1 1

using namespace std;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name



												///////////////////////////////////////////////
INT weight = 0;
INT MAX_WEIGHT = 600;

INT value = 0;

INT position = 420;  // elevator's position
					 //////////////////////////////////////////////////////




					 // Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void add_human(int a, int b);


///////////////////////////////////////////////////
HWND P1_2, P1_3, P1_4, P1_5;
HWND P2_1, P2_3, P2_4, P2_5;
HWND P3_1, P3_2, P3_4, P3_5;
HWND P4_1, P4_2, P4_3, P4_5;
HWND P5_1, P5_2, P5_3, P5_4;

RECT drawArea1 = { 105, 15, 395, 505 };

RECT drawAreaF1 = { 404, 405, 799, 495 };
RECT drawAreaF2 = { 404, 305, 799, 395 };
RECT drawAreaF3 = { 404, 205, 799, 295 };
RECT drawAreaF4 = { 404, 105, 799, 195 };
RECT drawAreaF5 = { 404, 0, 799, 95 };


struct waiting
{
	int start;
	int finish;
	int direction;
};


queue <waiting> elevator;

vector <waiting> F1;        // queues for the floors
vector <waiting> F2;
vector <waiting> F3;
vector <waiting> F4;
vector <waiting> F5;



void launch_lift(int a, int b) //a-skad, b-dokad
{
	if (F1.empty() && F2.empty() && F3.empty() && F4.empty() && F5.empty())
	{
		waiting p;

		p.start = a;
		p.finish = b;
		if (a - b < 0)
			p.direction = 1;    // up
		else
			p.direction = -1;    // down

		elevator.push(p);
	}
	add_human(a, b);
}



void add_human(int a, int b)
{
	waiting human;

	human.start = a;
	human.finish = b;
	if (a - b < 0)
		human.direction = 1;    // up
	else
		human.direction = -1;    // down

	if (a == 1)
		F1.push_back(human);
	if (a == 2)
		F2.push_back(human);
	if (a == 3)
		F3.push_back(human);
	if (a == 4)
		F4.push_back(human);
	if (a == 5)
		F5.push_back(human);

}

void draw_human(HDC hdc, int a, int b, int c) // b- rozmiar kolejki (ile ludzi czeka na pietrze) a- ktore pietro
{
	Graphics graphics(hdc);
	Pen red(Color(255, 87, 30, 255)); // zmienic kolor


	for (int i = 0; i < b; i++)
	{
		graphics.DrawRectangle(&red, c + i * 35, a, 30, 60);
	}

}
/*
void to_lift(int a, int b, vector <waiting> c) // a-which floor, b-direction
{
for (int i = 0; i < c.size(); i++)
{
if ((c[i].direction == b) && position == a)     //&& F2[i].finish <= elevator.front().start
{
elevator.push(c[i]);
c.erase(c.begin() + i);
}
}
}*/


void MyOnPaint(HDC hdc)   // Paints the elevator with floors
{

	Graphics graphics(hdc);
	Pen violet(Color(255, 87, 30, 255));


	graphics.DrawRectangle(&violet, 100, 10, 300, 500);

	graphics.DrawLine(&violet, 400, 100, 800, 100);      // draws the floors
	graphics.DrawLine(&violet, 400, 200, 800, 200);
	graphics.DrawLine(&violet, 400, 300, 800, 300);
	graphics.DrawLine(&violet, 400, 400, 800, 400);
	graphics.DrawLine(&violet, 400, 500, 800, 500);


	draw_human(hdc, 420, F1.size(), 405);
	draw_human(hdc, 320, F2.size(), 405);
	draw_human(hdc, 220, F3.size(), 405);
	draw_human(hdc, 120, F4.size(), 405);
	draw_human(hdc, 20, F5.size(), 405);


	if (!elevator.empty())
	{
		Pen szary(Color(200, 53, 67, 0));
		int x = position;
		int y = 420 - (elevator.front().start - 1) * 100;

		if (x > y)
		{
			position--;
			x = position;


			if (!F1.empty() && (F2.empty() || F3.empty() || F4.empty() || F5.empty() || F1.size() > 1))
			{
				for (int i = 0; i < F1.size(); i++)
				{
					if ((F1[i].direction == 1) && position == 420 && (value + 1) * 70 < MAX_WEIGHT)
					{
						elevator.push(F1[i]);
						F1.erase(F1.begin() + i);
						value++;
					}
				}
			}
			if (!F2.empty() && (F1.empty() || F3.empty() || F4.empty() || F5.empty() || F2.size() > 1))
			{
				for (int i = 0; i < F2.size(); i++)
				{
					if ((F2[i].direction == 1) && position == 320 && (value + 1) * 70 < MAX_WEIGHT)     /* && F2[i].finish <= elevator.front().start*/
					{
						elevator.push(F2[i]);
						F2.erase(F2.begin() + i);
						value++;
					}
				}
			}
			if (!F3.empty() && (F1.empty() || F2.empty() || F4.empty() || F5.empty() || F3.size() > 1))
			{
				for (int i = 0; i < F3.size(); i++)
				{
					if ((F3[i].direction == 1) && position == 220 && (value + 1) * 70 < MAX_WEIGHT)
					{
						elevator.push(F3[i]);
						F3.erase(F3.begin() + i);
						value++;
					}
				}
				//to_lift(220, 1, F3);
			}
			if (!F4.empty() && (F1.empty() || F2.empty() || F3.empty() || F5.empty() /*|| F4.size() > 1*/))
			{
				for (int i = 0; i < F4.size(); i++)
				{
					if ((F4[i].direction == 1) && position == 120 && (value+1)*70 < MAX_WEIGHT)
					{
						elevator.push(F4[i]);
						F4.erase(F4.begin() + i);
						value++;
					}
				}
			}

		} if (x < y)
		{
			position++;
			x = position;


			if (!F2.empty() && (F1.empty() || F3.empty() || F4.empty() || F5.empty() || F2.size() > 1))
			{
				for (int i = 0; i < F2.size(); i++)
				{
					if ((F2[i].direction == -1) && position == 320 && (value + 1) * 70 < MAX_WEIGHT)
					{
						elevator.push(F2[i]);
						F2.erase(F2.begin() + i);
						value++;
					}
				}
			}
			if (!F3.empty() && (F1.empty() || F2.empty() || F4.empty() || F5.empty() || F3.size() > 1))
			{
				for (int i = 0; i < F3.size(); i++)
				{
					if ((F3[i].direction == -1) && position == 220 && (value + 1) * 70 < MAX_WEIGHT)
					{
						elevator.push(F3[i]);
						F3.erase(F3.begin() + i);
						value++;
					}
				}
			}
			if (!F4.empty() && (F1.empty() || F2.empty() || F3.empty() || F5.empty() || F4.size() > 1))
			{
				for (int i = 0; i < F4.size(); i++)
				{
					if ((F4[i].direction == -1) && position == 120 && (value + 1) * 70 < MAX_WEIGHT)
					{
						elevator.push(F4[i]);
						F4.erase(F4.begin() + i);
						value++;
					}
				}
			}
			if (!F5.empty() && (F1.empty() || F2.empty() || F3.empty() || F4.empty() || F5.size() > 1))
			{
				for (int i = 0; i < F4.size(); i++)
				{
					if ((F5[i].direction == -1) && position == 120 && (value + 1) * 70 < MAX_WEIGHT)
					{
						elevator.push(F5[i]);
						F5.erase(F5.begin() + i);
						value++;
					}
				}
			}
		}
		else; /////////////dodac wstrzymanie na 2 sekundy
		graphics.DrawRectangle(&szary, 110, x, 280, 80);
		draw_human(hdc, x + 10, value, 120);
	}
}




int OnCreate(HWND window)
{
	SetTimer(window, TMR_1, 30, 0);
	return 0;
}



int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;


	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);



	P5_1 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("1"), WS_CHILD | WS_VISIBLE, 820, 50, 20, 30, hWnd, NULL, hInstance, NULL);
	P5_2 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("2"), WS_CHILD | WS_VISIBLE, 850, 50, 20, 30, hWnd, NULL, hInstance, NULL);
	P5_3 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("3"), WS_CHILD | WS_VISIBLE, 880, 50, 20, 30, hWnd, NULL, hInstance, NULL);
	P5_4 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("4"), WS_CHILD | WS_VISIBLE, 910, 50, 20, 30, hWnd, NULL, hInstance, NULL);

	P4_1 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("1"), WS_CHILD | WS_VISIBLE, 820, 150, 20, 30, hWnd, NULL, hInstance, NULL);
	P4_2 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("2"), WS_CHILD | WS_VISIBLE, 850, 150, 20, 30, hWnd, NULL, hInstance, NULL);
	P4_3 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("3"), WS_CHILD | WS_VISIBLE, 880, 150, 20, 30, hWnd, NULL, hInstance, NULL);
	P4_5 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("5"), WS_CHILD | WS_VISIBLE, 910, 150, 20, 30, hWnd, NULL, hInstance, NULL);

	P3_1 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("1"), WS_CHILD | WS_VISIBLE, 820, 250, 20, 30, hWnd, NULL, hInstance, NULL);
	P3_2 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("2"), WS_CHILD | WS_VISIBLE, 850, 250, 20, 30, hWnd, NULL, hInstance, NULL);
	P3_4 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("4"), WS_CHILD | WS_VISIBLE, 880, 250, 20, 30, hWnd, NULL, hInstance, NULL);
	P3_5 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("5"), WS_CHILD | WS_VISIBLE, 910, 250, 20, 30, hWnd, NULL, hInstance, NULL);

	P2_1 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("1"), WS_CHILD | WS_VISIBLE, 820, 350, 20, 30, hWnd, NULL, hInstance, NULL);
	P2_3 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("3"), WS_CHILD | WS_VISIBLE, 850, 350, 20, 30, hWnd, NULL, hInstance, NULL);
	P2_4 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("4"), WS_CHILD | WS_VISIBLE, 880, 350, 20, 30, hWnd, NULL, hInstance, NULL);
	P2_5 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("5"), WS_CHILD | WS_VISIBLE, 910, 350, 20, 30, hWnd, NULL, hInstance, NULL);

	P1_2 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("2"), WS_CHILD | WS_VISIBLE, 820, 450, 20, 30, hWnd, NULL, hInstance, NULL);
	P1_3 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("3"), WS_CHILD | WS_VISIBLE, 850, 450, 20, 30, hWnd, NULL, hInstance, NULL);
	P1_4 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("4"), WS_CHILD | WS_VISIBLE, 880, 450, 20, 30, hWnd, NULL, hInstance, NULL);
	P1_5 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("5"), WS_CHILD | WS_VISIBLE, 910, 450, 20, 30, hWnd, NULL, hInstance, NULL);





	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:



		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if ((HWND)lParam == P2_1)   // DOKOÑCZY DLA PIETER 4-5 !!!
		{
			launch_lift(2, 1);
		}
		if ((HWND)lParam == P3_1)
		{
			launch_lift(3, 1);
		}
		if ((HWND)lParam == P4_1)
		{
			launch_lift(4, 1);
		}
		if ((HWND)lParam == P5_1)
		{
			launch_lift(5, 1);
		}
		if ((HWND)lParam == P1_2)
		{
			launch_lift(1, 2);
		}
		if ((HWND)lParam == P3_2)
		{
			launch_lift(3, 2);
		}
		if ((HWND)lParam == P4_2)
		{
			launch_lift(4, 2);
		}
		if ((HWND)lParam == P5_2)
		{
			launch_lift(5, 2);
		}
		if ((HWND)lParam == P1_3)
		{
			launch_lift(1, 3);
		}
		if ((HWND)lParam == P2_3)
		{
			launch_lift(2, 3);
		}
		if ((HWND)lParam == P4_3)
		{
			launch_lift(4, 3);
		}
		if ((HWND)lParam == P5_3)
		{
			launch_lift(5, 3);
		}
		if ((HWND)lParam == P1_4)
		{
			launch_lift(1, 4);
		}
		if ((HWND)lParam == P2_4)
		{
			launch_lift(2, 4);
		}
		if ((HWND)lParam == P3_4)
		{
			launch_lift(3, 4);
		}
		if ((HWND)lParam == P5_4)
		{
			launch_lift(5, 4);
		}
		if ((HWND)lParam == P1_5)
		{
			launch_lift(1, 5);
		}
		if ((HWND)lParam == P2_5)
		{
			launch_lift(2, 5);
		}
		if ((HWND)lParam == P3_5)
		{
			launch_lift(3, 5);
		}
		if ((HWND)lParam == P4_5)
		{
			launch_lift(4, 5);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////
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
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			InvalidateRect(hWnd, &drawArea1, TRUE);
			InvalidateRect(hWnd, &drawAreaF1, TRUE);
			InvalidateRect(hWnd, &drawAreaF2, TRUE);
			InvalidateRect(hWnd, &drawAreaF3, TRUE);
			InvalidateRect(hWnd, &drawAreaF4, TRUE);
			InvalidateRect(hWnd, &drawAreaF5, TRUE);
			hdc = BeginPaint(hWnd, &ps);
			MyOnPaint(hdc);
			EndPaint(hWnd, &ps);

			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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