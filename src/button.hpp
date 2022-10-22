#pragma once

template<typename pin>
struct button {
    static bool pressed() { return pin::get_state(); }
};
