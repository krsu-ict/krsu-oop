#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

template<class T>
class Stack
{
public:
    typedef size_t size_type;

    Stack() = default; // ask compiler to generate default constructor

    Stack(const Stack &other) : _data{new T[other._size]}, _size{other._size}
    {
        std::copy(other._data, other._data + other._size, _data);
    } // copy constructor

    Stack(Stack &&other) :
        _data{std::exchange(other._data, nullptr)},
        _size{std::exchange(other._size, 0)} {} // move constructor (C++11)

    Stack& operator=(const Stack &other)
    {
        if (this != &other) {
            T *temp = new T[other._size];
            std::copy(other._data, other._data + other._size, temp);

            delete[] _data;
            _data = temp;
            _size = other._size;
        }

        return *this;
    } // copy assignment operator

    Stack& operator=(Stack &&other)
    {
        if (this != &other) {
            delete[] _data;

            _data = std::exchange(other._data, nullptr);
            _size = std::exchange(other._size, 0);
        }

        return *this;
    } // move assignment operator

    ~Stack() // destructor
    {
        delete[] _data;
    }

    bool is_empty() const
    {
        return _size == 0;
    }

    size_type get_size() const
    {
        return _size;
    }

    void push(T value)
    {
        T *temp = new T[_size + 1];
        std::copy(_data, _data + _size, temp);
        temp[_size] = value;
        ++_size;

        delete[] _data;
        _data = temp;
    }

    T top() const
    {
        if (_size == 0) {
            throw std::out_of_range("The stack is empty.");
        }

        return _data[_size - 1];
    }

    void pop()
    {
        --_size;
        T *temp = new T[_size];
        std::copy(_data, _data + _size, temp);

        delete[] _data;
        _data = temp;
    }

private:
    // State
    T *_data{new T[0]};
    size_type _size{0};
};

