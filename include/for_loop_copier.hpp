#pragma once

#include "instantiate_copiers.hpp"

template <typename T>
void for_loop_copier(T* dest, T const* src, std::size_t n) {
  for (std::size_t i = 0; i < n; ++i) {
    dest[i] = src[i];
  }
}

INSTANTIATE_COPIERS(for_loop_copier);
