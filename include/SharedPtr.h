//
// Created by Лев on 12.10.2020.
//

#ifndef TEMPLATE_SHAREDPTR_H
#define TEMPLATE_SHAREDPTR_H
#include "SharedPtr.h"
#include <cstddef>

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
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
  auto use_count() const -> size_t;
 private:
  static std::map<void*, std::atomic_int> listOfAddress;
  T* object;
};


#endif  // TEMPLATE_SHAREDPTR_H
