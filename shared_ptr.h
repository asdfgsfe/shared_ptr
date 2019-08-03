#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

#include <assert.h>
#include <iostream>
#include <new>

namespace Memory
{
template<typename T>
class shared_ptr
{
	template<class Y> friend class shared_ptr;
public:
	//构造函数2个
	shared_ptr() 
		: ptr_(nullptr), count_(nullptr)
	{
	}

	explicit shared_ptr(T* ptr)
		: ptr_(nullptr), count_(nullptr)
	{
		acquire(ptr);
	}
	
	//拷贝构造函数2个
	shared_ptr(const shared_ptr& other)
		: count_(other.count_)
	{
		assert(!other.ptr_ || 0 != *(other.count_));
		acquire(other.ptr_);
	}
	
	template<typename Y>
	shared_ptr(const shared_ptr<Y>& other)
		: count_(other.count_)
	{
			assert(other.ptr == nullptr || *(other.count_) != 0);
			acquire(static_cast<T*>(other.ptr_));
	}

	//赋值操作2个
	shared_ptr& operator=(shared_ptr other)
	{
        std::swap(count_, other.count_);
		std::swap(ptr_, other.ptr_);
        return *this;
	}

	template<typename Y>
	shared_ptr& operator=(shared_ptr<Y> other)
	{
		std::swap(count_, other.count_);
		std::swap(ptr_, static_cast<T*>(other.ptr));
    return *this;
	}


	//移动构造函数2个
	shared_ptr(shared_ptr&& other)
	{
		assert(!other.ptr_ || 0 != *other.count_);
		ptr_ = other.ptr_;
		count_ = other.count_;
		other.ptr_ = nullptr;
		other.count_ = nullptr;
	}
	template <class Y> 
	shared_ptr(shared_ptr<Y>&& other)
		: count_(other.count_)
	{
		assert(!other.ptr_ || 0 != *other.count_);
		ptr_ = static_cast<T*>(other.ptr_);
		other.ptr_ = nullptr;
		other.count_ = nullptr;
	}


	//移动赋值2个
	shared_ptr& operator=(shared_ptr&& other)
	{
		--*(count_);
		if (0 == *count_)
		{
			delete ptr_;
			delete count_;
		}
		ptr_ = other.ptr_;
		count_= other.count_;
		other.ptr_ = nullptr;
		other.count_ = nullptr;
    return *this;
	}
	template< class Y > 
	shared_ptr& operator=(shared_ptr<Y>&& other)
	{
		--*(count_);
		if (0 == *count_)
		{
			delete ptr_;
			delete count_;
		}
		ptr_ = static_cast<T*>(other.ptr_);
		count_= other.count_;
		other.ptr_ = nullptr;
		other.count_ = nullptr;
    return *this;
	}
	

	//析构函数
	~shared_ptr()
	{
		if (!ptr_ || !count_)
		{
			return;
		}
		--(*count_);
		if (*count_ == 0)
		{
			delete ptr_;
			delete count_;
		}
	}

	//->运算符
	T* operator->() const
    {
        assert(ptr_);
        return ptr_;
    }

	T operator*() const
	{
		assert(ptr_);
		return *ptr_;
	}

	int use_count() const
	{
		assert(count_);
		return *count_;
	}
private:
	template<typename U>
	void acquire(U* p)
    {
		if (!p)
		{
			return;
		}
		if (!count_)
		{
			count_ = new int(0);
		}
		++(*count_);
		ptr_ = p;
    }
private:
	T* ptr_;
	int* count_;
};
} //namespace Memory

#endif //__SHARED_PTR_H__



//1.构造函数是现在的对象还没有内存 不需要释放现在的对象 
//仅仅只有other对象有内存 实现深拷贝要给现在的对象分配内存

//2.赋值操纵是现在的对象已经有了内存 原来的对象也已经有了内存 所以要线释放现在的内存 在分配新的内存
//考虑异常安全 所以这个释放在分配的过长采用交换操作 raii管理内存

