#ifndef TRUCKER_GAME_MAPPEDVECTOR_H
#define TRUCKER_GAME_MAPPEDVECTOR_H

#include <vector>
#include <unordered_map>

using namespace std;

template<typename T>
class MappedVector {
private:
    vector<T> mVector;
    unordered_map<unsigned int, unsigned int> mIdToIndexMap;
    unsigned int last_id = 0;
public:

    unsigned int push_back(T element) {
        mIdToIndexMap[last_id] = mVector.size();
        mVector.push_back(element);
        return last_id++;
    }

    void eraseAtIndex(unsigned int index) {
        mVector.erase(index);
        for (const auto &entry: mIdToIndexMap) {
            if (entry.second == index) {
                mIdToIndexMap.erase(entry.first);
                return;
            }
        }
    }

    void eraseById(unsigned int id) {
        if (!mIdToIndexMap.contains(id)) {
            throw invalid_argument("Invalid ID");
        }
        mVector.erase(mVector.begin() + mIdToIndexMap[id]);
        mIdToIndexMap.erase(id);
    }

    unsigned int emplace_back(unsigned int index, T&& value) {
        mIdToIndexMap[last_id] = mVector.size();
        mVector.emplace_back(std::forward<T>(value));
        return last_id++;
    }

    unsigned int push_back(unsigned int index, T value) {
        mIdToIndexMap[last_id] = mVector.size();
        mVector.push_back(value);
        return last_id++;
    }

    std::vector<T>::iterator begin() {
        return mVector.begin();
    }

    std::vector<T>::iterator end() {
        return mVector.begin();
    }

    T& operator [](unsigned int index) {
        return mVector[index];
    }

    size_t size() const {
        return mVector.size();
    }
};


#endif //TRUCKER_GAME_MAPPEDVECTOR_H
