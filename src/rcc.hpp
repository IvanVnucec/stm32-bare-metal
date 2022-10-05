#pragma once

#include "reg.hpp"

struct rcc : periph<0x40021000> {
    struct cr       : reg<base, 0x00> {};
    struct cfgr     : reg<base, 0x04> {};
    struct cir      : reg<base, 0x08> {};
    struct apb2rstr : reg<base, 0x0C> {};
    struct apb1rstr : reg<base, 0x10> {};
    struct ahbenr   : reg<base, 0x14> {};
    struct apb2enr  : reg<base, 0x18> {};
    struct apb1enr  : reg<base, 0x1C> {};
    struct bdcr     : reg<base, 0x20> {};
    struct csr      : reg<base, 0x24> {};
};
