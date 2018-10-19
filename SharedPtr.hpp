#include <iostream>
#include <exception>
#include <atomic>

// Counter class
class Counter
{
private:
    std::atomic_uint count;
    
public:
    void AddRef()
    {
        count++;
    }
    
    int Release()
    {
        return --count;
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
        if (reference->Release() == 0)
        {
            if (pData != nullptr)
            {
                delete pData;
                pData = nullptr;
            }
            delete reference;
        }
        reference = nullptr;
    }
    SharedPtr(const SharedPtr& a) : pData(a.pData), reference(a.reference)
    {
        reference->AddRef();
    }
    SharedPtr<T>& operator=(const SharedPtr& a)
    {
        if (this != &a)
        {
            if (reference->Release() == 0)
            {
                if (pData != nullptr)
                {
                    delete pData;
                }
                delete reference;
            }
            pData = a.pData;
            reference = a.reference;
            reference->AddRef();
        }
        return *this;
    }
    
    void reset()
    {
        if (reference->Release() == 0)
        {
            if (pData != nullptr)
            {
                delete pData;
                pData = nullptr;
            }
            delete reference;
        }
        else
        {
            pData = nullptr;
        }
        reference = nullptr;
        
    }
    void reset(T* b)
    {
        if (reference->Release() == 0)
        {
            if (pData != nullptr)
            {
                 delete pData;
            }
            delete reference;
        }
        pData = b;
        reference = new Counter;
        reference->AddRef();
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
        return pData != nullptr ? true : false;
    }
};

