#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include <cstdlib>
#include <iostream>

#include "List.h"

using namespace std;

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* ��������� ����� */

struct Monom
{
	double coef;
	int deg;

	Monom ()
	{
		coef = 0;
		deg = 0;
	}
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* ����� ������� */

class Polynomial
{
protected:
	List <Monom> pol;
public:
	Polynomial ():pol(){} // ����������� �� ��������� (��� ����������)

	Polynomial (char * line); // ����������� � ����������
	Polynomial (const Polynomial & q); // ����������� �����������

	void Sort (Polynomial q); // �������������� ������� �� �������� ��������
	Polynomial AddOfSimTerms (const Polynomial & q); // ���������� ��������

	Polynomial & operator + (const Polynomial & q); // ���������� �������� �������� ���������
	Polynomial & operator * (const Polynomial & q); // ���������� �������� ��������� ���������
};

#endif