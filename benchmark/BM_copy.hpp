#pragma once

#include <benchmark/benchmark.h>

#include <vector>

#include "REPEAT.hpp"

template <auto copier, typename T>
static void BM_copy(benchmark::State& state) {
  auto const n_items = state.range(0);
  auto const a = [n_items] {
    auto v = std::vector<T>(n_items);
    for (auto i = 0; auto& x : v) {
      x = static_cast<T>(i++);
    }
    return v;
  }();
  auto b = std::vector<T>(n_items);

  for (auto _ : state) {
    REPEAT({
      auto result_ptr = b.data();
      copier(b.data(), a.data(), n_items);
      benchmark::DoNotOptimize(result_ptr);
      benchmark::ClobberMemory();
    });
  }

  state.SetItemsProcessed(n_items * N_REPEAT * state.iterations());
  state.SetBytesProcessed(n_items * sizeof(T) * N_REPEAT * state.iterations());
}

#define BM_COPY(COPIER, DATA_TYPE)               \
  BENCHMARK_TEMPLATE(BM_copy, COPIER, DATA_TYPE) \
      ->RangeMultiplier(2)                       \
      ->Range(1, (1 << 30) / sizeof(DATA_TYPE));
