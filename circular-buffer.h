#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <array>
#include <iostream>
#include <ostream>

template <class T>
class CircularBuffer {
 public:
  CircularBuffer() { Clear(); }

  void Print() const {
    for (const T& str : arr_) {
      std::cout << str << ", ";
    }
    std::cout << std::endl;
  }

  void Clear() { arr_.fill(T{}); }

  void Push(const T& el) { arr_[current_array_index_++ % kMaxArraySize] = el; }

  template <std::size_t N>
  void Push(const std::array<T, N>& ar) {
    std::size_t start_index = (N > kMaxArraySize) ? (N - kMaxArraySize) : 0;
    std::size_t elements_to_add = (N > kMaxArraySize) ? kMaxArraySize : N;

    current_array_index_ += start_index % kMaxArraySize;

    for (std::size_t i = start_index; i < start_index + elements_to_add; ++i) {
      Push(ar[i % N]);
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const CircularBuffer& obj) {
    obj.Print(os);
    return os;
  }

  friend bool operator==(const CircularBuffer& obj1,
                         const CircularBuffer& obj2) {
    return (obj1.arr_ == obj2.arr_);
  }

 private:
  int current_array_index_ = 0;
  static constexpr int kMaxArraySize = 4;
  std::array<T, kMaxArraySize> arr_;

  void Print(std::ostream& os) const {
    for (const T& str : arr_) {
      os << str << ", ";
    }
  }
};

#endif  // CIRCULAR_BUFFER_H
