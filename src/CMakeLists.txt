set(COPIER_FAMILIES
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

foreach(COPIER_FAMILY IN LISTS COPIER_FAMILIES)
  foreach(DATA_TYPE IN LISTS DATA_TYPES)
    string(REGEX REPLACE ".*::" "" DATA_TYPE_NAME "${DATA_TYPE}")

    set(COPIER_FUNCTION_NAME "${COPIER_FAMILY}_${DATA_TYPE_NAME}_copier")

    set(HEADER_FILE_NAME "${COPIER_FUNCTION_NAME}.hpp")
    set(HEADER_FILE_PATH "${GENERATED_FILE_DIR}/${HEADER_FILE_NAME}")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/copier.hpp.in"
      "${HEADER_FILE_PATH}"
    )

    set(SOURCE_FILE_NAME "${COPIER_FUNCTION_NAME}.cpp")
    set(SOURCE_FILE_PATH "${GENERATED_FILE_DIR}/${SOURCE_FILE_NAME}")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${COPIER_FAMILY}_copier.cpp.in"
      "${SOURCE_FILE_PATH}"
    )

    add_library("${COPIER_FUNCTION_NAME}" STATIC "${SOURCE_FILE_PATH}")
    target_include_directories("${COPIER_FUNCTION_NAME}" PUBLIC
      "${GENERATED_FILE_DIR}"
    )
    set_target_properties("${COPIER_FUNCTION_NAME}" PROPERTIES
      DATA_TYPE "${DATA_TYPE}"
      HEADER_FILE_NAME "${HEADER_FILE_NAME}"
    )
    set_property(GLOBAL APPEND PROPERTY COPIER_FUNCTIONS
      "${COPIER_FUNCTION_NAME}"
    )
  endforeach()
endforeach()

foreach(COPIER_FAMILY IN LISTS COPIER_FAMILIES)
  foreach(DATA_TYPE IN LISTS DATA_TYPES)
    string(REGEX REPLACE ".*::" "" DATA_TYPE_NAME "${DATA_TYPE}")

    set(COPIER_FUNCTION_NAME
      "${COPIER_FAMILY}_${DATA_TYPE_NAME}_restrict_copier"
    )

    set(HEADER_FILE_NAME "${COPIER_FUNCTION_NAME}.hpp")
    set(HEADER_FILE_PATH "${GENERATED_FILE_DIR}/${HEADER_FILE_NAME}")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/restrict_copier.hpp.in"
      "${HEADER_FILE_PATH}"
    )

    set(SOURCE_FILE_NAME "${COPIER_FUNCTION_NAME}.cpp")
    set(SOURCE_FILE_PATH "${GENERATED_FILE_DIR}/${SOURCE_FILE_NAME}")
    configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/${COPIER_FAMILY}_restrict_copier.cpp.in"
      "${SOURCE_FILE_PATH}"
    )

    add_library("${COPIER_FUNCTION_NAME}" STATIC "${SOURCE_FILE_PATH}")
    target_include_directories("${COPIER_FUNCTION_NAME}" PUBLIC
      "${GENERATED_FILE_DIR}"
    )
    set_target_properties("${COPIER_FUNCTION_NAME}" PROPERTIES
      DATA_TYPE "${DATA_TYPE}"
      HEADER_FILE_NAME "${HEADER_FILE_NAME}"
    )
    set_property(GLOBAL APPEND PROPERTY COPIER_FUNCTIONS
      "${COPIER_FUNCTION_NAME}"
    )
  endforeach()
endforeach()

get_property(LOCAL_COPIER_FUNCTIONS GLOBAL PROPERTY COPIER_FUNCTIONS)
message(STATUS "COPIER_FUNCTIONS (src): ${LOCAL_COPIER_FUNCTIONS}")
