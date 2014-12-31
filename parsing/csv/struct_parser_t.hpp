#pragma once

#include <tuple>

#include "../terminals.hpp"

namespace parsing {
    namespace csv {

        template <char sep, class C, class... Ts>
        struct struct_parser_t {

            using mem_ptrs_t = std::tuple<Ts C::*...>;
            template <class It>
            using rule_t = boost::spirit::qi::rule<It>;
            // TODO: Move that elsewhere
            template <bool cond>
            using enabler_t = typename std::enable_if<cond>::type;

            static constexpr auto size = sizeof...(Ts);

            struct_parser_t(Ts C::*... mem_ptrs):
                mem_ptrs(mem_ptrs...) { }

            template <class It>
            bool parse(It first, It last, C & c) const {
                using boost::spirit::qi::parse;

                static auto rule = csv_rule<0, It>(c);

                if (!parse(first, last, rule))
                    return false;
                return (first == last);
            }

        private:

            // Using template recursion to chain rules with the separator
            template <size_t i, class It, enabler_t<i < size - 1>...>
            rule_t<It> csv_rule(C & c) const {
                return field_rule<i, It>(c).copy() >> sep >>
                       csv_rule<i + 1, It>(c).copy();
            }

            // Edge case
            template <size_t i, class It, enabler_t<i == size - 1>...>
            rule_t<It> csv_rule(C & c) const {
                return field_rule<i, It>(c);
            }

            // Here we just return the terminal of the i-th type with a setter
            // to the i-th member as the semantic action
            template <size_t i, class It>
            rule_t<It> field_rule(C & c) const {
                using std::get;
                using std::move;
                using T = typename std::tuple_element<i, std::tuple<Ts...>>::type;

                auto setter = [this, &c](const T & v) {
                    c.*get<i>(mem_ptrs) = move(v);
                };

                return terminals::terminal<T>[setter];
            }

            mem_ptrs_t mem_ptrs;

        };

    }
}
