#pragma once

#include "instantiate_copiers.hpp"

template <typename T>
void warmup_copier(T*, T const*, std::size_t) {}

INSTANTIATE_COPIERS(warmup_copier);
