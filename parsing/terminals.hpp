#pragma once

namespace parsing {
    namespace terminals {

        // Here we will use C++14's variable templates to create templated
        // aliases of qi's terminals

        template <class T>
        auto terminal = nullptr;

        template <> auto terminal<int> = boost::spirit::qi::int_;
        template <> auto terminal<double> = boost::spirit::qi::double_;
        // ...

    }
}
