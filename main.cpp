#include "parsing/csv.hpp"

struct A { int a, b; double c; };

int main(int, char **)
{
    A a;
    std::string input { "1,2,4.2" };

    auto parser = parsing::csv::make_parser(&A::a, &A::b, &A::c);
    assert(parser.parse(input.begin(), input.end(), a));
    assert(a.a == 1 && a.b == 2 && a.c == 4.2);

    return (0);
}
