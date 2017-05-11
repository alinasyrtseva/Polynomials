#ifndef __POLYNOMIALS_H__
#define __POLYNOMIALS_H__

#include <cstdlib>
#include <iostream>

#include "List.h"

using namespace std;

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Структура Моном */

struct Monom
{
	double coef;
	int deg;

	Monom () { coef = 0; deg = 0; } // конструктор по умолчанию
	Monom (double _coef, int  _deg) { coef = _coef; deg = _deg; } // конструктор с параметрами

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

/* Класс Полином */

class Polynomial
{
protected:
	List <Monom> pol;
public:
	Polynomial (): pol () {} // конструктор по умолчанию (без параметров)
	Polynomial (Monom * _m, int n);
	Polynomial (char * line); // интерпретатор
	Polynomial (const Polynomial & q) : pol (q.pol) {} // конструктор копирования

	~ Polynomial () {} // деструктор

	int GetPolySize () { return pol.GetSize (); }

	void AddOfSimTerms (); // приведение подобных

	Polynomial & operator = (const Polynomial & q) { 
		pol = q.pol; 
		return (*this);
	}
	Polynomial operator + (Polynomial & q); // перегрузка операции сложения полиномов
	Polynomial operator - (Polynomial & q); // перегрузка операции сложения полиномов
	Polynomial operator * (const Monom & m); // перегрузка операции умножения полинома на моном
	Polynomial operator * (Polynomial & q); // перегрузка операции умножения полиномов

	friend bool operator == (const Polynomial & p1, const Polynomial & p2) { return p1.pol == p2.pol; }
	friend bool operator != (const Polynomial & p1, const Polynomial & p2) { return p1.pol != p2.pol; }

	void Sort (Monom * arr, int n);

	friend istream & operator >> (istream & ins, Polynomial & p);
	friend ostream & operator << (ostream & outs, Polynomial & p); 
};

#endif