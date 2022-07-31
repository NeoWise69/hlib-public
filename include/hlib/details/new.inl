void* operator new(size_t, hlib::placeholder, void* ptr)
{
	return ptr;
}

void operator delete(void*, hlib::placeholder, void* ptr) HLIB_THROW()
{}
