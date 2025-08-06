#include<iostream>
#include<cassert>
#include<type_traits>


bool same_bytes(const char* p0, const char* p1, std::size_t n) {
	for (std::size_t i = 0; i < n; ++i) {
		if (*(p0 + i) != *(p1 + i))
			return false;
	}
	return true;
}

template<class T, class U>
bool same_bytes(const T& a, const U& b) {
	static_assert(sizeof a == sizeof b);
	static_assert(std::has_unique_object_representations_v<T>);
	static_assert(std::has_unique_object_representations_v<U>);
	return same_bytes(reinterpret_cast<const char*>(&a), reinterpret_cast<const char*>(&b), sizeof a);
}

struct X {
	int x{ 2 }, y{ 3 };
	//char a='c';
	//float b{ 3.5 };
};
struct Y {
	int x{ 2 }, y{ 3 };
	//int8_t l{ 1 };
};

int main()
{
	constexpr X x;
	constexpr Y y;
	assert(same_bytes(x, y));
	return 0;
}
