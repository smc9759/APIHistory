#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="Client";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
} 

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;
	static RECT rt;
	switch(iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd, &rt);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		MyPen = CreatePen(PS_SOLID, 5, RGB(0,0,255));
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		MyBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
		OldBrush = (HBRUSH)SelectObject(hdc,MyBrush);
		
		Rectangle(hdc,50,50,300,200);

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		
		SelectObject(hdc,OldBrush);
		DeleteObject(MyBrush);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		GetClientRect(hWnd, &rt);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}