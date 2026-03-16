#pragma once
#include <list>
#include <unordered_map>
#include <stdexcept>

class LRUCache {
public:
    LRUCache(size_t capacity) : capacity_(capacity) {
        if (capacity_ == 0)
            throw std::invalid_argument("Capacity must be greater than zero");
    }

    int get(int key) {
        auto it = map_.find(key);

        if (it == map_.end())
            return -1;

        cache_.splice(cache_.begin(), cache_, it->second);

        return it->second->second;
    }

    void put(int key, int value) {

        auto it = map_.find(key);

        if (it != map_.end()) {
            it->second->second = value;
            cache_.splice(cache_.begin(), cache_, it->second);
            return;
        }

        if (cache_.size() == capacity_) {

            auto last = cache_.back();
            map_.erase(last.first);
            cache_.pop_back();
        }

        cache_.push_front({key, value});
        map_[key] = cache_.begin();
    }

    void printCache() {

        for (auto &p : cache_) {
            std::cout << "(" << p.first << "," << p.second << ") ";
        }

        std::cout << std::endl;
    }

private:

    size_t capacity_;

    std::list<std::pair<int,int>> cache_;

    std::unordered_map<int, std::list<std::pair<int,int>>::iterator> map_;
};