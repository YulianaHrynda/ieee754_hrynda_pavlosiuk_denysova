#include <iostream>
#include <iomanip>
#include "fp_convert.h"
#include <cassert>


int main() {
    float f = 3.14159f;
    std::string fbin = float_to_bin(f);
    assert(bin_to_float(fbin) == f);

    double d = 2.718281828;
    std::string dbin = double_to_bin(d);
    assert(bin_to_double(dbin) == d);

    uint16_t h = 0x3C00;
    std::string hbin = float16_to_bin(h);
    assert(bin_to_float16(hbin) == h);
    assert(classify_fp16(h) == "normal");

    uint16_t qnan = 0x7E00;
    assert(classify_fp16(qnan) == "qNaN");

    uint16_t snan = 0x7D00;
    assert(classify_fp16(snan) == "sNaN");

    uint16_t sub = 0x03FF;
    assert(classify_fp16(sub) == "subnormal");

    long double ld = 1.23456789012345L;
    std::string ldbin = long_double_to_bin(ld);
    long double ld2 = bin_to_long_double(ldbin);
    assert(std::abs(ld - ld2) < 1e-12);

    std::cout << "All tests passed!\n";
    return 0;
}
