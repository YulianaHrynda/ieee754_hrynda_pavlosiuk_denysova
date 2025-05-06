#include <gtest/gtest.h>
#include "fp_convert.h"
#include <cmath>
#include <limits>
#include <vector>

// FP32 Tests
TEST(FP32Test, RoundTripCommonValues) {
    std::vector<float> values = {
        0.0f, -0.0f, 1.0f, -1.0f, 3.14159f, -2.71828f,
        std::numeric_limits<float>::min(), std::numeric_limits<float>::max(),
        std::numeric_limits<float>::denorm_min(), 1e-38f, -1e-38f
    };
    for (float val : values) {
        std::string bin = float_to_bin(val);
        EXPECT_EQ(bin_to_float(bin), val);
    }
}

TEST(FP32Test, SpecialValues) {
    EXPECT_TRUE(std::isinf(bin_to_float(float_to_bin(INFINITY))));
    EXPECT_TRUE(std::isinf(bin_to_float(float_to_bin(-INFINITY))));
    EXPECT_TRUE(std::isnan(bin_to_float(float_to_bin(NAN))));
}

// FP64 Tests
TEST(FP64Test, RoundTripCommonValues) {
    std::vector<double> values = {
        0.0, -0.0, 1.0, -1.0, 2.718281828, -3.1415926535,
        std::numeric_limits<double>::min(), std::numeric_limits<double>::max(),
        std::numeric_limits<double>::denorm_min(), 1e-300, -1e-300
    };
    for (double val : values) {
        std::string bin = double_to_bin(val);
        EXPECT_EQ(bin_to_double(bin), val);
    }
}

TEST(FP64Test, SpecialValues) {
    EXPECT_TRUE(std::isinf(bin_to_double(double_to_bin(INFINITY))));
    EXPECT_TRUE(std::isinf(bin_to_double(double_to_bin(-INFINITY))));
    EXPECT_TRUE(std::isnan(bin_to_double(double_to_bin(NAN))));
}

// FP16 Tests
TEST(FP16Test, RoundTripBinary) {
    std::vector<uint16_t> values = {
        0x0000, 0x8000, 0x3C00, 0xBC00, 0x7BFF, 0x0001,
        0x03FF, 0x7C00, 0xFC00, 0x7E00, 0x7D00, 0x3555, 0x2000, 0x6E66
    };
    for (uint16_t val : values) {
        std::string bin = float16_to_bin(val);
        EXPECT_EQ(bin_to_float16(bin), val);
    }
}

TEST(FP16Test, Classification) {
    EXPECT_EQ(classify_fp16(0x0000), "zero");      // +0
    EXPECT_EQ(classify_fp16(0x8000), "zero");      // -0
    EXPECT_EQ(classify_fp16(0x0001), "subnormal"); // smallest subnormal
    EXPECT_EQ(classify_fp16(0x03FF), "subnormal"); // largest subnormal
    EXPECT_EQ(classify_fp16(0x0400), "normal");    // smallest normal
    EXPECT_EQ(classify_fp16(0x3C00), "normal");    // 1.0
    EXPECT_EQ(classify_fp16(0x7BFF), "normal");    // max normal
    EXPECT_EQ(classify_fp16(0x7C00), "inf");       // +inf
    EXPECT_EQ(classify_fp16(0xFC00), "inf");       // -inf
    EXPECT_EQ(classify_fp16(0x7E00), "qNaN");      // quiet NaN
    EXPECT_EQ(classify_fp16(0x7D00), "sNaN");      // signaling NaN
    EXPECT_EQ(classify_fp16(0x3555), "normal");    // arbitrary normal
    EXPECT_EQ(classify_fp16(0x2000), "normal");    // small exponent
    EXPECT_EQ(classify_fp16(0x6E66), "normal");    // another pattern
}

TEST(FP80Test, RoundTripPrecision) {
    std::vector<long double> values = {
        0.0L, -0.0L, 1.0L, -1.0L, 3.1415926535897932384626L,
        1.2345678901234567890L, -2.718281828459045235360L,
        std::numeric_limits<long double>::min(), std::numeric_limits<long double>::max(),
        std::numeric_limits<long double>::denorm_min()
    };
    for (long double val : values) {
        std::string bin = long_double_to_bin(val);
        long double result = bin_to_long_double(bin);
        EXPECT_NEAR(static_cast<double>(result), static_cast<double>(val), 1e-12);
    }
}
