#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(size_t size)
{
	_start = new uint8_t[sizeof(uint8_t) * size];
	_end = _start + (sizeof(uint8_t) * size);
	_current = _start;
	_usedMemory = 0;
}

LinearAllocator::~LinearAllocator()
{
	delete[] _start;
	_start = nullptr;
	_end = nullptr;
	_current = nullptr;

	_usedMemory = 0;
}

void* LinearAllocator::Allocate(const size_t size)
{
	void* user_ptr = static_cast<void*>(_current);
	_current += size;
	_usedMemory += size;

	if (_current > _end)
		return nullptr;

	if (_current + size > _end)
		return nullptr;

	return user_ptr;
}

void  LinearAllocator::Reset()
{
	_current = _start;
	_usedMemory = 0;
}