

class invalid_pointer {};
class invalid {};
template<class T>
class non_null_ptr {
	T* p;
public:
	non_null_ptr(T* p) :p{ p } {
		if (!p) throw invalid_pointer{};
	}
	T* get() const { return p; }
	constexpr operator bool() const noexcept {
		return true;
	}
};

struct X { int n; };
int extract_value(const non_null_ptr<X>& p) {
	return p->n; // no need for validation as it stems from the type system itself
}

#include<iostream>
int main()   {
try {
	X x{ 3 };
	std::cout << extract_value(&x) << '\n'
		<< extract_value(nullptr) << '\n';

}
catch (...) {
	std::cerr << "oops\n";
}
return 0;
}
