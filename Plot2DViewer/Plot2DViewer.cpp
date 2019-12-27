#include <windows.h>
#include <windowsx.h>
#include "Data.h"
#include "Scene2D.h"
#include "Scene3D.h"
#include "Matrix.h"
#include "AffineTransform.h"
#include "Model2D.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� �������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Plot2D Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200, 200, 400, 400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Scene2D
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������

Scene3D scene(X0, Y0, px, py);

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch (msg)
	{
	case WM_PAINT:
	{
		HDC dc = GetDC(hWnd);
		scene.Clear(dc);				// ����� �������������� � ������ Camera2D ������, ����������� �� ������� ������� ������� ���� hWnd
										// scene.Plot(dc, Sinusoid);		// ����� �������������� � ������ Scene2D ������, ����������� �� ��������� ������� ���������
		scene.Render(dc);
		ReleaseDC(hWnd, dc);
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	case WM_SIZE:
	{
		HDC dc = GetDC(hWnd);
		scene.SetResolution(dc);
		ReleaseDC(hWnd, dc);
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
		{
			scene.model.Apply(Translation(-1, 0, 0));
			break;
		}
		case VK_RIGHT:
		{
			scene.model.Apply(Translation(1, 0, 0));
			break;
		}
		case VK_UP:
		{
			scene.model.Apply(Translation(0, 1, 0));
			break;
		}
		case VK_DOWN:
		{
			scene.model.Apply(Translation(0, -1, 0));
			break;
		}
		case 0x4A:
		{
			scene.model.Apply(Translation(0, 0, 1));
			break;
		}
		case VK_OEM_COMMA:
		{
			scene.model.Apply(RotationY(M_PI_4 / 8));
			break;
		}
		case VK_OEM_PERIOD:
		{
			scene.model.Apply(RotationY(-M_PI_4 / 8));
			break;
		}
		case 0x4B:
		{
			// K
			scene.model.Apply(RotationX(M_PI_4 / 8));
			break;
		}
		case 0x4C:
		{
			// L
			scene.model.Apply(RotationX(-M_PI_4 / 8));
			break;
		}
		case 0x49:
		{
			// I
			scene.model.Apply(RotationZ(M_PI_4 / 8));
			break;
		}
		case 0x4F:
		{
			// O
			scene.model.Apply(RotationZ(-M_PI_4 / 8));
			break;
		}
		}
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		scene.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (scene.IsDragging())
		{
			scene.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			InvalidateRect(hWnd, nullptr, false);
		}
		return 0;
	}
	case WM_LBUTTONUP:
	{
		scene.StopDragging();
		return 0;
	}
	//case WM_MOUSEWHEEL:
	//{
	//	double diff = GET_WHEEL_DELTA_WPARAM(wParam);
	//	POINT P;
	//	P.x = GET_X_LPARAM(lParam);
	//	P.y = GET_Y_LPARAM(lParam);
	//	ScreenToClient(hWnd, &P);
	//	if (diff < 0) {
	//		scene.changeSize(1.1, P.x, P.y);
	//	}
	//	else {
	//		scene.zoom(0.9, P.x, P.y);
	//	}
	//	InvalidateRect(hWnd, nullptr, false);
	//	return 0;
	//}
	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	return 0;
}
