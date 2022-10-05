#pragma once

#include <cstdint>

template<std::uint32_t base_addr>
struct periph {
    static constexpr auto base = base_addr;
};
