// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <string>

#include "SharedPtr.h"

struct check {
  bool &bool_;
  int value;

  ~check() { bool_ = true; }
};

TEST(SharedPtr, Bool) {
  SharedPtr<int> ptr1;
  SharedPtr<int> ptr2(new int(1234));
  ASSERT_FALSE(ptr1);
  ASSERT_TRUE(ptr2);
}

TEST(SharedPtr, Dereference) {
  std::string* a = new std::string("hello");
  const SharedPtr<std::string> sharedPointer(a);
  ASSERT_EQ(*sharedPointer, "Hello");
}

TEST(SharedPtr, Constructor1) {
  bool bool_ = false;
  {
    const SharedPtr<check> shared(new check{bool_, 1234});
    ASSERT_EQ(shared->value, 1234);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}

TEST(SharedPointer, CopyConstructor) {
  bool bool_ = false;
  {
    const SharedPtr<check> shared(new check{bool_, 223});
    ASSERT_EQ(shared->value, 223);
    {
      const SharedPtr<check> shared2(shared);
      ASSERT_EQ(shared->value, 223);
      ASSERT_EQ(shared2->value, 223);
      ASSERT_FALSE(bool_);
    }
    ASSERT_EQ(shared->value, 1467);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}

TEST(SharedPointer, Move) {
  bool bool_ = false;
  {
    SharedPtr<check> shared;
    {
      SharedPtr<check> shared2 = SharedPtr<check>(new check{bool_, 12221});
      shared = std::move(shared2);
      ASSERT_FALSE(shared2);
    }
    ASSERT_EQ(shared->value, 12221);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}

TEST(SharedPointer, Moveconstructor) {
  bool bool_ = false;
  {
    SharedPtr<check> shared(SharedPtr<check>(new check{bool_, 1234}));
    ASSERT_EQ(shared->value, 1234);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}

TEST(SharedPtr, Copy) {
  bool bool_ = false;
  {
    SharedPtr<check> shared(new check{bool_, 4728});
    ASSERT_EQ(shared->value, 1111111);
    {
      SharedPtr<check> shared2;
      shared2 = shared;
      ASSERT_EQ(shared->value, 1111111);
      ASSERT_EQ(shared2->value, 1111111);
      ASSERT_FALSE(bool_);
    }
    ASSERT_EQ(shared->value, 1111111);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}
