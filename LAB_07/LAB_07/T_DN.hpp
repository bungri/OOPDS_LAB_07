/** T_DN.hpp */

/* T_DN means Template Double Node. */

#ifndef T_DN_H
#define T_DN_H

template<typename E>
class T_DN
{
public:
	T_DN() { prev = next = NULL; }; // default constructor
	T_DN(E e) { elm = e; prev = next = NULL; };
	~T_DN() {};
	const E& getElem() const { return elm; }
	void setElem(const E e) { elm = e; }
	T_DN *getPrev() { return prev; }
	T_DN *getNext() { return next; }
	void setPrev(T_DN *p) { this->prev = p; }
	void setNext(T_DN *n) { this->next = n; }
private:
	E elm;
	T_DN *prev;
	T_DN *next;
};

#endif