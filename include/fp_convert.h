//
// Created by yuliana on 06.05.25.
//

#ifndef FP_CONVERT_H
#define FP_CONVERT_H

#include <string>
#include <cstdint>

// --- FP16 ---
std::string float16_to_bin(uint16_t value);
uint16_t bin_to_float16(const std::string& bin);
std::string classify_fp16(uint16_t bits); // new!

// --- FP32 ---
std::string float_to_bin(float value);
float bin_to_float(const std::string& bin);

// --- FP64 ---
std::string double_to_bin(double value);
double bin_to_double(const std::string& bin);

// --- FP80 ---
std::string long_double_to_bin(long double value);
long double bin_to_long_double(const std::string& bin);

#endif //FP_CONVERT_H
