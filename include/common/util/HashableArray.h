#ifndef TRUCKER_GAME_HASHABLEARRAY_H
#define TRUCKER_GAME_HASHABLEARRAY_H

#include <array>
#include <functional>

namespace std {
    template <typename T, size_t N>
    struct hash<std::array<T, N>> {
        size_t operator()(const std::array<T, N>& arr) const {
            size_t hashValue = 0;
            for (const auto& element : arr) {
                hashValue ^= std::hash<T>{}(element) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            }
            return hashValue;
        }
    };
}

#endif //TRUCKER_GAME_HASHABLEARRAY_H
