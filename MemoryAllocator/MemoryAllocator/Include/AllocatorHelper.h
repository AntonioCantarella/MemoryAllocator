/*	
	This file is literally an helper file. It containts all the functions 
	needed to smoothly use the LinearAllocator and/or the BaseAllocator class
*/

#ifndef __ALLOCATOR_HELPER_H__
#define __ALLOCATOR_HELPER_H__

/*	
	This macro is used to to easy call the Allocate() function get back a valid
	address and then pass it to the placement new operator
*/
#define NEW(type, allocatorInstance)	new(allocatorInstance->Allocate(sizeof(type))) type 

/*	
	This macro simply call the helper template function Delete().
*/
#define DELETE(instance)	Delete(instance)

/*	
	This macro is used to call NewArray() which need the correct type, the array size(the value between this -> []),
	and of course a valid allocator instance.
	
*/
#define NEW_ARRAY(type, allocatorInstance)	NewArray<DeduceArrayTypeAndCount<type>::Type>(allocatorInstance, DeduceArrayTypeAndCount<type>::_count)

/*	
	Macro to simply call DeleteArray function.
*/
#define DELETE_ARRAY(instance, allocatorInstance) DeleteArray(instance, allocatorInstance)

/*
	Base template struct that accept a type T as template parameter
*/
template <class T>
struct DeduceArrayTypeAndCount {};

/*
	Specialized version of the above template struct that accept N
	as secundary template parameter. N will be filled by the compiler.
	So with this we will get a the compile time the info about the type of the array
	and the size.
	Example :	DeduceArrayTypeAndCount<int[7]>::Type; (Type value is int)
				DeduceArrayTypeAndCount<int[7]>::_count; (_count value is 7)
				
*/
template <class T, size_t N>
struct DeduceArrayTypeAndCount<T[N]>
{
	typedef T Type;
	static const size_t _count = N;
};

/*
	This function will simply call the instance destructor(Except for integral or POD types).
*/
template<typename T>
void Delete(T* object);

/*
	This function, by using a valid allocator instance, allow to reserve space for T[N] array.
	To get those info we go throught the DeduceArrayTypeAndCount helper template.
	This function will even store, just before array[0], the value of N itself, we do this because it will be useful for the DeleteArray().
	Example:	NewArray<int, LinearAllocator>(allocatorInstance, 5);
			->	[N = 5][int][int][int][int][int]	
*/
template<typename T, class Allocator>
T* NewArray(Allocator* allocator, size_t arraySize);

/*
	This function will emulate most compiler's behavior: 
	will get back the N value stored just before array[0].
	Than will call the instances destructor in the reverse order.
	This is why we store N in NewArray function : to be able to know how many destructor instance to call !
*/
template<typename T, class Allocator>
void DeleteArray(T* instance, Allocator* allocator);

#include "AllocatorHelper.inl";

#endif // !__ALLOCATOR_HELPER_H__