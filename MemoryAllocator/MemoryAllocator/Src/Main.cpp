#include <iostream>
#include "LinearAllocator.h"

int main()
{
	LinearAllocator* allocator = new LinearAllocator(256);

	int* i = NEW(int, allocator);
	*i = 5213;

	long int* li= NEW(long int , allocator);
	*li = 2893;

	long long int* lli = NEW(long long int, allocator);
	*lli = 13423;

	int* array_int = NEW_ARRAY(int[4], allocator);
	array_int[0] = 10;
	array_int[1] = 11;
	array_int[2] = 12;
	array_int[3] = 13;

	std::cout << "*i = " << *i << std::endl;
	std::cout << "i = " << i << std::endl;
	std::cout << "*li = " << *li << std::endl;
	std::cout << "li = " << li << std::endl;
	std::cout << "*lli = " << *lli << std::endl;
	std::cout << "lli = " << lli << std::endl;
	for(int idx = 0; idx < 4; ++idx)
		std::cout << "array_int[idx] = " << array_int[idx] << std::endl;
	//std::cout << "allocator->GetUsedMemory() = " << allocator->GetUsedMemory() << std::endl;

	DELETE(i);
	DELETE(li);
	DELETE(lli);
	DELETE_ARRAY(array_int, allocator);

	i = nullptr;
	li = nullptr;
	lli = nullptr;
	array_int = nullptr;
	
	
	std::cin.get();

	allocator->Reset();
	delete allocator;
	allocator = nullptr;

	return EXIT_SUCCESS;
}