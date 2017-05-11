#ifndef __LIST_H__
#define __LIST_H__


#include <cstdlib>
#include <iostream>

using namespace std;


//  ласс —писок

template <class ValType>
struct Node {
	ValType Data; // информационное поле
	Node <ValType> * Next; // указатель св€зи
};

template <class ValType>
class List
{
protected:
	Node <ValType> * Head;
	int Size;
public:

	List (int s = 0) // конструктор по умолчанию
	{

	if (s < 0) throw 1;

	Size = s;

	if (Size == 0) { Head = NULL; return; }

	Head = new Node<ValType> ;
	Node<ValType>* tmp=Head;
	for (int i = 1; i < Size; i++) {
		tmp->Next = new Node<ValType>;
		tmp = tmp->Next;
	}
	tmp->Next = NULL;
}

	List (const List & l); // конструктор копировани€

	~ List (); // деструктор

	int GetSize () const // получить размер списка
	{
		return Size;
	}


	int IsEmpty () const // проверка на пустоту
	{ 
		if (Head) 
			return 0; 
		return 1; 
	}


	List & operator = (const List & l);

	bool operator == (const List & l) const;
	bool operator != (const List & l) const;

	void InsertInTheHead  (ValType _data); // вставка звена с заданным ключом в начало списка
	void InsertInTheTail (ValType _data); // вставка звена с заданным ключом в конец списка
	void InsertAfterPointer (ValType _data, Node <ValType> * ptr); // вставка звена с заданным ключом после указател€
	void InsertBeforePointer (ValType _data, Node <ValType> * ptr); // вставка звена с заданным ключом до указател€

	void InsertNodeInTheTail (Node <ValType> * ptr);
	void InsertNodeInTheHead (Node <ValType> * ptr);

	void RemoveFromTheHead (); // удаление звена из начала списка
	void RemoveFromTheTail (); // удаление звена из конца списка
	void RemoveAfterPointer (Node <ValType> * ptr); // удаление звена после указател€
	void RemoveBeforePointer (Node <ValType> * ptr); // удаление звена до указател€
	void Remove (int n);

	Node <ValType> * SearchByKey (ValType _data); // поиск звена по ключу

	ValType ViewPointerData (Node <ValType> * ptr) // получить данные звена
	{
		return (ptr -> Data); 
	}	

	ValType ViewHeadData () // получить данные головы списка
	{
		return (Head -> Data); 
	}	

	Node <ValType> * ViewHead ()
	{
		return Head;
	}

	ValType ViewTailData () // получить данные хвоста списка
	{
		Node <ValType> * tmp = Head;
		while (tmp -> Next != NULL) 
			tmp = tmp -> Next;
		return tmp -> Data; 
	}


	template <class Type> friend istream& operator >> (istream &istr, List<ValType>& l);
	template <class Type> friend ostream& operator << (ostream &ostr, const  List<ValType>& l);

	
};










template <class ValType>
List <ValType> :: List (const List <ValType> & l)
{
	Head = NULL;
	Size = 0;

	Node <ValType> * tmp = l.Head;
	while (tmp != NULL) {
		InsertInTheTail (tmp -> Data);
		tmp = tmp -> Next;
	}
}


template <class ValType>
List <ValType> :: ~ List ()
{
	Node <ValType> * tmp;
	while (Head)
	{
		tmp = Head -> Next;
		delete Head;
		Head = tmp;
	}
}


template <class ValType>
List <ValType> & List <ValType> :: operator = (const List & l)
{
	if (this != &l) {
		if (Size >= l.Size) {
			for (int i = l.Size, s = Size; i < s; i++) RemoveFromTheTail ();
			for (Node <ValType> * pf = Head, * plf = l.Head; pf; pf = pf -> Next, plf = plf -> Next)
				pf -> Data = plf -> Data;
		}
		else {
			Node <ValType> * plf = l.Head;
			for (Node <ValType>* pf = Head; pf; pf = pf -> Next, plf = plf -> Next)
				pf -> Data = plf -> Data;
			for(; plf; plf = plf -> Next) 
				InsertInTheTail (plf -> Data);
		}
		Size = l.Size;
	}
	return * this;
}

template <class ValType>
bool List <ValType> :: operator == (const List & l) const
{
	if (Size != l.Size) return false;
	for (Node <ValType> * pf = Head, *plf = l.Head; pf ; plf = plf->Next, pf = pf->Next)
		if ((pf->Data) != (plf->Data)) return false;
	return true;
}

template <class ValType>
bool List <ValType> :: operator != (const List & l) const
{
	return !(*this == l);
}

template <class ValType>
void List <ValType> :: InsertInTheHead (ValType _data)
{
	Node <ValType> * tmp = new Node <ValType>;

	tmp -> Data = _data;
	tmp -> Next = Head;


	Head = tmp;
	Size ++;
}


template <class ValType>
void List <ValType> :: InsertNodeInTheHead (Node <ValType> * ptr)
{

	ptr -> Next = Head;
	Head = ptr;
	Size ++;
}

template <class ValType>
void List <ValType> :: InsertInTheTail (ValType _data)
{
	if (IsEmpty ()) 
	{ 
		InsertInTheHead (_data); 
		return;
	}
	Node <ValType> * tmp = new Node <ValType>;

	tmp -> Data = _data;
	tmp -> Next = NULL;

	Node <ValType> * ptr = Head;
	while (ptr -> Next != NULL) 
		ptr = ptr -> Next;
	ptr -> Next = tmp;
	Size ++;
}

template <class ValType> 
void List <ValType> :: InsertAfterPointer (ValType _data, Node <ValType> * ptr)
{
	if (ptr)
	{
		Node <ValType> * tmp = new Node <ValType>;

		tmp -> Data = _data;
		tmp -> Next = ptr -> Next;

		ptr -> Next = tmp;
		Size ++;
	}
	else
	{
		Node <ValType> * tmp = new Node <ValType>;

		tmp -> Data = _data;
		tmp -> Next = NULL;


		Head = tmp;
		Size ++;
	}
}


template <class ValType> 
void List <ValType> :: InsertBeforePointer (ValType _data, Node <ValType> * ptr)
{
	if (ptr == Head)
		InsertInTheHead (_data);
	else
	{
		Node <ValType> * tmp = Head;

		while (tmp -> Next != ptr)
			tmp = tmp -> Next;


		Node <ValType> * tmp1 = new Node <ValType>;
		tmp1 -> Data = _data;
		tmp1 -> Next = tmp -> Next;

		tmp -> Next = tmp1;

		Size ++;
	}
}




template <class ValType> 
void List <ValType> :: InsertNodeInTheTail (Node <ValType> * ptr)
{
	if (IsEmpty ()) 
	{ 
		Head -> Next = ptr;
		ptr -> Next = NULL;

		Size ++;

		return;
	}

		Node <ValType> * tmp = Head;
		while (tmp -> Next != NULL) 
			tmp = tmp -> Next;
		tmp -> Next = ptr;
		ptr -> Next = NULL;
		Size ++;

}



template <class ValType> 
/*удаление элемента с заданным номером из однонаправленного списка*/
void List <ValType> :: Remove (int n) 
{
	Node <ValType> * ptr; //вспомогательный указатель
    Node <ValType> * Current = Head;
    for (int i = 1; (i < n) && (Current != NULL); i++)
    Current = Current -> Next;
    if (Current != NULL) { //проверка на корректность
		if (Current == Head) { //удал€ем первый элемент
			Head = Head->Next;
            delete(Current);
			Size --;
            Current = Head;
		}
        else {//удал€ем непервый элемент
          ptr = Head;
          while (ptr->Next != Current)
            ptr = ptr->Next; 
          ptr->Next = Current->Next;
          delete(Current);
		  Size --;
          Current=ptr;
		}
  }
 
}



template <class ValType> 
void List <ValType> :: RemoveFromTheHead ()
{
	if (Head != NULL) 
	{
		Node <ValType> * tmp = Head -> Next;
		delete Head;
		Head = tmp;
		Size --;
	}
	else
		throw 1;
}

template <class ValType> 
void List <ValType> :: RemoveFromTheTail ()
{
	if (Size == 1)
	{
		delete Head;
		Head = NULL;
		Size --;
	}
	else if (Size > 0)
	{

		Node <ValType> * tmp = Head;
		while (tmp -> Next -> Next)
		{
			tmp = tmp -> Next;
		}
		delete tmp -> Next;
		tmp -> Next = NULL;
		Size --;
	}
	else
		throw 1;
}

template <class ValType>
void List <ValType> :: RemoveAfterPointer (Node <ValType> * ptr)
{
	if (Size == 1)
	{
		delete Head;
		Head = NULL;
		Size --;
	}
	else if (Size > 0)
	{
		Node <ValType> * tmp = ptr -> Next -> Next;
		delete ptr -> Next;
		ptr -> Next = tmp;
		Size --;
	}
	else
		throw 1;
}


template <class ValType>
void List <ValType> :: RemoveBeforePointer (Node <ValType> * ptr)
{
	if (ptr == Head) throw 1;
	else if (ptr == Head -> Next) {
		RemoveFromTheHead ();
		return;
	}
	else {
		Node <ValType> * tmp = Head; 
		if ((tmp != NULL) && (tmp -> Next != NULL))
			if (tmp -> Next -> Next == ptr) {
				delete tmp -> Next;
				tmp -> Next = ptr;
				Size --;
				return;
			}
		}
}



template <class ValType> 
Node <ValType> * List <ValType> :: SearchByKey (ValType _data)
{
	if (Size > 0)
	{
		Node <ValType> * tmp = Head;
		while (tmp != NULL)
		{
			if (tmp -> Data == _data)
				break;	
			else
				tmp = tmp -> Next;
		}
		return tmp;
	 }
	else
		throw 1;
}

template <class ValType>
istream& operator >> (istream &istr, List<ValType>& l) {
	cout << "size=";
	istr >> l.Size;
	ValType tmp;
	for (int i = 0; i < l.Size; i++) {
		istr >> tmp;
		l.InsertInTheTail(tmp);
	}
	return istr;
}

template <class ValType>
ostream& operator << (ostream &ostr, const List<ValType>& l) {
	for(Node<ValType>* plf=l.Head; plf ; plf=plf->Next)
		ostr << (plf->Data);
	ostr << endl;
	return ostr;
}


#endif








