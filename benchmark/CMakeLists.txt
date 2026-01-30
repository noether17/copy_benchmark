add_executable(copy_benchmark)
target_link_libraries(copy_benchmark PRIVATE
  benchmark::benchmark
  benchmark::benchmark_main
)

add_library(warmup_copier_benchmark OBJECT warmup_copier_benchmark.cpp)
target_link_libraries(warmup_copier_benchmark PRIVATE
  benchmark::benchmark
  warmup_copier
)
target_link_libraries(copy_benchmark PRIVATE
  warmup_copier
)
target_sources(copy_benchmark PRIVATE
  $<TARGET_OBJECTS:warmup_copier_benchmark>
)

add_library(memcpy_copier_benchmark OBJECT memcpy_copier_benchmark.cpp)
target_link_libraries(memcpy_copier_benchmark PRIVATE
  benchmark::benchmark
  memcpy_copier
)
target_link_libraries(copy_benchmark PRIVATE
  memcpy_copier
)
target_sources(copy_benchmark PRIVATE
  $<TARGET_OBJECTS:memcpy_copier_benchmark>
)

add_library(copy_n_copier_benchmark OBJECT copy_n_copier_benchmark.cpp)
target_link_libraries(copy_n_copier_benchmark PRIVATE
  benchmark::benchmark
  copy_n_copier
)
target_link_libraries(copy_benchmark PRIVATE
  copy_n_copier
)
target_sources(copy_benchmark PRIVATE
  $<TARGET_OBJECTS:copy_n_copier_benchmark>
)

add_library(for_loop_copier_benchmark OBJECT for_loop_copier_benchmark.cpp)
target_link_libraries(for_loop_copier_benchmark PRIVATE
  benchmark::benchmark
  for_loop_copier
)
target_link_libraries(copy_benchmark PRIVATE
  for_loop_copier
)
target_sources(copy_benchmark PRIVATE
  $<TARGET_OBJECTS:for_loop_copier_benchmark>
)
