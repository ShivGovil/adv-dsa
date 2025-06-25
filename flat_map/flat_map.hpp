#ifndef flat_map_HPP
#define flat_map_HPP

#include <cstdint>
#include <cfloat>
#include <xxhash.h>

template <typename K, typename V>
class flat_map {
  public:
    flat_map(int _capacity = INITIAL_CAP) : capacity(_capacity) {
      entries = new entry[capacity];
      cache = new uint8_t[capacity];
    }
    ~flat_map();

    void insert(const K &key, const V &value) {}

    void find(const K &key) {}

    void clear() {}

    V& operator[](const K &key) {}

    const V& operator[](const K &key) const {}

  private:
    static constexpr float LOAD_FACTOR = 0.875;
    static constexpr float GROWTH_FACTOR = 1.5;
    static constexpr uint8_t INITIAL_CAP = 128;

    struct entry {
      K key;
      V value;
      // status?
    };

    class Iterator {

    };

    entry *entries;
    uint8_t *cache;
    int capacity;
    int size{};

    void grow() {
    // realloc?

    }

    uint64_t hash() {

    }

};

#endif // flat_map_HPP
