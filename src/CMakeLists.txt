set(COPIERS
  memcpy
  copy_n
  for_loop
)

set(DATA_TYPES
  std::uint8_t
  std::uint16_t
  std::uint32_t
  std::uint64_t
)

set(GENERATED_FILE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
foreach(COPIER IN LISTS COPIERS)
  foreach(DATA_TYPE IN LISTS DATA_TYPES)
    string(REGEX REPLACE ".*::" "" DATA_TYPE_NAME "${DATA_TYPE}")

    set(COPIER_FUNCTION_NAME "${COPIER}_${DATA_TYPE_NAME}_copier")

    set(HEADER_FILE_NAME "${COPIER_FUNCTION_NAME}.hpp")
    set(HEADER_FILE_PATH "${GENERATED_FILE_DIR}/${HEADER_FILE_NAME}")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/copier.hpp.in"
      "${HEADER_FILE_PATH}"
    )

    set(SOURCE_FILE_NAME "${COPIER_FUNCTION_NAME}.cpp")
    set(SOURCE_FILE_PATH "${GENERATED_FILE_DIR}/${SOURCE_FILE_NAME}")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${COPIER}_copier.cpp.in"
      "${SOURCE_FILE_PATH}"
    )

    add_library("${COPIER_FUNCTION_NAME}" STATIC "${SOURCE_FILE_PATH}")
    target_include_directories("${COPIER_FUNCTION_NAME}" PUBLIC
      "${GENERATED_FILE_DIR}"
    )
    set_target_properties("${COPIER_FUNCTION_NAME}" PROPERTIES
      HEADER_FILE_NAME "${HEADER_FILE_NAME}"
    )
    set_property(GLOBAL APPEND PROPERTY COPIER_FUNCTIONS
      "${COPIER_FUNCTION_NAME}"
    )
  endforeach()
endforeach()
