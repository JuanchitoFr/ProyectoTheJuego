#include <utility>
#include <stdexcept>
#include <iostream>
#include <string>

#ifndef MAPA_H
#define MAPA_H


template<class Key, class Value>

class Mapa {
private:
    Key* keys;
    Value* values;
    int capacity, size;

    void resize() {
        capacity *= 2;
        Key* newKeys = new K[capacity];
        Value* newValues = new V[capacity];
        for (int i = 0; i < size; ++i) {
            newKeys[i] = keys[i];
            newValues[i] = values[i];
        }
        delete[] keys;
        delete[] values;
        keys = newKeys;
        values = newValues;
    }

public:
    Mapa() : capacity(1), size(0) {
        keys = new K[capacity];
        values = new V[capacity];
    }

    ~Mapa() {
        delete[] keys;
        delete[] values;
    }

    void insert(const K& key, const V& value) {
        for (int i = 0; i < size; ++i) {
            if (keys[i] == key) {
                values[i] = value;
                return;
            }
        }

        if (size == capacity) {
            resize();
        }

        keys[size] = key;
        values[size] = value;
        ++size;
    }

    V get(const K& key) const {
        for (int i = 0; i < size; ++i) {
            if (keys[i] == key) {
                return values[i];
            }
        }
        throw std::out_of_range("Key not found");
    }

    void erase(const K& key) {
        for (int i = 0; i < size; ++i) {
            if (keys[i] == key) {
                for (int j = i; j < size - 1; ++j) {
                    keys[j] = keys[j + 1];
                    values[j] = values[j + 1];
                }
                --size;
                return;
            }
        }
        throw std::out_of_range("Key not found");
    }

    bool contains(const K& key) const {
        for (int i = 0; i < size; ++i) {
            if (keys[i] == key) {
                return true;
            }
        }
        return false;
    }

    int getSize() const {
        return size;
    }

    V& operator[](const K& key) {
        for (int i = 0; i < size; ++i) {
            if (keys[i] == key) {
                return values[i];
            }
        }

        if (size == capacity) {
            resize();
        }

        keys[size] = key;
        values[size] = V(); // Valor por defecto segun el tipo de dato;
        ++size;
        return values[size - 1];
    }

    // Iterador el cual nos permite utilizar funciones similares al std::map original
    // Esto mediante pair el cual nos permite utilizar y vincular un par de valores
    class Iterator {
    private: 
        K* keys;
        V* values;
        int index;
    public:
        Iterator(K* keys, V* values, int index) : keys(keys), values(values), index(index) {}

        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }

        void operator++() {
            ++index;
        }

        std::pair<K, V> operator*() const {
            return std::make_pair(keys[index], values[index]);
        }
    };

    Iterator begin() {
        return Iterator(keys, values, 0);
    }

    Iterator end() {
        return Iterator(keys, values, size);
    }

};

#endif // !MAPA_H
