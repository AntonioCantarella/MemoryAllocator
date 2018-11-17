template<typename T>
void Delete(T* object)
{
	object->~T();
}

template<typename T, class Allocator>
T* NewArray(Allocator* allocator, size_t arraySize)
{
	void* array_size_memory_block = allocator->Allocate((sizeof(T) * arraySize) + sizeof(size_t));

	size_t* start_offset = static_cast<size_t*>(array_size_memory_block);
	*start_offset = arraySize;
	start_offset++;

	T* start = static_cast<T*>(static_cast<void*>(start_offset));
	T* end = start + arraySize;
	while (start < end)
	{
		new (start) T;
		++start;
	}

	return (start - arraySize);
}

template<typename T, class Allocator>
void DeleteArray(T* instance, Allocator* allocator)
{
	size_t array_count = *(static_cast<size_t*>(static_cast<void*>(instance)) - 1);

	for (size_t i = array_count; i > 0; --i)
		instance[i - 1].~T();

	// call allocator->Deallocate((sizeof(T) * array_count) + sizeof(size_t))
}