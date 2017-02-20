#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

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

	Monom ()
	{
		coef = 0;
		deg = 0;
	}
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Класс Полином */

class Polynomial
{
protected:
	List <Monom> pol;
public:
	Polynomial ():pol(){} // конструктор по умолчанию (без параметров)

	Polynomial (char * line); // конструктор с параметром
	Polynomial (const Polynomial & q); // конструктор копирования

	void Sort (Polynomial q); // упорядочивание мономов по убыванию степеней
	Polynomial AddOfSimTerms (const Polynomial & q); // приведение подобных

	Polynomial & operator + (const Polynomial & q); // перегрузка операции сложения полиномов
	Polynomial & operator * (const Polynomial & q); // перегрузка операции умножения полиномов
};

#endif