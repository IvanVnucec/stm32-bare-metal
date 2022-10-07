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
    static void mask(const std::uint32_t val) { write(val | read()); }
    static void clear(const std::uint32_t val) { write(~val & read()); }
};
