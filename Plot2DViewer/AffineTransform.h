#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H
#include <math.h>
Matrix<> Translation(double x, double y, double z)
{
	double T[16] = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, T);
}

Matrix<> Rotation(double t)
{
	double T[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, T);
}
Matrix<> Scaling(double kx, double ky)
{	double T[9] = {
		kx, 0, 0,
		0, ky, 0,
		0, 0, 1};
	return Matrix<>(3, 3, T);
}

Matrix<> Scaling(double kx, double ky, double kz)
{
	double T[16] = {
		kx,  0, 0, 0,
		0, ky, 0, 0,
		0,  0, kz, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, T);
}

Matrix<> Identify()
{
	double T[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, T);
}

Matrix<> RotationX(double t)
{
	double T[16] = {
		1, 0, 0, 0,
		0, cos(t), -sin(t), 0,
		0, sin(t),  cos(t), 0,
		0, 	    0,       0, 1
	};
	return Matrix<>(4, 4, T);
}

Matrix<> RotationX(double c, double s)
{
	double T[16] = {
		1, 0, 0, 0,
		0, c, -s, 0,
		0, s,  c, 0,
		0, 	    0,       0, 1
	};
	return Matrix<>(4, 4, T);
}

Matrix<> RotationY(double t)
{
	double T[16] = {
		cos(t), 0, sin(t), 0,
		0, 1, 0,       0,
		-sin(t), 0, cos(t),  0,
		0, 0, 0,       1
	};
	return Matrix<>(4, 4, T);
}

Matrix<> RotationY(double c, double s)
{
	double T[16] = {
		c, 0, s, 0,
		0, 1, 0,       0,
		-s, 0, c,  0,
		0, 0, 0,       1
	};
	return Matrix<>(4, 4, T);
}

Matrix<> RotationZ(double t)
{
	double T[16] = {
		cos(t), -sin(t), 0, 0,
		sin(t),  cos(t), 0, 0,
		0,       0, 1, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, T);
}

Matrix<> RotationZ(double c, double s)
{
	double T[16] = {
		c, -s, 0, 0,
		s,  c, 0, 0,
		0,       0, 1, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, T);
}

Matrix<> Rotation(double c, double s)
{	double inter = 1 / sqrt(c*c + s*s);
	double T[9] = {
		inter * c, -inter * s, 0,
		inter * s, inter * c, 0,
		0, 0, 1};
	return Matrix<>(3, 3, T);
}

Matrix<> MappingX()
{
	double T[9] = {
		1,  0, 0,
		0, -1, 0,
		0,  0, 1
	};
	return Matrix<>(3, 3, T);
}

Matrix<> MappingY()
{
	double T[9] = {
		-1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
	return Matrix<>(3, 3, T);
}

Matrix<> MappingO()
{
	double T[9] = {
		-1,  0, 0,
		0, -1, 0,
		0,  0, 1
	};
	return Matrix<>(3, 3, T);
}

Matrix<> Reflection(double x1, double x2, double y1, double y2)
{
	double a = y1 - y2;
	double b = x2 - x1;
	double c = x1* y2 - x2 * y1;

	double inter = 1 / (a * a + b * b);
	double T[9] = {
		inter * (b*b - a*a), inter * (-2*a*b), inter * (-2*a*c),
		inter * (-2*a*b), inter * (a*a - b*b), inter * (-2*b*c),
		0, 0, inter * (a*a + b*b) };
	return Matrix<>(3, 3, T);
}

// ����� ��������� ����������� �������, ������������ ������� ������� ��:
// Rotation(c, s) - ������� �� ����, ������� � ����� �������� ��������������� ��������� c � s;

// � ���������� ������� ������������ ����������� ������� �� ������.
// �������������� ���� � ������ �������� �������� ������.
// ��������, ����� �������, ��������� ��������� �������,
// � ����������� ���������������� ��������� � �������������.

#endif AFFINE_TRANSFORM_H
