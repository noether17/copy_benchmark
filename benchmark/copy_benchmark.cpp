#include <benchmark/benchmark.h>

#include <vector>

#include "copy_n_copier.hpp"
#include "for_loop_copier.hpp"
#include "memcpy_copier.hpp"
#include "warmup_copier.hpp"

#define REPEAT2(X) X X
#define REPEAT4(X) REPEAT2(REPEAT2(X))
#define REPEAT16(X) REPEAT4(REPEAT4(X))
#define REPEAT(X) REPEAT16(REPEAT16(X))

inline constexpr auto N_REPEAT = 256;

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

#define SINGLE_BM(COPIER, T)                \
  BENCHMARK_TEMPLATE(BM_copy, COPIER<T>, T) \
      ->RangeMultiplier(2)                  \
      ->Range(1, 1 << 30 / sizeof(T));
#define BM_ALL_TYPES(COPIER)        \
  SINGLE_BM(COPIER, std::uint8_t);  \
  SINGLE_BM(COPIER, std::uint16_t); \
  SINGLE_BM(COPIER, std::uint32_t); \
  SINGLE_BM(COPIER, std::uint64_t);
#define RUN_ALL_BMS()          \
  BM_ALL_TYPES(warmup_copier); \
  BM_ALL_TYPES(memcpy_copier); \
  BM_ALL_TYPES(copy_n_copier); \
  BM_ALL_TYPES(for_loop_copier);
RUN_ALL_BMS();
