#ifndef __POLYNOMIALS_H__
#define __POLYNOMIALS_H__

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

	Monom () { coef = 0; deg = 0; } // ����������� �� ���������
	Monom (double _coef, int  _deg) { coef = _coef; deg = _deg; } // ����������� � �����������

	Monom operator + (const Monom & m);

	friend int operator == (const Monom & m1, const Monom & m2) { 
		return (m1.coef == m2.coef) && (m1.deg == m2.deg); 
	}

	friend int operator != (const Monom & m1, const Monom & m2) {
		return !(m1 == m2);
	}

	friend istream & operator >> (istream &, Monom &);
	friend ostream & operator << (ostream &, const  Monom &);
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* ����� ������� */

class Polynomial
{
protected:
	List <Monom> pol;
public:
	Polynomial (): pol () {} // ����������� �� ��������� (��� ����������)
	Polynomial (Monom * _m, int n);
	Polynomial (char * line); // �������������
	Polynomial (const Polynomial & q) : pol (q.pol) {} // ����������� �����������

	~ Polynomial () {} // ����������

	int GetPolySize () { return pol.GetSize (); }

	void AddOfSimTerms (); // ���������� ��������

	Polynomial & operator = (const Polynomial & q) { 
		pol = q.pol; 
		return (*this);
	}
	Polynomial operator + (Polynomial & q); // ���������� �������� �������� ���������
	Polynomial operator - (Polynomial & q); // ���������� �������� �������� ���������
	Polynomial operator * (const Monom & m); // ���������� �������� ��������� �������� �� �����
	Polynomial operator * (Polynomial & q); // ���������� �������� ��������� ���������

	friend bool operator == (const Polynomial & p1, const Polynomial & p2) { return p1.pol == p2.pol; }
	friend bool operator != (const Polynomial & p1, const Polynomial & p2) { return p1.pol != p2.pol; }

	void Sort (Monom * arr, int n);

	friend istream & operator >> (istream & ins, Polynomial & p);
	friend ostream & operator << (ostream & outs, Polynomial & p); 
};

#endif