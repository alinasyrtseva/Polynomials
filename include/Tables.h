#ifndef __TABLES_H__
#define __TABLES_H__

#include <string>
#include <iostream> 

#include "List.h"
#include "Polynomials.h"

using namespace std;


/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* ����� ����� (�������) ������� */

class TabRecord {

protected:
	string key; // ��� ������ (����)
	Polynomial * body; // ���� ������

public:
	TabRecord () { key = ""; body = new Polynomial; } // ����������� �� ���������
	TabRecord (string key_, Polynomial & body_) { key = key_; body = new Polynomial (body_); }  // ����������� � �����������

	TabRecord (const TabRecord & trec) { // ����������� �����������
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

	// ������
	string GetKey () { return key; }
	Polynomial GetBody () { return * body; }

	// ������ ������

	friend ostream & operator << (ostream & outs, TabRecord & trec) {
		outs << trec.key;
		if (trec.body != NULL)
			outs << "     " << (* trec.body);
		outs << endl;
		return outs;
	}

};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* ������� - ������� ����� */

class Table {

protected:
	int size; // ����. ��������� ���������� �������
	int count; // ���������� �������
	int pos; // ����� ������� ������

public:
	Table (int size_ = 0) { // �����������
		size = size_;
		count = 0;
		pos = 0;
	}
	
	// �������������� ������
	int	IsEmpty () { // �����?
		if (count == 0)
			return 1;
		return 0;
	} 

	int	IsFull () { // ���������?
		if (count == size)
			return 1;
		return 0;
	}

	// �������� ������
	virtual TabRecord * FindRecord (string key_) = 0; // ����� ������
	virtual void InsRecord (string key_, Polynomial body_) = 0; // ������� ������
	                                      // ������� � �����
	virtual void DelRecord (string key_) = 0; // �������� ������

	// ���������
	virtual void Reset () { pos = 0; } // ���������� �� ������ ������
	virtual int	GoNext () { // ������� � ��������� ������
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

	// ������
	int GetCount () { return count; }
	int GetSize () { return size; }
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* ��������������� ������� */

class ScanTable : public Table {

protected:
	TabRecord ** recs;

public:

	ScanTable (int size_= 0) : Table (size_) { // �����������
		recs = new TabRecord * [size_];
		for (int i = 0; i < size_; i ++)
			recs [i] = NULL;
	}

	ScanTable (ScanTable & tab) { // ����������� �����������
		size = tab.size;
		count = tab.count;
		pos = 0;
		for (int i = 0; i < size; i ++)
			recs [i] = (tab.GetRec (i));                  // ����������� ����������� � ���������� �������� = ��� ������� ����
	}

	~ ScanTable () { delete [] recs; } // ����������

	virtual TabRecord * FindRecord (string key_) {
		for (int i = 0; i < count; i ++)
			if (key_ == recs [i] -> GetKey ()) {
				pos = i;
				return recs [i];
			}
		return NULL;
	}

	virtual void InsRecord (string key_, Polynomial body_) { // ������� � �����
		if (IsFull ()) 
			throw 1;
		recs [count] = new TabRecord (key_, body_);
		count ++;
	}

	virtual void DelRecord (string key_) { // �������� ������
		if (IsEmpty ())
			throw 1;
		if (FindRecord (key_) == NULL)
			return;
		delete recs [pos];
		recs [pos] = recs [count - 1];
		count --;
	}

	void Print () { // ������ �������
		for (int i = 0; i < count; i ++)
			cout << recs [i] -> GetKey() << "   " << recs [i] -> GetBody () << endl;
	}

	TabRecord * GetRec (int i) { return recs [i]; }
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

/* ������������� ������� */

class SortTable : public ScanTable {

public:

	SortTable (int size_) : ScanTable (size_) {}; // �����������

	~ SortTable () { delete [] recs; } // ����������

	virtual TabRecord * FindRecord (string key_) { // �������� (��������) �����, ���������
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

	virtual void InsRecord (string key_, Polynomial body_) { // ������� ������
		if (IsFull ())
			throw 1;
		TabRecord * tmp;
		tmp = FindRecord (key_);

		// ����� ������ ����� ������� ������ (�����������)
		for (int i = count + 1; i >= pos + 1; i --)
			recs [i] = recs [i - 1];


		recs [pos] = new TabRecord (key_, body_);
		count ++;
	};

	virtual void DelRecord (string key_) { // �������� ������
		if (IsEmpty ())
			return;
		if (FindRecord (key_) == NULL)
			throw 1;

		// ����� ������ ����� ������� ����� (�����������)
		for (int i = pos; i < count - 1; i ++)
			recs [i] = recs [i + 1];


		recs [count] = NULL;
		count --;
	}

	void Sort (); // ���������� ���������

	TabRecord * Min ();
};

/*----------------------------------------------------------------------------------------------------------------------------------------------*/

void SortTable :: Sort () { // ���������� ���������
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