add_executable(copy_benchmark)
target_link_libraries(copy_benchmark PRIVATE
  benchmark::benchmark
  benchmark::benchmark_main
)

add_library(warmup_copier STATIC warmup_copier.hpp)
set_target_properties(warmup_copier PROPERTIES
  LINKER_LANGUAGE CXX
  DATA_TYPE std::uint8_t
  HEADER_FILE_NAME warmup_copier.hpp
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
  target_compile_features("${BENCHMARK_NAME}" PRIVATE cxx_std_20)
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

generate_copier_benchmark(warmup_copier)

get_property(COPIERS GLOBAL PROPERTY COPIER_FUNCTIONS)
message(STATUS "COPIERS: ${COPIERS}")
foreach(COPIER IN LISTS COPIERS)
  generate_copier_benchmark("${COPIER}")
endforeach()

add_custom_target(run_benchmark
  "bash"
  "${CMAKE_SOURCE_DIR}/scripts/run_benchmark.sh"
  "${CMAKE_CURRENT_BINARY_DIR}/copy_benchmark"
)
