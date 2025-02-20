#include <iostream>
#include <cinttypes>
#include <bitset>
#include <bit>

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


int main() {
    float const num = -42.f;
    uint32_t bits = toBytes(num);
    std::cout << "floatToBits: " << std::bitset<32>(bits) << std::endl;
    float restored = toFloat(bits);
    std::cout << "bitsToFloat: " << restored << std::endl;
}
