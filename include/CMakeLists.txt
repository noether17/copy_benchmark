add_library(warmup_copier STATIC warmup_copier.hpp)
set_target_properties(warmup_copier PROPERTIES LINKER_LANGUAGE CXX)

add_library(memcpy_copier STATIC memcpy_copier.hpp)
set_target_properties(memcpy_copier PROPERTIES LINKER_LANGUAGE CXX)

add_library(copy_n_copier STATIC copy_n_copier.hpp)
set_target_properties(copy_n_copier PROPERTIES LINKER_LANGUAGE CXX)

add_library(for_loop_copier STATIC for_loop_copier.hpp)
set_target_properties(for_loop_copier PROPERTIES LINKER_LANGUAGE CXX)
