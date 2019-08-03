#include "shared_ptr.h"

class Test
{
public:
	Test()
	{
		std::cout << "Test()" << std::endl;
	}
	
	Test(const Test& other)
	{
		std::cout << "Test(const Test& other)" << std::endl;
	}
	
	Test& operator=(const Test other)
	{
		std::cout << "Test& operator=(const Test other)" << std::endl;
	}
	
	Test(Test&& other)
	{
		std::cout << "Test(Test&& other)" << std::endl;
	}

	Test& operator=(Test&& other)
	{
		std::cout << "Test& operator=(Test&& other)" << std::endl;
	}

	~Test()
	{
		std::cout << "~Test()" << std::endl;
	}
};

int main(void)
{
	Test* t = new Test;
	Memory::shared_ptr<Test> tPtr(new Test);
	std::cout << "c1=" << tPtr.use_count() << std::endl; //1

	Memory::shared_ptr<Test> tPtr2(tPtr);
	std::cout << "c2=" << tPtr.use_count() << std::endl; //2

	Memory::shared_ptr<Test> tPtr3;
	tPtr3 = tPtr2;
	std::cout << "c3=" << tPtr.use_count() << std::endl; //3

	Memory::shared_ptr<Test> tPtr4(std::move(tPtr3));
	std::cout << "c4=" << tPtr.use_count() << std::endl; //3

	return 0;
}
