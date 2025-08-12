
#include<thread>
#include<mutex>
#include<string>
#include<algorithm>
#include<string_view>
#include<iostream>

class string_mutator {
	std::string text;
	mutable std::mutex m;
public:
	//note: m in uncopiable to string_mutator
	//also is uncopiable
	string_mutator(std::string_view src) :text{ src.begin(),src.end() } {}

	template<class F> void operator()(F f) {
		std::lock_guard lck{ m };
		std::transform(text.begin(), text.end(), text.begin(), f);
		
	}
	std::string grab_snapshot() const {
		std::lock_guard lck{ m };
			
		return text;
	}
};
int main()
{
	string_mutator sm{ " I love my instructor" };
	sm([](char c) {
		return static_cast<char>(std::toupper(c));
		});
	std::cout << sm.grab_snapshot();

	return 0;
}
