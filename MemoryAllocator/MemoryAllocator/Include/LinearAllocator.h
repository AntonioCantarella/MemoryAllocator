#ifndef __LINEAR_ALLOCATOR_H__
#define __LINEAR_ALLOCATOR_H__

#include <stdint.h>
#include "AllocatorHelper.h"

/*
	This class create a buffer of size_t size(specified at the construction) and than manage this buffer using
	_start, _end and _current pointers. 
	Each call to Allocate() will move the _current pointer and get back first address of free memory.
	This will guarantees blazing fast allocation without the need of the extra overhead from the use of new() operator.
	Complexity O(1).
*/
class LinearAllocator
{
public:
	/*
		Construct the class with a size_t size buffer. Once created the buffer will maintain
		its size during the entire lifetime of the class.
	*/
	explicit LinearAllocator(size_t size);

	/*
		Delete the buffer and invalidate all the pointers.
	*/
	~LinearAllocator();
	
	/*
		Return the memory used in the buffer.
	*/
	size_t GetUsedMemory() const { return _usedMemory; }

	/*
		Return the _current address, while moving _current of size value position.
	*/
	void*		Allocate(const size_t size);
	
	/*
		Move _current to _start position and let overwrite all previous values
	*/
	void		Reset();

private:
	uint8_t* _start;
	uint8_t* _end;
	uint8_t* _current;

	size_t _usedMemory;
};

#endif // !__LINEAR_ALLOCATOR_H__