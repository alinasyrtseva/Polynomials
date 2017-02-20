#include "Polynomials.h"
#include "List.h"

/* Конструктор с параметром */

Polynomial :: Polynomial (char * line)
{
	
//ЗАМЕЧАНИЕ: если у монома коэффициент равен 1, пользователь должен ввести его


	//Node <Monom> * fict = new Node <Monom>;
	Node <Monom> * tmp = new Node <Monom>;

	/*fict -> Data.deg = 0;
	fict -> Data.coef = 0;
	fict -> Next = NULL;*/

	pol.InsertNodeInTheTail (tmp);

	int len = strlen (line);

	int i = 0;

	while ((isdigit (line [i + 1])) || (line [i + 1] == '.'))
	{
		//ccoef_ = ccoef_ + line [i + 1];
		i ++;
	}
	//double coef_ = atof (ccoef_);
	//tmp -> Data.coef = coef_;

	int deg_ = (line [i + 2] * 100) + (line [i + 6] * 10) + line [i + 10];
	i = i + 11;
	tmp -> Data.deg = deg_;

	pol.InsertNodeInTheTail (tmp);

	while (i < len)
	{
		if (line [i] == '+')
		{
			i ++;
			while ((isdigit (line [i + 1])) || (line [i + 1] == '.'))
			{
				//ccoef_ = ccoef_ + line [i + 1];
				i ++;
			}
			//double coef_ = atof (ccoef_);
			//tmp -> Data.coef = coef_;

			int deg_ = (line [i + 2] * 100) + (line [i + 6] * 10) + line [i + 10];
			i = i + 11;
			tmp -> Data.deg = deg_;

			pol.InsertNodeInTheTail (tmp);
		}
	}
	tmp -> Next = NULL;
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Конструктор копирования 

Polynomial :: Polynomial (const Polynomial & q)
{
	Node <Monom> * tmpA = pol.ViewHead () -> Next;
	//Node <Monom> * tmpB = q.ViewHead ();

	double c;

	while (tmpA != NULL)
	{
		tmpB -> Next = new Node <Monom>;
		tmpB -> Next -> Data.coef = tmpA -> Data.coef;
		tmpB -> Next -> Data.deg = tmpA -> Data.deg;
		tmpB = tmpB -> Next;
		tmpA = tmpA -> Next;
	}
	tmpB -> Next = NULL;

};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Упорядочивание мономов по убыванию степеней 

void Polynomial :: Sort (Polynomial pol)
{
	Node <Monom> * ptr = pol.ViewHead () -> Next, * tmp = NULL, * prev = NULL;
    bool flag = false;  
	head_ = pol.ViewHead () -> Next;
    do
    {
        flag = false;
        ptr = pol.ViewHead () -> Next;
        while (ptr -> Next)
        {
            if (ptr -> Data.deg < ptr -> Next -> Data.deg)
            {
                if (ptr == head_)
                {
                    tmp = ptr;
                    ptr = tmp -> Next;
                    tmp -> Next = ptr -> Next;
                    ptr -> Next = tmp;
                    head_ = ptr;
                    flag = true;                    
                }
                else
                {
                    tmp = ptr;
                    ptr = tmp->Next;
                    tmp -> Next = ptr -> Next;
                    ptr -> Next = tmp;
                    prev -> Next = ptr;
                    flag = true;
                }
            }
            prev = ptr;
            ptr = ptr -> Next;
        }
    }
    while (flag);
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/
 
/* Приведение подобных (addition of similar terms) */

Polynomial Polynomial :: AddOfSimTerms (const Polynomial & q) 
{
	Node <Monom> * tmp1 = pol.ViewHead ();
	while (tmp1 != NULL)
	{
		tmp1 = tmp1 -> Next;
		Node <Monom> * tmp2 = tmp1 -> Next;
		Node <Monom> * buf = tmp1;
		while (tmp2 != NULL)
		{
			if ((tmp1 -> Data.deg) == (tmp2 -> Data.deg))
			{
				tmp1 -> Data.coef = (tmp1 -> Data.coef) + (tmp2 -> Data.coef);
				pol.RemoveAfterPointer (buf);
			}
			buf = tmp2;
			tmp2 = tmp2 -> Next;
		}
	}
	
	return *this;
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Перегрузка операции сложения полиномов 

Polynomial & Polynomial :: operator + (const Polynomial & q)
{
	Polynomial res;
	Node <Monom> * tmpA = pol.ViewHead () -> Next;
	Node <Monom> * tmpB = q.ViewHead () -> Next;
	Node <Monom> * tmpC = res.ViewHead () -> Next;

	Node <Monom> * headres = tmpC;

	double c;

	while (tmpA != NULL)
	{
		while (tmpB != NULL)
		{
			if ((tmpA -> Data.deg) == (tmpB -> Data.deg))
			{
				c = tmpA -> Data.coef + tmpB -> Data.coef;
				tmpC -> Next = new Node <Monom>;
				tmpC -> Next -> Data.coef = c;
				tmpC -> Next -> Data.deg = tmpA -> Data.deg;
				tmpC = tmpC -> Next;
			}
				
				tmpB = tmpB -> Next;
				
		}
		tmpA = tmpA -> Next;
	}
	tmpC -> Next = NULL;
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Перегрузка операции умножения полиномов 

Polynomial & Polynomial :: operator * (const Polynomial & q)
{
	Polynomial res;
	Node <Monom> * tmpA = pol.ViewHead () -> Next;
	Node <Monom> * tmpB = q.ViewHead () -> Next;
	Node <Monom> * tmpC = res.ViewHead () -> Next;

	Node <Monom> * headres = tmpC;

	int d;

	while (tmpA != NULL)
	{
		while (tmpB != NULL)
		{
			tmpC -> Next = new Node <Monom>;
			tmpC -> Next -> Data.coef = tmpA -> Data.coef * tmpB -> Data.coef;
			d = tmpA -> Data.deg + tmpB -> Data.deg;
			if (((d / 100) > 9) || (((d / 10) % 10) > 9) || ((d % 100) > 9))
			{
				throw 1;
				return;
			}
			else
			tmpC -> Next -> Data.deg = d;
			tmpB = tmpB -> Next;				
			tmpC = tmpC -> Next;
		}
		tmpA = tmpA -> Next;
	}
	tmpC -> Next = NULL;
};*/