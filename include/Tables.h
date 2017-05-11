#ifndef __TABLES_H__
#define __TABLES_H__

#include <string>
#include <iostream> 

#include "List.h"
#include "Polynomials.h"

using namespace std;


/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Класс строк (записей) таблицы */

class TabRecord {

protected:
	string key; // имя записи (ключ)
	Polynomial * body; // тело записи

public:
	TabRecord () { key = ""; body = new Polynomial; } // конструктор по умолчанию
	TabRecord (string key_, Polynomial & body_) { key = key_; body = new Polynomial (body_); }  // конструктор с параметрами

	TabRecord (const TabRecord & trec) { // конструктор копирования
		key = trec.key;
		body = new Polynomial (* trec.body);
	}


	TabRecord & operator = (TabRecord & trec) {
		if (trec != (*this)) {
			if (body != NULL) delete body;
			if (trec.body != NULL) 
				body = new Polynomial (* trec.body);
			else body = NULL;
			key = trec.key;
		}
		return trec;
	}

	friend int operator == (const TabRecord & trec1, const TabRecord & trec2) {
		return (trec1.key == trec2.key);
	}

	friend int operator!= (TabRecord & trec1, TabRecord & trec2) {
		return !(trec1 == trec2);
	}

	// доступ
	string GetKey () { return key; }
	Polynomial GetBody () { return * body; }

	// печать записи

	friend ostream & operator << (ostream & outs, TabRecord & trec) {
		outs << trec.key;
		if (trec.body != NULL)
			outs << "     " << (* trec.body);
		outs << endl;
		return outs;
	}

};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Таблицы - базовый класс */

class Table {

protected:
	int size; // макс. возможное количество записей
	int count; // количество записей
	int pos; // номер текущей записи

public:
	Table (int size_ = 0) { // конструктор
		size = size_;
		count = 0;
		pos = 0;
	}
	
	// информационные методы
	int	IsEmpty () { // пуста?
		if (count == 0)
			return 1;
		return 0;
	} 

	int	IsFull () { // заполнена?
		if (count == size)
			return 1;
		return 0;
	}

	// основные методы
	virtual TabRecord * FindRecord (string key_) = 0; // поиск записи
	virtual void InsRecord (string key_, Polynomial body_) = 0; // вставка записи
	                                      // вставка в конец
	virtual void DelRecord (string key_) = 0; // удаление записи

	// навигация
	virtual void Reset () { pos = 0; } // установить на первую запись
	virtual int	GoNext () { // переход к следующей записи
		if (!IsTabEnded ())	{
			pos ++;
			return 1;
		}
		return 0;
	}

	virtual int IsTabEnded () {
		if (pos == count)
			return 1;
		return 0;
	}

	// доступ
	int GetCount () { return count; }
	int GetSize () { return size; }
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Просматриваемые таблицы */

class ScanTable : public Table {

protected:
	TabRecord ** recs;

public:

	ScanTable (int size_= 0) : Table (size_) { // конструктор
		recs = new TabRecord * [size_];
		for (int i = 0; i < size_; i ++)
			recs [i] = NULL;
	}

	ScanTable (ScanTable & tab) { // конструктор копирования
		size = tab.size;
		count = tab.count;
		pos = 0;
		for (int i = 0; i < size; i ++)
			recs [i] = (tab.GetRec (i));                  // конструктор копирования и перегрузка операции = для записей есть
	}

	~ ScanTable () { delete [] recs; } // деструктор

	virtual TabRecord * FindRecord (string key_) {
		for (int i = 0; i < count; i ++)
			if (key_ == recs [i] -> GetKey ()) {
				pos = i;
				return recs [i];
			}
		return NULL;
	}

	virtual void InsRecord (string key_, Polynomial body_) { // вставка в конец
		if (IsFull ()) 
			throw 1;
		recs [count] = new TabRecord (key_, body_);
		count ++;
	}

	virtual void DelRecord (string key_) { // удаление записи
		if (IsEmpty ())
			throw 1;
		if (FindRecord (key_) == NULL)
			return;
		delete recs [pos];
		recs [pos] = recs [count - 1];
		count --;
	}

	void Print () { // печать таблицы
		for (int i = 0; i < count; i ++)
			cout << recs [i] -> GetKey() << "   " << recs [i] -> GetBody () << endl;
	}

	TabRecord * GetRec (int i) { return recs [i]; }
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* Упорядоченные таблицы */

class SortTable : public ScanTable {

public:

	SortTable (int size_) : ScanTable (size_) {}; // конструктор

	~ SortTable () { delete [] recs; } // деструктор

	virtual TabRecord * FindRecord (string key_) { // двоичный (бинарный) поиск, дихотомия
		int left = 0;
		int right = count - 1;
		int mid;
		while (left <= right) {
			mid = left + (right - left) / 2;
			if (key_ < (recs [mid] -> GetKey ())) {
				right = mid - 1;
				pos = left;
			}
			else if (key_ > (recs [mid] -> GetKey ())) {
				left = mid + 1;
				pos = left;
			}
			else {
				pos = mid;
				return recs [mid];
			}
		}
		return 0;
	}

	virtual void InsRecord (string key_, Polynomial body_) { // вставка записи
		if (IsFull ())
			throw 1;
		TabRecord * tmp;
		tmp = FindRecord (key_);

		// сдвиг правой части таблицы вправо (перепаковка)
		for (int i = count + 1; i >= pos + 1; i --)
			recs [i] = recs [i - 1];


		recs [pos] = new TabRecord (key_, body_);
		count ++;
	};

	virtual void DelRecord (string key_) { // удаление записи
		if (IsEmpty ())
			return;
		if (FindRecord (key_) == NULL)
			throw 1;

		// сдвиг правой части таблицы влево (перепаковка)
		for (int i = pos; i < count - 1; i ++)
			recs [i] = recs [i + 1];


		recs [count] = NULL;
		count --;
	}

	void Sort (); // сортировка пузырьком

	TabRecord * Min ();
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

void SortTable :: Sort () { // сортировка пузырьком
	TabRecord * tmp;
	for (int i = 0; i < count; i ++)
		for (int j = i + 1; j < count; j ++)
			if (recs [i] -> GetKey () > recs [j] -> GetKey ()) 
				{ tmp = recs [i]; recs [i] = recs [j]; recs[j] = tmp; }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

TabRecord * SortTable :: Min () { return recs [0]; }

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

#endif