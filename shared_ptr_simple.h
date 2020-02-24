class shared_ptr
{
    shared_ptr()
        : ptr_(nullptr), count_(nullptr)
    {}

    explicit shared_pt(int* p)
        : ptr_(p), count_(new int(1))
    {}

    shared_ptr(const shared_ptr& other)
    {
        ptr_ = other.ptr_;
        count_ = cother.count_;
        ++(*count_);
        //fix 
        //count_ = __sync_add_and_fetch(other.count_, 1);
    }

    shared_ptr(shared_ptr&& other)
    {
        ptr_ = other.ptr_;
        //貌似有错误 移动构造为什么要++count_
        count_ = other.count_;
        ++(*count_);
        if (--*(other.count_) == 0)
        {
            delete other_ptr_;
            other.ptr_ = nullptr;
            delete other.count_;
            other.count_  = nullptr;
        }
        //正确的移动操作
        ptr_ = other.ptr_;
        count_ = __sync_fetch_and_add(other.count_, 0);
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        //应该直接调用析构函数 当前的析构函数
        ~shared_ptr();
        //--(*count_);
        //if (*count_ == 0)
        //{
            //delete ptr_;
            //delete count_;
        //}
        ptr_ = other.ptr_;
        //count_ = other.count_;
        //++(*count_);
        count_ = __sync_add_and_fetch(other.count_, 1);
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other)
    {
        //--(*count_);
        //if (*count_ == 0)
        //{
        //    delete ptr_;
        //    delete count_;
        //}
        //改为直接调用析构函数
        ~shared_ptr();
        ptr_ = other.ptr_;
        count_ = __sync_fetch_add_add(other.count_, 0);
        //count_ = other.ptr_;
        //if (--*other.count_ == 0)
        //{
            //delete other.ptr_;
            //other.ptr_ = nullptr;
            //delete other.count_;
            //other.count_ = nullptr;
        //}
        return *this;
    }
    ~shared_ptr()
    {
        if (!ptr_ || !count_)
        {
            return;
        }
        //--(*count_);
        *count_ = __sync_sub_and_fetch(count_, 1);
        //原子比较
        if (__sync_fetch_and_add(count_, 0) == 0)
        {
            delete ptr_;
            ptr_ = nullptr;
            delete count_;
            count_ = nullptr;
        }
    }

    int* opertor->() const
    {
        return ptr_;
    }

private:
    int* ptr_;
    int* count_;
};
