#include <iostream>
#include <exception>
#include <atomic>

// Counter class
class Counter
{
private:
    std::atomic_uint count;
    
public:
    ~Counter() = default;
    Counter& AddRef()
    {
        count++;
        return *this;
    }
    
    Counter& Release()
    {
        count--;
        return *this;
    }
    size_t getCount()
    {
        return count;
    }
};

// shared_ptr
template <typename T>
class SharedPtr
{
private:
    T* pData;
    Counter* reference;
public:
    
    SharedPtr() : pData(nullptr)
    {
        reference = new Counter;
    }
    
    SharedPtr(T* data)
    {
        pData = new T(*data);
        reference = new Counter;
        reference->AddRef();
    }
    ~SharedPtr()
    {
        reset();
    }
    
    SharedPtr(const SharedPtr& a) : pData(a.pData), reference(a.reference)
    {
        if (reference != nullptr)
        {
            reference->AddRef();
        }
    }
    SharedPtr<T>& operator=(const SharedPtr& a)
    {
        SharedPtr(a).swap(*this);
        return *this;
    }
    
    void reset()
    {
        if (reference != nullptr)
        {
            reference->Release();
        }
        if (reference->getCount() == 0)
        {
            if (pData != nullptr)
            {
                delete pData;
            }
            delete reference;
        }
        reference = nullptr;
        pData = nullptr;
    }
    void reset(T* b)
    {
        if (reference != nullptr)
        {
            reference->Release();
        }
        if (reference->getCount() == 0)
        {
            if (pData != nullptr)
            {
                delete pData;
            }
            delete reference;
        }
        reference = new Counter;;
        reference->AddRef();
        pData = b;
    }
    void swap(SharedPtr& a)
    {
        if (pData != a.pData)
        {
            std::swap(pData, a.pData);
            std::swap(reference, a.reference);
        }
    }
    T* get()
    {
        if (pData == nullptr)
        {
            throw std::invalid_argument("Received null pointer");
        }
        return pData;
    }
    T& operator*() const
    {
        if (pData == nullptr)
        {
            throw std::invalid_argument("Received null pointer");
        }
        return *pData;
    }
    T* operator->() const
    {
        if (pData == nullptr)
        {
            throw std::invalid_argument("Received null pointer");
        }
        return pData;
    }
    // возвращает количество объектов shared_ptr, которые ссылаются на тот же управляемый объект
    size_t use_count() const
    
    {
        return reference->getCount();
    }
    // проверяет, указывает ли указатель на объект
    operator bool() const
    {
        return pData != nullptr;
    }
};
