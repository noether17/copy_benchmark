#pragma once

#include <benchmark/benchmark.h>

#include <vector>

#include "REPEAT.hpp"

template <auto copier, typename T>
static void BM_copy(benchmark::State& state) {
  auto const n_bytes = state.range(0);
  auto const a = [n_bytes] {
    auto v = std::vector<T>(n_bytes);
    for (auto i = 0; auto& x : v) {
      x = static_cast<T>(i++);
    }
    return v;
  }();
  auto b = std::vector<T>(n_bytes);

  for (auto _ : state) {
    REPEAT({
      auto result_ptr = b.data();
      copier(b.data(), a.data(), n_bytes);
      benchmark::DoNotOptimize(result_ptr);
      benchmark::ClobberMemory();
    });
  }

  state.SetBytesProcessed(n_bytes * N_REPEAT * state.iterations());
}

#define BM_COPY(COPIER, DATA_TYPE)               \
  BENCHMARK_TEMPLATE(BM_copy, COPIER, DATA_TYPE) \
      ->RangeMultiplier(2)                       \
      ->Range(1, (1 << 30) / sizeof(DATA_TYPE));
