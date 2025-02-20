#include <iostream>
#include <cinttypes>
#include <bitset>
#include <limits>


uint32_t toBytes(float const x) {
    float const* x_ptr = &x;
    uint32_t const *bytes_ptr = (uint32_t const*)(x_ptr);
    return *bytes_ptr;
}
float toFloat(uint32_t const x) {
    uint32_t const* x_ptr = &x;
    float const *bytes_ptr = (float const*)(x_ptr);
    return *bytes_ptr;
}
bool isFinite(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7FFFFFFF) < 0x7F800000;
}

bool isInfinity(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7FFFFFFF) == 0x7F800000;
}

bool isPositiveInfinity(float const x) {
    uint32_t bytes = toBytes(x);
    return bytes == 0x7F800000;
}

bool isNegativeInfinity(float const x) {
    uint32_t bytes = toBytes(x);
    return bytes == 0xFF800000;
}
bool isAnyZero(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes == 0x00000000 || bytes == 0x80000000);
}

bool isPositiveZero(float const x) {
    uint32_t bytes = toBytes(x);
    return bytes == 0x00000000;
}

bool isNegativeZero(float const x) {
    uint32_t bytes = toBytes(x);
    return bytes == 0x80000000;
}

bool isNotANumber(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7F800000) == 0x7F800000 && (bytes & 0x007FFFFF) != 0;
}

bool isNormal(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7F800000) != 0x00000000 && (bytes & 0x7F800000) < 0x7F800000;
}

bool isSubnormal(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7F800000) == 0x00000000 && (bytes & 0x007FFFFF) != 0;
}

bool isSigned(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x80000000) != 0;
}
// 1 це обичне,2 це позитивна нескінченність,3- негативна нескінченність,4- NaN6: 5- Позитивний нуль,6- Негативний нуль, 7- Піднормальне число.
int classify(float const x) {
    uint32_t bytes = toBytes(x);
    uint32_t exponent = (bytes & 0x7F800000) >> 23;
    uint32_t fraction = bytes & 0x007FFFFF;
    bool sign = (bytes & 0x80000000) != 0;

    if (exponent == 0xFF) {
        if (fraction == 0) {
            if (sign) {
                return 3;
            } else {
                return 2;
            }
        } else {
            return 4;
        }
    }
    else if (exponent == 0) {
        if (fraction == 0) {
            if (sign) {
                return 6;
            } else {
                return 5;
            }
        } else {
            return 7;
        }
    }
    else {
        return 1;
    }
}

int main() {
    float const num = -42.f;
    uint32_t bits = toBytes(num);
    std::cout << "floatToBits: " << std::bitset<32>(bits) << std::endl;
    float restored = toFloat(bits);
    std::cout << "bitsToFloat: " << restored << std::endl;
    float num1 = 3.14f;
    float num2 = -3.14f;
    float num3 = 0.0f;
    float num4 = -0.0f;
    float num5 = std::numeric_limits<float>::infinity();
    float num6 = -std::numeric_limits<float>::infinity();
    float num7 = std::numeric_limits<float>::quiet_NaN();

    std::cout << "Classify num1 (3.14): " << classify(num1) << std::endl;
    std::cout << "Classify num2 (-3.14): " << classify(num2) << std::endl;
    std::cout << "Classify num3 (0.0): " << classify(num3) << std::endl;
    std::cout << "Classify num4 (-0.0): " << classify(num4) << std::endl;
    std::cout << "Classify num5 (Infinity): " << classify(num5) << std::endl;
    std::cout << "Classify num6 (-Infinity): " << classify(num6) << std::endl;
    std::cout << "Classify num7 (NaN): " << classify(num7) << std::endl;
}
