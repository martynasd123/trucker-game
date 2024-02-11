#ifndef TRUCKER_GAME_TRIPLE_H
#define TRUCKER_GAME_TRIPLE_H

#include <functional>

template<typename T1, typename T2, typename T3>
class Triple {
public:
    T1 first;
    T2 second;
    T3 third;
    Triple(T1 first, T2 second, T3 third) : first(first), second(second), third(third) {}

    bool operator==(const Triple& other) const {
        return first == other.first && second == other.second && third == other.third;
    }
};

namespace std {

    template<typename T1, typename T2, typename T3>
    struct hash<Triple<T1, T2, T3>> {
        size_t operator()(const Triple<T1, T2, T3>& triple) const {
            size_t hash1 = hash<T1>{}(triple.first);
            size_t hash2 = hash<T2>{}(triple.second);
            size_t hash3 = hash<T3>{}(triple.third);

            return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
        }
    };

}

#endif //TRUCKER_GAME_TRIPLE_H
