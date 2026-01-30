#pragma once

#include <cstring>

#include "instantiate_copiers.hpp"

template <typename T>
void memcpy_copier(T* dest, T const* src, std::size_t n) {
  std::memcpy(dest, src, n * sizeof(T));
}

INSTANTIATE_COPIERS(memcpy_copier);
