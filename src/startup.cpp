#include <algorithm>
#include <cstdint>

using FuncType =  void(*)(void);

extern uintptr_t  __bss_start;
extern uintptr_t  __bss_end;
extern uintptr_t  __data_src_start;
extern uintptr_t  __data_dst_start;
extern uintptr_t  __data_dst_end;

extern FuncType __preinit_array_start[];
extern FuncType __preinit_array_end  [];
extern FuncType __init_array_start   [];
extern FuncType __init_array_end     [];
extern FuncType __fini_array_start[];
extern FuncType __fini_array_end  [];

extern "C" void clear_bss() {
    std::fill(&__bss_start, &__bss_end, UINT8_C(0x00));
}

extern "C" void copy_data() {
    const std::size_t size = static_cast<std::size_t>(&__data_dst_end - &__data_dst_start);
    std::copy(&__data_src_start, &__data_src_start + size, &__data_dst_start);
}

// TODO
/*
extern "C" void preinit_array() {
  std::for_each(__preinit_array_start,
                __preinit_array_end,
                [](FuncType const func)
                {
                  func();
                });
}

extern "C" void init_array() {
  std::for_each(__init_array_start,
                __init_array_end,
                [](FuncType const func)
                {
                  func();
                });
}

extern "C" void fini_array() {
  std::for_each(__fini_array_start,
                __fini_array_end,
                [](FuncType const func)
                {
                  func();
                });
}
*/