# IEEE 754 Binary Converter

Authors (team):\
Pavlosiuk Roman - https://github.com/UCUgllekk \
Hrynda Yuliana - https://github.com/YulianaHrynda \
Denysova Iryna - https://github.com/Shnapa

This project provides bidirectional conversion between binary string representation and floating-point formats:
- **FP16** (Half precision, 16-bit)
- **FP32** (`float`)
- **FP64** (`double`)
- **FP80** (`long double`, x86-specific extended precision)

The converter supports:
- Normalized and denormalized numbers
- Positive and negative zero
- Infinity (`+Inf`, `-Inf`)
- NaN values (both **quiet NaN** and **signaling NaN** for FP16)

---

## Build Instructions

### Clone with Google Test (as submodule)

```bash
git clone https://github.com/YulianaHrynda/ieee754_hrynda_pavlosiuk_denysova.git
cd ieee754_hrynda_pavlosiuk_denysova
```
```bash
git submodule add https://github.com/google/googletest.git external/googletest
git submodule update --init --recursive
```

## Build the project

```bash
mkdir build && cd build
cmake ..
make
```

Run Google Tests
```bash
./run_tests
```
