#pragma once
#include <vector>
#include <cstdint>

class Bitstream {
public:
    template<typename T>
    void write(const T &val) {

        const uint8_t *bytes = reinterpret_cast<const uint8_t*>(&val);
        data.insert(data.end(), bytes, bytes + sizeof(T));
    }

    template<typename T>
    void read(T &val) {

        uint8_t *bytes = reinterpret_cast<uint8_t*>(&val);
        std::copy(data.begin(), data.begin() + sizeof(T), bytes);
        data.erase(data.begin(), data.begin() + sizeof(T));
    }

    std::vector<uint8_t> data;
};

