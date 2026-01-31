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

set(GENERATED_FILE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
function(generate_copier_benchmark COPIER)
  get_target_property(COPIER_HEADER_FILE "${COPIER}" HEADER_FILE_NAME)
  get_target_property(COPIER_DATA_TYPE "${COPIER}" DATA_TYPE)
  set(BENCHMARK_NAME "${COPIER}_benchmark")
  set(SOURCE_FILE_NAME "${BENCHMARK_NAME}.cpp")
  set(SOURCE_FILE_PATH "${GENERATED_FILE_DIR}/${SOURCE_FILE_NAME}")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/copy_benchmark.cpp.in"
    "${SOURCE_FILE_PATH}"
  )
  add_library("${BENCHMARK_NAME}" OBJECT "${SOURCE_FILE_PATH}")
  target_include_directories("${BENCHMARK_NAME}" PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
  )
  target_link_libraries("${BENCHMARK_NAME}" PRIVATE
    benchmark::benchmark
    "${COPIER}"
  )
  target_link_libraries(copy_benchmark PRIVATE "${COPIER}")
  target_sources(copy_benchmark PRIVATE $<TARGET_OBJECTS:${BENCHMARK_NAME}>)
endfunction()

get_property(COPIERS GLOBAL PROPERTY COPIER_FUNCTIONS)
message(STATUS "COPIERS: ${COPIERS}")
foreach(COPIER IN LISTS COPIERS)
  generate_copier_benchmark("${COPIER}")
endforeach()

#add_library(memcpy_copier_benchmark OBJECT memcpy_copier_benchmark.cpp)
#target_link_libraries(memcpy_copier_benchmark PRIVATE
#  benchmark::benchmark
#  memcpy_copier
#)
#target_link_libraries(copy_benchmark PRIVATE
#  memcpy_copier
#)
#target_sources(copy_benchmark PRIVATE
#  $<TARGET_OBJECTS:memcpy_copier_benchmark>
#)
#
#add_library(copy_n_copier_benchmark OBJECT copy_n_copier_benchmark.cpp)
#target_link_libraries(copy_n_copier_benchmark PRIVATE
#  benchmark::benchmark
#  copy_n_copier
#)
#target_link_libraries(copy_benchmark PRIVATE
#  copy_n_copier
#)
#target_sources(copy_benchmark PRIVATE
#  $<TARGET_OBJECTS:copy_n_copier_benchmark>
#)
#
#add_library(for_loop_copier_benchmark OBJECT for_loop_copier_benchmark.cpp)
#target_link_libraries(for_loop_copier_benchmark PRIVATE
#  benchmark::benchmark
#  for_loop_copier
#)
#target_link_libraries(copy_benchmark PRIVATE
#  for_loop_copier
#)
#target_sources(copy_benchmark PRIVATE
#  $<TARGET_OBJECTS:for_loop_copier_benchmark>
#)
