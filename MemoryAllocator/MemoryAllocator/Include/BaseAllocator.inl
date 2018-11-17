template<class AllocatorPolicy>
void* BaseAllocator<AllocatorPolicy>::Allocate(const size_t size)
{
	return _allocator.Allocate(size);
}

template<class AllocatorPolicy>
void BaseAllocator<AllocatorPolicy>::Reset()
{
	_allocator.Reset();
}