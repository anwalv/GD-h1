#include <iostream>
#include <cinttypes>
#include <limits>

uint32_t toBytes(float const x) {
    float const* x_ptr = &x;
    uint32_t const* bytes_ptr = (uint32_t const*)(x_ptr);
    return *bytes_ptr;
}

float toFloat(uint32_t const x) {
    uint32_t const* x_ptr = &x;
    float const* bytes_ptr = (float const*)(x_ptr);
    return *bytes_ptr;
}

uint64_t toBytes(double const x) {
    double const* x_ptr = &x;
    uint64_t const* bytes_ptr = (uint64_t const*)(x_ptr);
    return *bytes_ptr;
}

double toDouble(uint64_t const x) {
    uint64_t const* x_ptr = &x;
    double const* bytes_ptr = (double const*)(x_ptr);
    return *bytes_ptr;
}

bool isFinite(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7FFFFFFF) < 0x7F800000;
}

bool isFinite(double const x) {
    uint64_t bytes = toBytes(x);
    return (bytes & 0x7FFFFFFFFFFFFFFF) < 0x7FF0000000000000;
}

bool isInfinity(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7FFFFFFF) == 0x7F800000;
}

bool isInfinity(double const x) {
    uint64_t bytes = toBytes(x);
    return (bytes & 0x7FFFFFFFFFFFFFFF) == 0x7FF0000000000000;
}

bool isPositiveInfinity(float const x) {
    uint32_t bytes = toBytes(x);
    return bytes == 0x7F800000;
}

bool isPositiveInfinity(double const x) {
    uint64_t bytes = toBytes(x);
    return bytes == 0x7FF0000000000000;
}

bool isNegativeInfinity(float const x) {
    uint32_t bytes = toBytes(x);
    return bytes == 0xFF800000;
}

bool isNegativeInfinity(double const x) {
    uint64_t bytes = toBytes(x);
    return bytes == 0xFFF0000000000000;
}

bool isAnyZero(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes == 0x00000000 || bytes == 0x80000000);
}

bool isAnyZero(double const x) {
    uint64_t bytes = toBytes(x);
    return (bytes == 0x0000000000000000 || bytes == 0x8000000000000000);
}

bool isPositiveZero(float const x) {
    uint32_t bytes = toBytes(x);
    return bytes == 0x00000000;
}

bool isPositiveZero(double const x) {
    uint64_t bytes = toBytes(x);
    return bytes == 0x0000000000000000;
}

bool isNegativeZero(float const x) {
    uint32_t bytes = toBytes(x);
    return bytes == 0x80000000;
}

bool isNegativeZero(double const x) {
    uint64_t bytes = toBytes(x);
    return bytes == 0x8000000000000000;
}

bool isNotANumber(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7F800000) == 0x7F800000 && (bytes & 0x007FFFFF) != 0;
}

bool isNotANumber(double const x) {
    uint64_t bytes = toBytes(x);
    return (bytes & 0x7FF0000000000000) == 0x7FF0000000000000 && (bytes & 0x000FFFFFFFFFFFFF) != 0;
}

bool isNormal(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7F800000) != 0x00000000 && (bytes & 0x7F800000) < 0x7F800000;
}

bool isNormal(double const x) {
    uint64_t bytes = toBytes(x);
    return (bytes & 0x7FF0000000000000) != 0x0000000000000000 && (bytes & 0x7FF0000000000000) < 0x7FF0000000000000;
}

bool isSubnormal(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x7F800000) == 0x00000000 && (bytes & 0x007FFFFF) != 0;
}

bool isSubnormal(double const x) {
    uint64_t bytes = toBytes(x);
    return (bytes & 0x7FF0000000000000) == 0x0000000000000000 && (bytes & 0x000FFFFFFFFFFFFF) != 0;
}

bool isSigned(float const x) {
    uint32_t bytes = toBytes(x);
    return (bytes & 0x80000000) != 0;
}

bool isSigned(double const x) {
    uint64_t bytes = toBytes(x);
    return (bytes & 0x8000000000000000) != 0;
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

int classify(double const x) {
    uint64_t bytes = toBytes(x);
    uint64_t exponent = (bytes & 0x7FF0000000000000) >> 52;
    uint64_t fraction = bytes & 0x000FFFFFFFFFFFFF;
    bool sign = (bytes & 0x8000000000000000) != 0;

    if (exponent == 0x7FF) {
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
    float num1 = 3.14f;
    float num2 = -3.14f;
    float num3 = 0.0f;
    float num4 = -0.0f;
    float num5 = std::numeric_limits<float>::infinity();
    float num6 = -std::numeric_limits<float>::infinity();
    float num7 = std::numeric_limits<float>::quiet_NaN();
    double num8 = 3.14;
    double num9 = -3.14;
    double num10 = 0.0;
    double num11 = -0.0;
    double num12 = std::numeric_limits<double>::infinity();
    double num13 = -std::numeric_limits<double>::infinity();
    double num14 = std::numeric_limits<double>::quiet_NaN();

    std::cout << "Classify num1 (float): " << classify(num1) << std::endl;
    std::cout << "Classify num2 (float): " << classify(num2) << std::endl;
    std::cout << "Classify num3 (float): " << classify(num3) << std::endl;
    std::cout << "Classify num4 (float): " << classify(num4) << std::endl;
    std::cout << "Classify num5 (float): " << classify(num5) << std::endl;
    std::cout << "Classify num6 (float): " << classify(num6) << std::endl;
    std::cout << "Classify num7 (float): " << classify(num7) << std::endl;
    std::cout << "Classify num8 (double): " << classify(num8) << std::endl;
    std::cout << "Classify num9 (double): " << classify(num9) << std::endl;
    std::cout << "Classify num10 (double): " << classify(num10) << std::endl;
    std::cout << "Classify num11 (double): " << classify(num11) << std::endl;
    std::cout << "Classify num12 (double): " << classify(num12) << std::endl;
    std::cout << "Classify num13 (double): " << classify(num13) << std::endl;
    std::cout << "Classify num14 (double): " << classify(num14) << std::endl;

    return 0;
}
