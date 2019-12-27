#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double X0, Y0;						// �������� ���������� ������ ������� ������� ���������
	double px, py;						// ������� �������� ������� ������� ���������, ���������� � ��������
	int W, H;							// ���������� ������� ������� ����
	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return px*X + X0;
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return Y0 - py*Y;
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return (X - X0)/px;
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return (Y - Y0)/py;
	}
	double L()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return -(X0/px);
	}
	double R()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	{
		return (W-X0)/px;
	}
	double T()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return Y0/py;
	}
	double B()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	{
		return -(H-Y0)/py;
	}
	double previousX,
		previousY;
	
private:
	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
	bool isDragging, isAxes;
	
public:
	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
	{
		isDragging = false;
		previousX = 0;
		previousY = 0;
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc),&r);
		Rectangle(dc,0,0,r.right,r.bottom);
	}
	void SetResolution(HDC dc)
	{
		// ������ ��������� ���������� ��� ��������� �������� ����
		// � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� X0, Y0, px, py ����� �������, ����� ���������� ���������� �������� �� ������������ ����
		RECT r;
		GetClientRect(WindowFromDC(dc),&r);
		H = r.bottom + 1;
		W = r.right + 1;
	}
	void MoveTo(double X, double Y)
	{
		// ����������� ������������ ������� (posX, posY)
		// �������� ��������, ��� �� ��������� � ������� �����������
		
			posX = X;
			posY = Y;
	}
	void LineTo(HDC dc, double X, double Y)
	{
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);		
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);

	}
	void Axes(HDC dc)
	{
		// ��������� ������������ ����
		isAxes = true;
		MoveTo(0, 0);
		LineTo(dc, R(), 0);
		MoveTo(0, 0);
		LineTo(dc, L(), 0);
		MoveTo(0, 0);
		LineTo(dc, 0, T());
		MoveTo(0, 0);
		LineTo(dc, 0, B());
		isAxes = false;
	}

	void changeSize(int t){
		int newSize = t*5;

		double new_px = px + px/py * newSize;
		double new_py = py + py/px * newSize;
		
		if (new_px > 10)

			px = new_px;
		
		if (new_py > 10)
			py = new_py;
	}

	void StopDragging()
	{
		isDragging = false;
	}

	bool IsDragging()
	{
		return isDragging;
	}

	void StartDragging(int X, int Y)
	{
		isDragging = true;
		previousX = X;
		previousY = Y;
	}
	void Drag(int X, int Y)
	{
		//X0 = X;
		//Y0 = Y;
		X0 += X - previousX;
		Y0 += Y - previousY;
		previousX = X;
		previousY = Y;
		//X -= previousX;
		//Y += previousY;
		///*X = X - X0;
		//Y = Y + Y0;*/
		//previousX = ScreenToWorldX(X);
		//previousY = ScreenToWorldY(Y);
	}
};

#endif CAMERA_2D_H
