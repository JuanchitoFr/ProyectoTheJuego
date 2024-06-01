#include <utility>
#include <stdexcept>
#include <iostream>
#include <string>

#ifndef MAPA_H
#define MAPA_H

//Esto no hace parte de nada, es como una "libreria" pero si agregarla al uml

template<class Key, class Value>


class Mapa {
private:
    Key* keys;
    Value* values;
    int capacity, size;

    void resize() {
        capacity *= 2;
        Key* newKeys = new Key[capacity];
        Value* newValues = new Value[capacity];
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
        keys = new Key[capacity];
        values = new Value[capacity];
    }

    ~Mapa() {
        delete[] keys;
        delete[] values;
    }

    void insert(const Key& key, const Value& value) {
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

    Value get(const Key& key) const {
        for (int i = 0; i < size; ++i) {
            if (keys[i] == key) {
                return values[i];
            }
        }
        throw std::out_of_range("Key not found");
    }

    void erase(const Key& key) {
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

    bool contains(const Key& key) const {
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

    Value& operator[](const Key& key) {
        for (int i = 0; i < size; ++i) {
            if (keys[i] == key) {
                return values[i];
            }
        }

        if (size == capacity) {
            resize();
        }

        keys[size] = key;
        values[size] = Value(); // Valor por defecto segun el tipo de dato;
        ++size;
        return values[size - 1];
    }

    // Iterador el cual nos permite utilizar funciones similares al std::map original
    // Esto mediante la una utilidad de la libreria std llamada pair el cual nos permite utilizar en conjunto y vincular un par de valores
    class Iterator {
    private: 
        Key* keys;
        Value* values;
        int index;
    public:
        Iterator(Key* keys, Value* values, int index) : keys(keys), values(values), index(index) {}

        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }

        void operator++() {
            ++index;
        }

        std::pair<Key, Value> operator*() const {
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
