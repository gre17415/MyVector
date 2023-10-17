#include <iostream>

class Array {
public:
    Array(std::ostream& ostream)
        : Ostream_(ostream)
        , size_ (0)
        , capacity_(2)
        , first (new int [2])

    {
        Ostream_ << "Constructed. ";
        Ostream_ << *this << "\n";
    }

    Array(const Array& array)
        : Ostream_(array.Ostream_)
        , size_ (array.size_)
        , capacity_ (array.capacity_)//hbjbubjb
        , first (new int [capacity_])
    {
        for(size_t i = 0; i < size_; i++)
            first[i] = array.first[i];
        Ostream_ << "Constructed from another Array. ";
        Ostream_ << (*this) << "\n";
    }
    Array(size_t size, std::ostream& ostream = std::cout, int defaultValue = 0)
        : Ostream_ (ostream)
        , size_ (size)
        , capacity_ (size * 2)
        , first (new int [capacity_])
    {
        for(size_t i = 0; i < size_; i++)
            first[i] = defaultValue;
        Ostream_ << "Constructed with default. ";
        Ostream_ << *this << "\n";
    }
    ~Array()
    {
        Ostream_ << "Destructed " << size_ << "\n";
        delete[] first;
        
    }

    size_t Size() const
    {
        return size_;
    }
    size_t Capacity() const
    {
        return capacity_;
    }
    void Reserve(size_t newCapacity)
    {
        if(newCapacity <= capacity_)
            return;
        capacity_ = newCapacity;
        int* newfirst = new int [capacity_];
        for(size_t i = 0; i < size_; i++)
           newfirst[i] = first[i];
        delete[] first;
        first = newfirst;    
    }
    void Resize(size_t newSize)
    {
        if(newSize > capacity_)
        {
            capacity_ = newSize;
            int* newfirst = new int [capacity_];
            for(size_t i = 0; i < size_; i++)
                newfirst[i] = first[i];
            delete [] first;
            first = newfirst;
        }
        size_ = newSize;

    }
    void PushBack(int value = 0)
    {
        if(size_ == capacity_)
        {
            capacity_ *= 2;
            int* newfirst = new int [capacity_];
            for(size_t i = 0; i < size_; i++)
                newfirst[i] = first[i];
            delete[] first;
            first = newfirst;
        }
        size_++;
        first[size_ - 1] = value;
    }
    void PopBack()
    {
        size_--;
    }

    const int& operator[](const size_t i) const
    {
        return const_cast <Array*> (this)->operator[](i);

    }
    int& operator[](const size_t i)
    {
        return first[i];//up?
    }
    explicit operator bool() const
    {
        return size_ != 0;
    }

    bool operator<(const Array& it) const 
    {
        size_t size_2 = it.size_;
        int* first2 = it.first;
        
        for(size_t i = 0; i < std::min(size_2, size_); i++)
        {
            if(first[i] < first2[i])
                return true;
            if(first[i] > first2[i])
                return false;
        }
        return size_ < size_2;
    }
    bool operator>(const Array& it) const
    {
        return !(*this < it);
    }
    bool operator!=(const Array& it) const
    {
        return !(it < *this && *this > it);
    }
    bool operator == (const Array& it) const
    {
        size_t size_2 = it.size_;
        int* first2 = it.first;
        if(size_2 != size_)
            return false;
        for(size_t i = 0; i < size_; i++)
        {
            if(first[i] != first2[i])
                return false;
        }
        return true;
    }
    bool operator<=(const Array& it) const
    {
        return *this < it || *this == it;
    }
    bool operator>=(const Array& it) const
    {
        return *this > it || *this == it;
    }

    Array& operator<<(const int value)
    {
        PushBack(value);
        return *this;
    }
    Array& operator<<(const Array& it)
    {
        for(size_t i = 0; i < it.size_; i++)
        {
            PushBack(it.first[i]);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& ostream, const Array& array);

private:
    std::ostream& Ostream_;
    size_t size_, capacity_;
    int* first;

    // ...
};


std::ostream& operator <<(std::ostream& ostream, const Array& array)
{
    ostream << "Result Array's capacity is " << array.capacity_ << " and size is " << array.size_;
    if(array.size_ > 0)
    {
        ostream << ", elements are: "; 
        for(size_t i = 0; i < array.size_ - 1; i++)
            ostream << array.first[i] << ", ";
    
        ostream << array.first[array.size_ - 1];
    }
    return ostream;
}
