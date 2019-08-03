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
	//���캯��2��
	shared_ptr() 
		: ptr_(nullptr), count_(nullptr)
	{
	}

	explicit shared_ptr(T* ptr)
		: ptr_(nullptr), count_(nullptr)
	{
		acquire(ptr);
	}
	
	//�������캯��2��
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

	//��ֵ����2��
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


	//�ƶ����캯��2��
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


	//�ƶ���ֵ2��
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
	

	//��������
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

	//->�����
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



//1.���캯�������ڵĶ���û���ڴ� ����Ҫ�ͷ����ڵĶ��� 
//����ֻ��other�������ڴ� ʵ�����Ҫ�����ڵĶ�������ڴ�

//2.��ֵ���������ڵĶ����Ѿ������ڴ� ԭ���Ķ���Ҳ�Ѿ������ڴ� ����Ҫ���ͷ����ڵ��ڴ� �ڷ����µ��ڴ�
//�����쳣��ȫ ��������ͷ��ڷ���Ĺ������ý������� raii�����ڴ�

