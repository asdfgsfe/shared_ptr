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
    }

    shared_ptr(shared_ptr&& other)
    {
        ptr_ = other.ptr_;
        count_ = other.count_;
        ++(*count_);
        if (--*(other.count_) == 0)
        {
            delete other_ptr_;
            other.ptr_ = nullptr;
            delete other.count_;
            other.count_  = nullptr;
        }
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        --(*count_);
        if (*count_ == 0)
        {
            delete ptr_;
            delete count_;
        }
        ptr_ = other.ptr_;
        count_ = other.count_;
        ++(*count_);
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other)
    {
        --(*count_);
        if (*count_ == 0)
        {
            delete ptr_;
            delete count_;
        }
        ptr_ = other.ptr_;
        count_ = other.ptr_;
        if (--*other.count_ == 0)
        {
            delete other.ptr_;
            other.ptr_ = nullptr;
            delete other.count_;
            other.count_ = nullptr;
        }
        return *this;
    }
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
    atomic<int>* count_;
};
