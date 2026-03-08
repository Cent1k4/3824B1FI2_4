#include"../lib_list/list.h"

Node::Node(const std::pair<double, int>& val, Node* next) : _val(val), _next(next) {}


List::Iterator::Iterator() : _current(nullptr) {}

List::Iterator::Iterator(Node* poc) : _current(poc) {}

List::Iterator::Iterator(const Iterator& A) : _current(A._current) {}


typename List::Iterator& List::Iterator::operator =(const Iterator& A) {
	_current = A._current;
	return (*this);
}


std::pair<double, int>& List::Iterator::operator*() {
	return _current->_val;
}


bool List::Iterator::operator != (const Iterator& A) {
	return _current != A._current;
}


bool List::Iterator::operator == (const Iterator& A) {
	return _current == A._current;
}


typename List::Iterator List::Iterator::operator ++(int) {
	Iterator tmp(*this);
	_current = _current->_next;
	return tmp;
}


typename List::Iterator List::Iterator::operator ++() {
	_current = _current->_next;
	return (*this);
}

Node* List::Iterator::get_current() { return _current; }


int sum_numb(int a) {
	int sum = 0;
	while (a != 0) {
		sum += a % 10;
		a /= 10;
	}
	return sum;
}



List::List() : _head(nullptr), _tail(nullptr), count(0) {}


List::List(const List& A) {
	_head = nullptr;
	_tail = nullptr;
	Node* tmp = A._head;
	while (tmp != nullptr) {
		push_back(tmp->_val);
		tmp = tmp->_next;
	}
}


List::~List() { clear(); }


void List::clear() noexcept {
	while (!is_empty()) {
		Node* tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
}


bool List::is_empty() {
	return _head == nullptr;
}


void List::pop_front() {
	if (is_empty())
		throw std::logic_error("list is empty");
	Node* tmp = _head;
	_head = _head->_next;

	if (is_empty()) {
		_tail = nullptr;
	}
	count--;
	delete tmp;
}


void List::push_front(const std::pair<double, int>& val) noexcept {
	Node* A = new Node(val, _head);
	if (is_empty())
		_tail = A;
	_head = A;
	count++;
}


void List::pop_back() {
	if (is_empty())
		throw std::logic_error("list is empty");
	Node* tmp = _head;

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


void List::push_back(const std::pair<double, int>& val) noexcept {
	Node* A = new Node(val, nullptr);
	if (is_empty())
		_head = A;

	else
		_tail->_next = A;
	_tail = A;
	count++;
}


void List::erase(int pos) {
	Node* A = _head;
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
			Node* B = A->_next;
			A->_next = B->_next;
			count--;
			delete B;
		}
		else
			throw std::logic_error("overrun");
	}
}



void List::insert(int pos, const std::pair<double, int>& val) {
	Node* A = _head;
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
			Node* B = new Node(val, A->_next);
			A->_next = B;
			count++;
		}
		else
			throw std::logic_error("element not found");
	}
}


void List::erase(Node* A) {
	if (A == nullptr)
		throw std::logic_error("A = nullptr");
	Node* B = _head;

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


void List::insert(Node* A, const std::pair<double, int>& val) {
	if (is_empty())
		throw std::logic_error("list is empty");
	if (A == nullptr)
		throw std::logic_error("A = nullptr");
	if (A == _tail)
		push_back(val);
	else {
		Node* B = new Node(val, A->_next);
		A->_next = B;
		count++;
	}
}



int List::find_pos(const std::pair<double, int>& val) {
	if (is_empty())
		throw std::logic_error("list is empty");

	size_t i = 0;
	Node* B = _head;
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


Node* List::find_node(const std::pair<double, int>& val) {
	if (is_empty())
		throw std::logic_error("list is empty");

	size_t i = 0;
	Node* B = _head;
	while (B->_val.second != val.second && B->_next != nullptr) {
		B = B->_next;
		i++;
	}
	if (B->_val.second == val.second)
		return B;
	else {
		std::cout << "element not find" << std::endl;
		return nullptr;
	}
}


void List::sort() noexcept {
	if (is_empty() || count == 1) return;

	else {
		std::pair<double, int> pivot = _tail->_val;
		List right_list;
		List left_list;

		Node* current = _head;
		while (current != _tail) {
			if (sum_numb(current->_val.second) >= sum_numb(pivot.second))
				left_list.push_back(current->_val);
			else
				right_list.push_back(current->_val);
			current = current->_next;
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

List& List::operator = (const List& A) {
	clear();
	for (auto it = A.begin(); it != A.end(); it++) 
		push_back(*it);
	return (*this);
}