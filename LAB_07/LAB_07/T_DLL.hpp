/** T_DLL.hpp */

/* T_DLL means Template Double Linked List. */

#ifndef T_DLL_HPP
#define T_DLL_HPP

//#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "T_DN.hpp"

using namespace std;

template<typename E>
class T_DLL
{
public:
	T_DLL();
	~T_DLL();
	bool empty();
	const E& getFront() const;
	const E& getBack() const;
	void addFront(const E& e);
	void addBack(const E& e);
	void removeFront();
	void removeBack();
	void printDLL(ostream& fout, int elem_per_line);
	int getNumEntry();
protected:
	void add(T_DN<E> *v, const E& e);
	void remove(T_DN<E> *v);
private:
	CRITICAL_SECTION cs_dll;
	int num_entry;
	T_DN<E>* header;
	T_DN<E>* trailer;
};

template<typename E>
T_DLL<E>::T_DLL()
{
	header = new T_DN<E>();
	trailer = new T_DN<E>();
	header->setNext(trailer);
	trailer->setPrev(header);
	num_entry = 0;
}

template<typename E>
T_DLL<E>::~T_DLL()
{
	cout << "Deleting all nodes in T_DLL" << endl;
	while (!empty())
		removeFront();
	delete header;
	delete trailer;
}

template<typename E>
bool T_DLL<E>::empty()
{
	return(num_entry == 0);
}

template<typename E>
int T_DLL<E>::getNumEntry()
{
	return num_entry;
}

template<typename E>
const E& T_DLL<E>::getFront() const
{
	return ((header->getNext())->getElem());
}

template<typename E>
const E& T_DLL<E>::getBack() const
{
	return ((trailer->getPrev())->getElem());
}

template<typename E>
void T_DLL<E>::add(T_DN<E> *v, const E& e)
{
	EnterCriticalSection(&cs_dll)
	T_DN<E>* u = new T_DN<E>();
	u->setElem(e);
	u->setNext(v);
	u->setPrev(v->getPrev());
	(v->getPrev())->setNext(u);
	v->setPrev(u);
	this->num_entry++;
	LeaveCriticalSection(&cs_dll);
}

template<typename E>
void T_DLL<E>::addFront(const E& e)
{
	add(header->getNext(), e);
}

template<typename E>
void T_DLL<E>::addBack(const E& e)
{
	add(trailer, e);
}

template<typename E>
void T_DLL<E>::remove(T_DN<E> *v)
{
	EnterCriticalSection(&cs_dll)
	T_DN<E>* u = v->getPrev();
	T_DN<E>* w = v->getNext();
	u->setNext(w);
	w->setPrev(u);
	delete v;
	this->num_entry--;
	LeaveCriticalSection(&cs_dll);
}

template<typename E>
void T_DLL<E>::removeFront()
{
	remove(header->getNext());
}

template<typename E>
void T_DLL<E>::removeBack()
{
	remove(trailer->getPrev());
}

template<typename E>
void T_DLL<E>::printDLL(ostream& fout, int elem_per_line)
{
	T_DN<E> * u;
	int count = 0;
	u = header->getNext();
	while (u != trailer)
	{
		fout << u->getElem() << " ";
		u = u->getNext();
		count++;
		if ((count % elem_per_line) == 0)
			printf("\n");
	}
	fout << endl;
}
#endif