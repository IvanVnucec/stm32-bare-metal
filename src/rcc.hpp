#pragma once

struct rcc : periph<0x40021000> {
    using cr       = reg<base, 0x00>;
    using cfgr     = reg<base, 0x04>;
    using cir      = reg<base, 0x08>;
    using apb2rstr = reg<base, 0x0C>;
    using apb1rstr = reg<base, 0x10>;
    using ahbenr   = reg<base, 0x14>;
    using apb2enr  = reg<base, 0x18>;
    using apb1enr  = reg<base, 0x1C>;
    using bdcr     = reg<base, 0x20>;
    using csr      = reg<base, 0x24>;
};
