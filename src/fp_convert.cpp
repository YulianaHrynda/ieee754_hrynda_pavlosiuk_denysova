#include "fp_convert.h"
#include <bitset>
#include <cmath>
#include <cstring>
#include <limits>
#include <sstream>
#include <cassert>
#include <iostream>

// --- FP16 ---
std::string float16_to_bin(uint16_t value) {
    return std::bitset<16>(value).to_string();
}

uint16_t bin_to_float16(const std::string& bin) {
    return static_cast<uint16_t>(std::bitset<16>(bin).to_ulong());
}

std::string classify_fp16(const uint16_t bits) {
    const uint16_t exp = (bits >> 10) & 0x1F;
    const uint16_t frac = bits & 0x03FF;

    if (exp == 0) {
        if (frac == 0) return "zero";
        return "subnormal";
    }

    if (exp == 0x1F) {
        if (frac == 0) return "inf";
        if ((frac >> 9) & 1) return "qNaN";
        return "sNaN";
    }
    return "normal";
}

// --- FP32 ---
std::string float_to_bin(const float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, sizeof(bits));
    return std::bitset<32>(bits).to_string();
}

float bin_to_float(const std::string& bin) {
    const uint32_t bits = std::bitset<32>(bin).to_ulong();
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

// --- FP64 ---
std::string double_to_bin(const double value) {
    uint64_t bits;
    std::memcpy(&bits, &value, sizeof(bits));
    return std::bitset<64>(bits).to_string();
}

double bin_to_double(const std::string& bin) {
    const uint64_t bits = std::bitset<64>(bin).to_ullong();
    double value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

// --- FP80 (GCC, x86 only) ---
std::string long_double_to_bin(const long double value) {
    static_assert(sizeof(long double) == 10 || sizeof(long double) == 16, "Unsupported long double size");

    std::stringstream ss;
    const auto* ptr = reinterpret_cast<const uint8_t*>(&value);
    for (int i = sizeof(long double) - 1; i >= 0; --i) {
        ss << std::bitset<8>(ptr[i]);
    }
    return ss.str();
}

long double bin_to_long_double(const std::string& bin) {
    static_assert(sizeof(long double) == 10 || sizeof(long double) == 16, "Unsupported long double size");

    long double value = 0;
    uint8_t bytes[sizeof(long double)] = {};
    for (size_t i = 0; i < sizeof(long double); ++i) {
        std::bitset<8> byte(bin.substr(bin.size() - 8 * (i + 1), 8));
        bytes[i] = static_cast<uint8_t>(byte.to_ulong());
    }
    std::memcpy(&value, bytes, sizeof(long double));
    return value;
}