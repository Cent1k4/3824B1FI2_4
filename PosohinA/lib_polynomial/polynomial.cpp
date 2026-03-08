#include"../lib_polynomial/polynomial.h"


int entering_degree(const char a) {
	int deg;
	while (true) {
		std::cout << "degree l" << a <<  " = ";
		std::cin >> deg;
		if (0 <= deg && deg <= 9)
			break;
		else
			std::cout << "Erorr\n";
	}
	return deg;
}

bool chek_deg(int A, int B) {
	while (A != 0) {
		if (A % 10 < B % 10)
			return false;
		A /= 10;
		B /= 10;
	}
	return true;
}


Polynomial::Polynomial() : view() {}

Polynomial::Polynomial(const List A) : view(A) {}

Polynomial::~Polynomial() { view.clear(); }

void Polynomial::record() {
	std::cout <<"enter the monomials step by step. General view of the monome K * x^l1 * y^l2 * z^l3\nl1,l2,l3 - (0 - 9), k - the real coefficient" << "To stop typing, write K = 0" << std::endl;
	int i = 1;
	double rat;
	int l1, l2, l3, degree;

	while (true) {
		std::cout << "Enter" << i++ << "monom" << std::endl;
		std::cout << "Ratio K = \n";
		std::cin >> rat;

		if (rat == 0)
			break;

		l1 = entering_degree('1');
		l2 = entering_degree('2');
		l3 = entering_degree('3');
		degree = 100 * l1 + 10 * l2 + l3;

		std::pair<double, int> monome = { rat, degree };

		if (view.is_empty()) {
			view.push_back(monome);
			continue;
		}

		for (auto it = view.begin(); it != view.end(); it++) {

			if (it.get_current()->_next == nullptr) {
				view.push_back(monome);
				break;
			}

			else if (monome.second == (*it).second) {
				(*it).first = (*it).first + monome.first;
				break;
			}

			else if (monome.second > (*it).second && monome.second < it.get_current()->_val.second) {
				view.insert(it.get_current(), monome);
				break;
			}
		}
		std::cout << "monom is recorded" << std::endl;
	} 
}


Polynomial Polynomial::operator + (const Polynomial& A) const {
	Polynomial new_Polynomial;
	auto it1 = view.begin();
	auto it2 = A.view.begin();

	while (it1 != view.end() || it2 != view.end()){
		if ((*it1).second == (*it2).second) {
			double sum = (*it1).first + (*it2).first;
			if (sum != 0.0) {
				std::pair<double, int> monome = { sum, (*it1).second };
				new_Polynomial.view.push_back(monome);
			}
			++it1;
			++it2;
		}

		else if ((*it1).second > (*it2).second) {
			new_Polynomial.view.push_back(*it1);
			it1++;
		}

		else if ((*it1).second < (*it2).second) {
			new_Polynomial.view.push_back(*it2);
			it2++;
		}
	}

	for(it1; it1 != view.end(); it1++)
		new_Polynomial.view.push_back((*it1));

	for (it2; it2 != view.end(); it2++)
		new_Polynomial.view.push_back((*it2));

	return new_Polynomial;
}

Polynomial Polynomial::operator - (const Polynomial& A) const {
	Polynomial new_Polynomial;
	new_Polynomial = (*this) + (A * (-1.0));
	return new_Polynomial;
}

Polynomial& Polynomial::operator = (const Polynomial& A) {
	view = A.view;
	return (*this);
}

Polynomial Polynomial::operator * (double A) const {
	Polynomial new_Polynomial;
	new_Polynomial.view.push_back(std::pair<double, int>(A, 0));
	return (*this) * new_Polynomial;
}

Polynomial Polynomial::operator * (const Polynomial& A) const {
	Polynomial new_Polynomial;
	int deg;
	auto it1 = view.begin();
	auto it2 = A.view.begin();

	for (it1; it1 != view.end(); it1++) {
		for (it2; it2 != view.end(); it2++) {
			deg = (*it1).second + (*it2).second;

			if (chek_deg(deg, (*it1).second) && chek_deg(deg, (*it2).second))
				new_Polynomial.view.push_back(std::pair<double, int>(((*it1).first * (*it2).first), deg));

			else
				throw std::logic_error("overflou");
		}
	}
	return new_Polynomial;
}

const Polynomial operator * (double val, const Polynomial& A) {
	return A * val;
}