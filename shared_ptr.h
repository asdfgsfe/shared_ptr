#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

template<typename T, typename D>
class shared_ptr
{
public:
	shared_ptr() 
		: ptr_(nullptr), count_(nullptr)
	{
	}

	explicit shared_ptr(T* ptr)
		: ptr_(ptr), count_(new int(1))
	{
	}
	
	shared_ptr(const shared_ptr& other)
	{
		if (other == *this)
		{
			return;
		}
		ptr_ = other.ptr;
		count_ = other.count_;
		++(*count_);
	}
	
	shared_ptr& operator=(const shared_ptr& ptr)
	{
		if (other == *this)
		{
			return *this;
		}

	}
private:
	T* ptr_;
	int* count_:
};


#endif //__SHARED_PTR_H__
