template <typename T>
class SharedPtr {
public:
  SharedPtr();
  SharedPtr(const SharedPtr&);
  SharedPtr& opeartor=(const SharedPtr&);
  SharedPtr(const SharedPtr&);
  
  void reset();
  void reset(T*);
  void swap(SharedPtr&);
  T* get();
  T& operator*() const;
  T* operator->() const;
  // возвращает количество объектов shared_ptr, которые ссылаются на тот же управляемый объект
  size_t use_count() const;
  // проверяет, указывает ли указатель на объект
  operator bool() const;
};
