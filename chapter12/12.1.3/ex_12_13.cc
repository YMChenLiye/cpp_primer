
#include <iostream>
#include <memory>

int main()
{

	auto sp = std::make_shared<int>();
	auto p = sp.get();
	delete p;

//double free
	return 0;
}
