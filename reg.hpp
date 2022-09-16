#pragma once

#include <cstdint>

template<const std::uint32_t addr_base, const std::uint32_t offset>
struct reg {
    static constexpr std::uint32_t addr = addr_base + offset;

    static std::uint32_t read() { return *reinterpret_cast<volatile const std::uint32_t*>(addr); }
    
    template<const std::uint32_t val>
    static void write() { *reinterpret_cast<volatile std::uint32_t*>(addr) = val; }
};
