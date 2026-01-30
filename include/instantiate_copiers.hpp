#pragma once

#include <cstdint>

#define INSTANTIATE_COPIERS(COPIER) \
  template void COPIER(std::uint8_t*, std::uint8_t const*, std::size_t); \
  template void COPIER(std::uint16_t*, std::uint16_t const*, std::size_t); \
  template void COPIER(std::uint32_t*, std::uint32_t const*, std::size_t); \
  template void COPIER(std::uint64_t*, std::uint64_t const*, std::size_t);
