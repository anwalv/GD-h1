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

float absoluteValue(float const x) {
    uint32_t bytes = toBytes(x);
    bytes = bytes & 0x7FFFFFFF;
    return toFloat(bytes);
}

double absoluteValue(double const x) {
    uint64_t bytes = toBytes(x);
    bytes = bytes & 0x7FFFFFFFFFFFFFFF;
    return toDouble(bytes);
}

float minValue(float const x, float const y) {
    uint32_t bytesX = toBytes(x);
    uint32_t bytesY = toBytes(y);

    bool isXLessThanY = (bytesX < bytesY);
    if (isXLessThanY) {
        return toFloat(bytesX);
    } else {
        return toFloat(bytesY);
    }
}

float maxValue(float const x, float const y) {
    uint32_t bytesX = toBytes(x);
    uint32_t bytesY = toBytes(y);

    bool isXGreaterThanY = (bytesX > bytesY);
    if (isXGreaterThanY) {
        return toFloat(bytesX);
    } else {
        return toFloat(bytesY);
    }
}

double minValue(double const x, double const y) {
    uint64_t bytesX = toBytes(x);
    uint64_t bytesY = toBytes(y);

    bool isXLessThanY = (bytesX < bytesY);
    if (isXLessThanY) {
        return toDouble(bytesX);
    } else {
        return toDouble(bytesY);
    }
}

double maxValue(double const x, double const y) {
    uint64_t bytesX = toBytes(x);
    uint64_t bytesY = toBytes(y);
    bool isXGreaterThanY = (bytesX > bytesY);
    if (isXGreaterThanY) {
        return toDouble(bytesX);
    } else {
        return toDouble(bytesY);
    }
}

float clamp(float const minVal, float const maxVal, float const value) {
    uint32_t minBytes = toBytes(minVal);
    uint32_t maxBytes = toBytes(maxVal);
    uint32_t valueBytes = toBytes(value);
    if (valueBytes < minBytes) {
        return toFloat(minBytes);
    } else if (valueBytes > maxBytes) {
        return toFloat(maxBytes);
    } else {
        return toFloat(valueBytes);
    }
}

double clamp(double const minVal, double const maxVal, double const value) {
    uint64_t minBytes = toBytes(minVal);
    uint64_t maxBytes = toBytes(maxVal);
    uint64_t valueBytes = toBytes(value);
    if (valueBytes < minBytes) {
        return toDouble(minBytes);
    } else if (valueBytes > maxBytes) {
        return toDouble(maxBytes);
    } else {
        return toDouble(valueBytes);
    }
}


int main() {

}
