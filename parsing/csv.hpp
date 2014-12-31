#pragma once

#include "csv/struct_parser_t.hpp"

namespace parsing {
    namespace csv {

        template <char sep = ',', class C, class... Ts>
        auto make_parser(Ts C::*... mem_ptrs)
        {
            return struct_parser_t<sep, C, Ts...> { mem_ptrs... };
        }

    }
}
