//
// Created by Лев on 12.10.2020.
//

#include "../include/SharedPtr.h"

#include <cstddef>
template <class T>
SharedPtr<T>::SharedPtr() {
  listOfAddress();
  object = nullptr;
}
template <typename T>
SharedPtr<T>::SharedPtr(T *ptr) {
  object = ptr;
  listOfAddress[ptr]++;
}
template <typename T>
auto SharedPtr<T>::get() -> T * {
  return object;
}
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &r) {
  object = r.object;
  listOfAddress[r.object]++;
}
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr &&r) {
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
auto SharedPtr<T>::operator*() const -> T & {
  return *object;
}

template <typename T>
auto SharedPtr<T>::operator->() const -> T * {
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
void SharedPtr<T>::reset(T *ptr) {
  listOfAddress[object]--;
  object = ptr;
  listOfAddress[object]++;
}
template <typename T>
void SharedPtr<T>::swap(SharedPtr &r) {
  T *buf = object;
  object = r.object;
  r.object = buf;
}
template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr &r) -> SharedPtr & {
  listOfAddress[r.object]--;
  object = r.object;
  listOfAddress[object]++;
  return *this;
}
template <typename T>
auto SharedPtr<T>::operator=(SharedPtr &&r) -> SharedPtr & {
  object = r.object;
  listOfAddress[object]++;
  r.reset();
  return *this;
}
