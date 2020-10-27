//
// Created by Лев on 12.10.2020.
//

#ifndef TEMPLATE_SHAREDPTR_H
#define TEMPLATE_SHAREDPTR_H
#include <atomic>
#include <cstddef>
#include <map>

#include "SharedPtr.h"
template <typename T>
class SharedPtr {
 public:
  SharedPtr(T&&);
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
  static std::map<void*, std::atomic_int> listOfAddress;
  T* object;
};

template <class T>
SharedPtr<T>::SharedPtr(T&& obj) {
  object = &obj;
  listOfAddress[object]++;
}
template <class T>
SharedPtr<T>::SharedPtr() {
  object = nullptr;
}
template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) {
  object = ptr;
  listOfAddress[ptr]++;
}
template <typename T>
auto SharedPtr<T>::get() -> T* {
  return object;
}
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& r) {
  object = r.object;
  listOfAddress[r.object]++;
}
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& r) {
  object = r.object;
  r.object = nullptr;
}
template <typename T>
SharedPtr<T>::~SharedPtr() {
  listOfAddress[object]--;
  if (listOfAddress[object] == 0) {
    delete object;
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
  return listOfAddress[object];
}
template <typename T>
void SharedPtr<T>::reset() {
  if (object) {
    listOfAddress[object]--;
  }
  object = nullptr;
}
template <typename T>
void SharedPtr<T>::reset(T* ptr) {
  listOfAddress[object]--;
  object = ptr;
  listOfAddress[object]++;
}
template <typename T>
void SharedPtr<T>::swap(SharedPtr& r) {
  T* buf = object;
  object = r.object;
  r.object = buf;
}
template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr& r) -> SharedPtr& {
  listOfAddress[r.object]--;
  object = r.object;
  listOfAddress[object]++;
  return *this;
}
template <typename T>
auto SharedPtr<T>::operator=(SharedPtr&& r) -> SharedPtr& {
  object = r.object;
  listOfAddress[object]++;
  r.reset();
  return *this;
}

#endif  // TEMPLATE_SHAREDPTR_H
