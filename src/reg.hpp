#pragma once

#include <cstdint>

template<std::uint32_t base, std::uint32_t offset=0>
struct reg {
    static constexpr std::uint32_t addr = base + offset;

    static void write(const std::uint32_t val) { *reinterpret_cast<volatile std::uint32_t *>(addr) = val; }
    static std::uint32_t read() { return *reinterpret_cast<volatile std::uint32_t *>(addr); }
    static void mask(const std::uint32_t val) { write(val | read()); }
    static void clear(const std::uint32_t val) { write(~val & read()); }
};
