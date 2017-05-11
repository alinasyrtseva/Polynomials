#include "Polynomials.h"
#include "List.h"

#include <iostream>

using namespace std;

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

istream & operator >> (istream & ins, Monom & m)
{
	cout << "Enter the monomial coefficient: ";
	ins >> m.coef;
	cout << "Enter the exponents of the degrees of variables X, Y and Z as (abc): ";
	ins >> m.deg;
	return ins;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

ostream & operator << (ostream & outs, Monom & m)
{
	if (m.coef == 0)
		outs << '0';
	else
	{
		if (m.coef != 1)
			outs << m.coef << '*';
		if (m.deg / 100 % 10 != 0) 
		{
			outs << 'x';
			if (m.deg / 100 % 10 != 1) 
				outs << '^' << m.deg / 100 % 10;
		}
		if (m.deg / 10 % 10 != 0)
		{
			outs << 'y';
			if (m.deg / 10 % 10 != 1) 
				outs << '^' << m.deg / 10 % 10;
		}
		if (m.deg % 10 != 0) 
		{
			outs << 'z';
			if (m.deg / 1 % 10 != 1) 
				outs << '^' << m.deg % 10;
		}
	}
	return outs;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

istream & operator >> (istream & ins, Polynomial & p)
	{
		int polysize;
		cout << "Enter the number of monomials in the polynomial: ";
	    ins >> polysize;
		Monom tmp;
		for (int i = 0; i < polysize; i ++) 
		{
			cout << "Enter the monomial coefficient: ";
			ins >> tmp.coef;
			cout << "Enter the exponents of the degrees of variables X, Y and Z as (abc): ";
			ins >> tmp.deg;
			p.pol.InsertInTheTail (tmp);
		}
		return ins; 
	}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
ostream & operator << (ostream & outs, Polynomial & p)
	{
		Node <Monom> * tmp1 = p.pol.ViewHead ();

		if (tmp1 == NULL) {
			outs << '0';
			return outs;
		}

		if (tmp1 -> Data.coef == 0)
			tmp1 = tmp1 -> Next;

		else
		{
			if (tmp1 -> Data.coef == -1) 
				outs << '-';

			else if (tmp1 -> Data.coef != 1) 
			{
				outs << tmp1 -> Data.coef;
			    if (tmp1 -> Data.deg != 0) 
					outs << '*';
			}

			if (tmp1 -> Data.deg / 100 % 10 != 0) 
			{
				outs << 'x';
				if (tmp1 -> Data.deg / 100 % 10 != 1) 
					outs << '^' << tmp1 -> Data.deg / 100 % 10;
			}
			if (tmp1 -> Data.deg / 10 % 10 != 0)
			{
				outs << 'y';
				if (tmp1 -> Data.deg / 10 % 10 != 1) 
					outs << '^' << tmp1 -> Data.deg / 10 % 10;
			}
			if (tmp1 -> Data.deg % 10 != 0) 
			{
				outs << 'z';
				if (tmp1 -> Data.deg / 1 % 10 != 1) 
					outs << '^' << tmp1 -> Data.deg % 10;
			}
			outs << ' ';
			tmp1 = tmp1 -> Next;
		}

		while (tmp1 != 0)
		{
			if (tmp1 -> Data.coef == 0)
			tmp1 = tmp1 -> Next;
			else
			{
				if (tmp1 -> Data.coef > 0)
					outs << '+';
				
				if (tmp1 -> Data.coef == -1) 
				outs << '-';

			else if (tmp1 -> Data.coef != 1) 
			{
				outs << tmp1 -> Data.coef;
			    if (tmp1 -> Data.deg != 0) 
					outs << '*';
			}

				if (tmp1 -> Data.deg / 100 % 10 != 0) 
				{
					outs << 'x';
					if (tmp1 -> Data.deg / 100 % 10 != 1) 
						outs << '^' << tmp1 -> Data.deg / 100 % 10;
				}
				if (tmp1 -> Data.deg / 10 % 10 != 0)
				{
					outs << 'y';
					if (tmp1 -> Data.deg / 10 % 10 != 1) 
						outs << '^' << tmp1 -> Data.deg / 10 % 10;
				}
				if (tmp1 -> Data.deg % 10 != 0) 
				{
					outs << 'z';
					if (tmp1 -> Data.deg / 1 % 10 != 1) 
						outs << '^' << tmp1 -> Data.deg % 10;
				}
				
				outs << ' ';

				tmp1 = tmp1 -> Next;
			}
		}
		return outs; 
	}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

Polynomial :: Polynomial (Monom * arr, int n) : pol (n)
{
	Sort (arr, n);

	int i = 0;
	for (Node <Monom> * p = pol.ViewHead (); p; p = p -> Next, i ++)
		if (arr[i].coef != 0) 
			p -> Data = arr [i];

	AddOfSimTerms ();
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Сортировка массива мономов по убыванию*/

void Polynomial :: Sort (Monom * arr, int n) 
{

	Monom tmp;
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n - 1 - i; j++)
			if (arr[j].deg > arr[j + 1].deg) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Приведение подобных (addition of similar terms) */

void Polynomial :: AddOfSimTerms () 
{
	Node <Monom> * tmp = pol.ViewHead ();

	while ((tmp != NULL) && (tmp -> Next != NULL))
	{
		if (tmp -> Data.deg == tmp -> Next -> Data.deg) 
		{
			if (tmp -> Data.coef + tmp->Next->Data.coef == 0) {
				pol.RemoveAfterPointer (tmp);
				pol.RemoveBeforePointer (tmp -> Next);
				
				tmp = pol.ViewHead ();		
			}
			else {
				tmp -> Data.coef = tmp -> Data.coef + tmp->Next->Data.coef;
			    pol.RemoveAfterPointer (tmp);	
			}
		}
		else {
			tmp = tmp -> Next;
		}
	}
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Интерпретатор */

Polynomial :: Polynomial (char * line)
{
	Monom tmp;
	int len = strlen (line);

	int i = 0;

	char ccoef_ [30];
	char cdeg_ [4];

	int k = 0;
	while ((isdigit (line [i])) || (line [i] == '.') || (line [i] == '-'))
	{
		ccoef_ [k] = line [i];
		k ++;
		i ++;
	}
	ccoef_ [k] = '\0';

	i = i + 3;

	double coef_ = atof (ccoef_);
	tmp.coef = coef_;

	cdeg_ [0] = line [i]; 
	cdeg_ [1] = line [i + 3];
	cdeg_ [2] = line [i + 6];
	cdeg_ [3] = '\0';

	int deg_ = atoi (cdeg_);
	i = i + 8;
	tmp.deg = deg_;

	pol.InsertInTheTail (tmp);

	while (i < len)
	{
		ccoef_ [0] = '\0';
		cdeg_ [0] = '\0';
		k = 0;
		if (line [i - 1] == '-') {
			ccoef_ [k] = '-';
			k ++;
		}


	while ((isdigit (line [i])) || (line [i] == '.') || (line [i] == '-'))
	{
		ccoef_ [k] = line [i];
		k ++;
		i ++;
	}
	ccoef_ [k] = '\0';

	i = i + 3;

	double coef_ = atof (ccoef_);
	tmp.coef = coef_;

	cdeg_ [0] = line [i]; 
	cdeg_ [1] = line [i + 3];
	cdeg_ [2] = line [i + 6];
	cdeg_ [3] = '\0';

	int deg_ = atoi (cdeg_);
	i = i + 8;
	tmp.deg = deg_;

	Node <Monom> * tmp1 = pol.ViewHead ();

	while ((tmp1 != NULL) && (tmp1 -> Data.deg > tmp.deg))
		  tmp1 = tmp1 -> Next;

	pol.InsertBeforePointer (tmp, tmp1);
	}

	if (GetPolySize () > 1) 
		AddOfSimTerms ();
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Перегрузка операции сложения полиномов */

Polynomial Polynomial :: operator + (Polynomial & q)
{
	Polynomial res;
	Node <Monom> * tmpA = pol.ViewHead ();
	Node <Monom> * tmpB = q.pol.ViewHead ();
	Monom tmp;

	while ((tmpA != NULL) && (tmpB != NULL))
	{

		if (tmpA -> Data.deg == tmpB -> Data.deg)
		{
			tmp.coef = (tmpA -> Data.coef) + (tmpB -> Data.coef);
			tmp.deg = tmpA -> Data.deg;
			if (abs (tmp.coef) > 1e-10)
				res.pol.InsertInTheTail (tmp);

			tmpA = tmpA -> Next;
			tmpB = tmpB -> Next;
		}
		else if (tmpA -> Data.deg < tmpB -> Data.deg)
		{
			res.pol.InsertInTheTail (tmpB -> Data);

			tmpB = tmpB -> Next;
		}
		else
		{
			res.pol.InsertInTheTail (tmpA -> Data);

			tmpA = tmpA -> Next;			
		}
	}
	while (tmpA != NULL)
	{
		res.pol.InsertInTheTail (tmpA -> Data);

		tmpA = tmpA -> Next;
	}
	while (tmpB != NULL)
	{
		res.pol.InsertInTheTail (tmpB -> Data);

		tmpB = tmpB -> Next;	
	}

	if (res.GetPolySize () > 1) 
	   res.AddOfSimTerms ();

	return res;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Перегрузка операции вычитания полиномов */

Polynomial Polynomial :: operator - (Polynomial & q)
{
	Polynomial res = q;

	Node <Monom> * tmpB = res.pol.ViewHead ();

	while (tmpB != NULL) {
		tmpB -> Data.coef = -1 * (tmpB -> Data.coef);
		tmpB = tmpB -> Next;
	}

	res = (*this) + res;


	if (res.GetPolySize () > 1) 
	 res.AddOfSimTerms ();


	return res;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Перегрузка операции умножения полинома на моном */

Polynomial Polynomial :: operator * (const Monom & m)
{
	Polynomial res;
	Node <Monom> * tmpA = pol.ViewHead ();
	Monom tmp;

	int d = m.deg;
	double c = m.coef;

	int _d;

	while (tmpA != NULL) 
	{

	if (((tmpA -> Data.deg) / 100  + d / 100  > 9) || ((tmpA -> Data.deg) / 10 % 10 + d / 10 % 10 > 9) || ((tmpA -> Data.deg) % 10 + d % 10 > 9)) 
	{
		throw 1; 
		return Polynomial ();
	}
		_d = (tmpA -> Data.deg) + d;
		

				tmp.deg = _d;
				tmp.coef = c * (tmpA -> Data.coef);

				res.pol.InsertInTheTail (tmp);
				tmpA = tmpA -> Next;

	}


	return res;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Перегрузка операции умножения полиномов */

Polynomial Polynomial :: operator * (Polynomial & q)
{
	Polynomial res, tmp;

	Node <Monom> * tmpB = q.pol.ViewHead ();

	tmp = (*this) * (tmpB -> Data);
			res = tmp;
			tmpB = tmpB -> Next;

		while (tmpB != NULL)
		{
			tmp = (*this) * (tmpB -> Data);
			res = res + tmp;
			tmpB = tmpB -> Next;
		}

		return res;
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
