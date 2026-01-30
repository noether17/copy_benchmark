#pragma once

#include <algorithm>

#include "instantiate_copiers.hpp"

template <typename T>
void copy_n_copier(T* dest, T const* src, std::size_t n) {
  std::copy_n(src, n, dest);
}

INSTANTIATE_COPIERS(copy_n_copier);
