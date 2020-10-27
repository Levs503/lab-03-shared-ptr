//
// Created by Лев on 12.10.2020.
//

#ifndef TEMPLATE_SHAREDPTR_H
#define TEMPLATE_SHAREDPTR_H
#include <atomic>
#include <cstddef>
#include <map>

template <typename T>
class SharedPtr {
 public:
  SharedPtr();
  SharedPtr(T* ptr);
  SharedPtr(const SharedPtr& r);
  SharedPtr(SharedPtr&& r);
  ~SharedPtr();
  auto operator=(const SharedPtr& r) -> SharedPtr&;
  auto operator=(SharedPtr&& r) -> SharedPtr&;

  // проверяет, указывает ли указатель на объект
  operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPtr& r);
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  auto use_count() const -> size_t;

 private:
  T* object;
  std::atomic_size_t* counter;
};

template <class T>
SharedPtr<T>::SharedPtr() : object(nullptr), counter(new std::atomic_size_t) {}
template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) : object(ptr), counter(new std::atomic_size_t) {
  *counter = 1;
}
template <typename T>
auto SharedPtr<T>::get() -> T* {
  return object;
}
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& r) {
  object = r.object;
  counter = r.counter;
  if (counter) (*counter)++;
}
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& r) {
  object = r.object;
  r.object = nullptr;
  counter = r.counter;
  r.counter = nullptr;
}
template <typename T>
SharedPtr<T>::~SharedPtr() {
  if (object) {
    (*counter)--;
    if (*counter == 0) {
      delete object;
      delete counter;
    }
  }
}
template <typename T>
SharedPtr<T>::operator bool() const {
  if (object == nullptr) return false;
  return true;
}
template <typename T>
auto SharedPtr<T>::operator*() const -> T& {
  return *object;
}

template <typename T>
auto SharedPtr<T>::operator->() const -> T* {
  return object;
}
template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  return *counter;
}
template <typename T>
void SharedPtr<T>::reset() {
  if (object) {
    (*counter)--;
    if (counter == 0) {
      delete object;
      delete counter;
    }
    object = nullptr;
    counter = nullptr;
  }
}
template <typename T>
void SharedPtr<T>::reset(T* ptr) {
  if(counter)
  (*counter)--;
  if (counter == 0) {
    delete object;
    delete counter;
  }
  counter = new std::atomic_size_t;
  object = ptr;
  (*counter) = 1;
}
template <typename T>
void SharedPtr<T>::swap(SharedPtr& r) {
  std::swap(object, r.object);
  std::swap(counter, r.pairOfAddress);
}
template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr& r) -> SharedPtr& {
  if (&r != this) {
    if (object) {
      (*counter)--;
      if (counter == 0) {
        delete object;
        delete counter;
      }
    }
    object = r.object;
    counter = r.counter;
    if (counter) (*counter)++;
  }
  return *this;
}
template <typename T>
auto SharedPtr<T>::operator=(SharedPtr&& r) -> SharedPtr& {
  if (&r != this) {
    if (object) {
      (*counter)--;
      if (counter == 0) {
        delete object;
        delete counter;
      }
    }
    object = r.object;
    counter = r.counter;
    r.object = nullptr;
    r.counter = nullptr;
  }
  return *this;
}

#endif  // TEMPLATE_SHAREDPTR_H
