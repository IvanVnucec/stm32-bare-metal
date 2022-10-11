#pragma once

#include <cstdint>
#include <type_traits>

struct ro {
    template<std::uint32_t addr>
    static std::uint32_t read() { return *reinterpret_cast<volatile std::uint32_t *>(addr); }
};

struct wo {
    template<std::uint32_t addr>
    static void write(const std::uint32_t val) { *reinterpret_cast<volatile std::uint32_t *>(addr) = val; }
};

struct rw : ro, wo {};

template<std::uint32_t base, std::uint32_t offset=0, typename mut=void>
struct reg {
    static_assert(not std::is_same<mut, void>::value, "Register mutability not defined.");
    static constexpr std::uint32_t addr = base + offset;

    static std::uint32_t read() { return mut::template read<addr>(); }
    static void write(const std::uint32_t val) { mut::template write<addr>(val); }

    template<std::uint32_t val>
    static void mask() { write(val | read()); }

    template<std::uint32_t val>
    static void clear() { write(~val & read()); }

    template<std::uint32_t val>
    static void toggle() { write(val ^ read()); } 
};
