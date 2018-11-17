#ifndef __BASE_ALLOCATOR_H__
#define __BASE_ALLOCATOR_H__

/*
	Interface class to allocators classes.
	Instead of dynamic polymorphism, it is preferable to use template and static polymorphism 
	because the latter is type safe, compile time resolved and so doesn't add overhead at run-time.
	To achieve static polymorphism, the policy based dispatch was chosen.
	Example :	int main()
				{
					typedef BaseAllocator<LinearAllocator(or any other allocator)> MyAllocator;
					MyAllocator* allocator = new Myallocator(128);
					....
					....	allocation operations
					....
				}
*/
template <class AllocatorPolicy>
class BaseAllocator
{
public:

	/*
		Call constructor passing the buffer size as parameter
	*/
	explicit BaseAllocator(const size_t size) : _allocator(size) {}

	/*
		Call to Allocate implementation function.
	*/
	void*		Allocate(const size_t size);

	/*
		Call to Reset implementation function.
	*/
	void		Reset();

private:
	AllocatorPolicy _allocator;
};

#include "BaseAllocator.inl";

#endif // !__BASE_ALLOCATOR_H__
