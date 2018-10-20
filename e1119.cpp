#include "pch.h"
#include <iostream>
#include <vector>

// design and implement a counted_ptr<T>: a type that
// holds a pointer to an object of type T and a pointer to a "user count" (an
// int) shared by all pointers to the same object of type T, holding the number
// of counted pointers pointing to a given T. The constructor should allocate a
// T and a use count on the heap and take an argument as initial value for the T
// elements. When the last counted_ptr for a T is destroyed, the destructor
// should delete the T.
// counted_ptr should have operations that allow us to use it as a pointer.
// Write a set of test cases.

template<typename T> class counted_ptr {
public:
	T* ptr;     // the wrapped pointer
	int* user_count;   // reference counter
public:
	counted_ptr(const T& argx);                  // constructor
	counted_ptr(const counted_ptr&);            // copy constructor
	counted_ptr& operator=(const counted_ptr&); // copy assignment

	~counted_ptr();

	T operator*() const { return *ptr; } // dereference op
	T* operator->() const { return ptr; } //object is a pointer

	int count() const { return *user_count; }
};

struct Status {
	Status() : val(0) {} // constructor
	Status(int n) : val(n) {} // val constructor
	Status(const Status& t) : val(t.val) { std::cout << "Calling copy constructor " << std::endl; } //copy constructor
	Status& operator=(const Status& t)
	{
		val = t.val;
		std::cout << "Calling copy assignment " << std::endl;
		return *this;
	}
	~Status() { std::cout << "Calling destructor " << std::endl; }
	int val;
};

template<typename T> counted_ptr<T>::counted_ptr(const T& argx) // constructor
{
	ptr = new T(argx);
	user_count = new int(1);
}


template<typename T> counted_ptr<T>::counted_ptr(const counted_ptr& argx)  //copy constr.
{
	ptr = argx.ptr;
	user_count = argx.user_count;
	++(*user_count);
}



template<typename T> counted_ptr<T>& counted_ptr<T>::operator=(const counted_ptr& argx) //copy assignemtn
{
	if (&argx == this) 
	{
		return *this;
	}
	--(*user_count);
	if ((*user_count) == 0) 
	{
		delete ptr;
		delete user_count;
	}
	ptr = argx.ptr;
	user_count = argx.user_count;
	++(*user_count);       
	return *this;
}

template<typename T> counted_ptr<T>::~counted_ptr()
{
	--(*user_count);
	if (*user_count == 0) {
		std::cout << " Destroying counted_pointer" << std::endl;
		delete ptr;
		delete user_count;
	}
}


void test_case2(const counted_ptr<int> & cp1)
{
	counted_ptr< int> cptr_2(cp1);
	std::cout << "*cptr_2.ptr, pointed value: " << *cptr_2.ptr << std::endl;
	std::cout << "cp2.count(): " << cptr_2.count() << std::endl;
	std::cout << "cp2.count(): " << cptr_2.count() << std::endl;
}
void test_case1()
{
	int t = 10;
	counted_ptr<int> cptr_1(t);
	std::cout << "*cp1.ptr, pointed value: " << *cptr_1 << std::endl;
	std::cout << "cp2.count(): " << cptr_1.count() << std::endl;
	test_case2(cptr_1);
	std::cout << "cp2.count(): " << cptr_1.count() << std::endl;
}
int main()
{
	
	try {
		test_case1();
		counted_ptr<int> cptr_xx(1);
		std::cout << &cptr_xx;
		//check for auto-destr on scope end
		std::cout << "\n scope now " << std::endl;
		{
			counted_ptr<int> cptr_3(1);
			std::cout << "&cptr_2: " << &cptr_xx;
		}
		std::cout<<  "&cptr_2: " << &cptr_xx;
		std::cout << "\n eof scope " << std::endl;
		test_case2(cptr_xx);

		counted_ptr<Status> cptr_1(Status(999));
		counted_ptr<Status> cptr_2(cptr_1);
		counted_ptr<Status> cptr_3(Status(333));
		counted_ptr<Status> cptr_4(cptr_3);
		std::cout << "cp1.count(): " << cptr_1.count() << std::endl;
		std::cout << "cp3.count(): " << cptr_3.count() << std::endl;
		cptr_3 = cptr_1;
		std::cout << "cp1.count(): " << cptr_1.count() << std::endl;



	}
catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
	std::cerr << "exception\n" << std::endl;
}
}
