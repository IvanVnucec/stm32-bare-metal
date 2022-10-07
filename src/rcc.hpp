#pragma once

#include "periph.hpp"
#include "reg.hpp"

struct rcc : periph<0x40021000> {
    struct cr       : reg<base, 0x00, rw> {};
    struct cfgr     : reg<base, 0x04, rw> {};
    struct cir      : reg<base, 0x08, rw> {};
    struct apb2rstr : reg<base, 0x0C, rw> {};
    struct apb1rstr : reg<base, 0x10, rw> {};
    struct ahbenr   : reg<base, 0x14, rw> {};
    struct apb2enr  : reg<base, 0x18, rw> {};
    struct apb1enr  : reg<base, 0x1C, rw> {};
    struct bdcr     : reg<base, 0x20, rw> {};
    struct csr      : reg<base, 0x24, rw> {};
};
