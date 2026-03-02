#ifndef LIB_LIST_LIST_H
#define LIB_LIST_LIST_H

#include <iostream>


template<class T>
struct Node {
	T _val;
	Node* _next;
	Node(const T&, Node<T>*);
};

template<class T>
Node<T>::Node(const T& val, Node<T>* next) : _val(val), _next(next) {}


template <class T>
class List
{
	Node<T>* _head, * _tail;
	size_t count = 0;
public:
	List();
	List(const List&);
	~List();

	bool is_empty();
	int find_pos(const T&);
	Node<T>* find_node(const T&);
	void pop_front();
	void push_front(const T&) noexcept;
	void pop_back();
	void push_back(const T&) noexcept;
	void erase(int);
	void insert(int, const T&);
	void erase(Node<T>* A);
	void insert(Node<T>* A, const T&);
	void clear() noexcept;
	void sort() noexcept;

	class Iterator {
		Node<T>* _current;
	public:
		Iterator();
		Iterator(Node<T>* poc);
		Iterator(const Iterator& A);

		Iterator& operator =(const Iterator& A);
		T& operator*();
		bool operator != (const Iterator& A);
		Iterator operator ++(int);
		Iterator operator ++();
	};

	Iterator begin() { return Iterator(_head); }
	Iterator end() { return Iterator(); }
	typedef Iterator iterator;
};

template<class T>
List<T>::Iterator::Iterator() : _current(nullptr) {}

template<class T>
List<T>::Iterator::Iterator(Node<T>* poc) : _current(poc) {}

template<class T>
List<T>::Iterator::Iterator(const Iterator& A) : _current(A._current) {}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator =(const Iterator& A) {
	(*this)->_current = A._current;
	return (*this);
}

template<class T>
T& List<T>::Iterator::operator*() {
	return _current->_val;
}

template<class T>
bool List<T>::Iterator::operator != (const Iterator& A) {
	return _current != A._current;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator ++(int) {
	Iterator tmp(*this);
	_current = _current->_next;
	return tmp;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator ++() {
	_current = _current->_next;
	return (*this);
}


template<class T>
List<T>::List() : _head(nullptr), _tail(nullptr), count(0) {}

template<class T>
List<T>::List(const List& A) {
	_head = nullptr;
	_tail = nullptr;
	Node<T>* tmp = A._head;
	while (tmp != nullptr) {
		push_back(tmp->_val);
		tmp = tmp->_next;
	}
}

template<class T>
List<T>::~List() { clear(); }

template<class T>
void List<T>::clear() {
	while (!is_empty()) {
		Node<T>* tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
}

template<class T>
bool List<T>::is_empty() {
	return _head == nullptr;
}

template<class T>
void List<T>::pop_front() {
	if (is_empty())
		throw std::logic_error("list is empty");
	Node<T>* tmp = _head;
	_head = _head->_next;

	if (is_empty()) {
		_tail = nullptr;
	}
	count--;
	delete tmp;
}

template<class T>
void List<T>::push_front(const T& val) noexcept {
	Node<T>* A = new Node<T>(val, _head);
	if (is_empty())
		_tail = A;
	_head = A;
	count++;
}


template<class T>
void List<T>::pop_back() {
	if (is_empty())
		throw std::logic_error("list is empty");
	Node<T>* tmp = _head;

	if (_head == _tail) {
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		while (tmp->_next != _tail)
			tmp = tmp->_next;

		_tail = tmp;
		tmp = tmp->_next;
		_tail->_next = nullptr;
	}
	count--;
	delete tmp;
}


template<class T>
void List<T>::push_back(const T& val) noexcept {
	Node<T>* A = new Node<T>(val, nullptr);
	if (is_empty())
		_head = A;

	else
		_tail->_next = A;
	_tail = A;
	count++;
}


template<class T>
void List<T>::erase(int pos) {
	Node<T>* A = _head;
	if (is_empty())
		throw std::logic_error("list is empty");

	else if (pos == 0) {
		pop_front();
	}

	else if (pos == count - 1)
		pop_back();

	else {
		while (pos != 1 && A->_next != nullptr) {
			A = A->_next;
			pos--;
		}

		if (pos == 1) {
			Node<T>* B = A->_next;
			A->_next = B->_next;
			count--;
			delete B;
		}
		else
			throw std::logic_error("overrun");
	}
}


template<class T>
void List<T>::insert(int pos, const T& val) {
	Node<T>* A = _head;
	if (pos == 0) {
		push_front(val);
	}

	else if (is_empty())
		throw std::logic_error("list is empty");

	else if (pos == count)
		push_back(val);

	else {
		while (pos != 1 && A->_next != nullptr) {
			A = A->_next;
			pos--;
		}

		if (pos == 1) {
			Node<T>* B = new Node<T>(val, A->_next);
			A->_next = B;
			count++;
		}
		else
			throw std::logic_error("element not found");
	}
}


template<class T>
void List<T>::erase(Node<T>* A) {
	if (A == nullptr)
		throw std::logic_error("A = nullptr");
	Node<T>* B = _head;

	if (is_empty())
		throw std::logic_error("list is empty");

	else if (A == _head)
		pop_front();

	else if (A == _tail)
		pop_back();

	else {
		while (B->_next != A && B->_next != nullptr)
			B = B->_next;


		if (B->_next == A) {
			B->_next = A->_next;
			count--;
			delete A;
		}
		else
			throw std::logic_error("overrun");
	}
}


template<class T>
void List<T>::insert(Node<T>* A, const T& val) {
	if (is_empty())
		throw std::logic_error("list is empty");
	if (A == nullptr)
		throw std::logic_error("A = nullptr");
	if (A == _tail)
		push_back(val);
	else {
		Node<T>* B = new Node<T>(val, A->_next);
		A->_next = B;
		count++;
	}
}

template<class T>
int List<T>::find_pos(const T& val) {
	if (is_empty())
		throw std::logic_error("list is empty");

	size_t i = 0;
	Node<T>* B = _head;
	while (B->_val != val && B->_next != nullptr) {
		B = B->_next;
		i++;
	}
	if (B->_val == val)
		return i;
	else {
		std::cout << "element not find" << std::endl;
		return -1;
	}
}

template<class T>
Node<T>* List<T>::find_node(const T& val) {
	if (is_empty())
		throw std::logic_error("list is empty");

	size_t i = 0;
	Node<T>* B = _head;
	while (B->_val != val && B->_next != nullptr) {
		B = B->_next;
		i++;
	}
	if (B->_val == val)
		return B;
	else {
		std::cout << "element not find" << std::endl;
		return nullptr;
	}
}

template<class T>
void List<T>::sort() {
	if (is_empty() || count == 1) return;

	else {
		T pivot = _tail->_val;
		List<T> right_list;
		List<T> left_list;
		for (auto it = begin(); it != --end(); it++) {

			if (*it < pivot)
				left_list.push_bask(*it);

			else
				right_list.push_back(*it);
		}

		left_list.sort();
		right_list.sort();
		clear();

		for (auto it = left_list.begin(); it != end(); it++)
			push_back(*it);

		push_back(pivot);

		for (auto it = right_list.begin(); it != end(); it++)
			push_back(*it);
	}
}
#endif // !LIB_LIST_LIST_H