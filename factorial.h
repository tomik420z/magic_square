#ifndef FACTORIAL_H
#define FACTORIAL_H

template<size_t N>
struct factorial {
    static constexpr size_t value = N * factorial<N - 1>::value;
};

template<>
struct factorial<0> {
    static constexpr size_t value = 1;
};

template<size_t N>
static constexpr size_t factorial_v = factorial<N>::value;

size_t fact(size_t num) {
    size_t f = 1;
    for(size_t i = 1; i <= num; ++i) {
        f *= i;
    }

    return f;
}

#endif

