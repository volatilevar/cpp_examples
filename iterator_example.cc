// Based on https://gist.github.com/jeetsukumaran/307264
// Simplified and correct errors in the original post

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

template <typename T>
class MyArray
{
public:

    class iterator
    {
    public:
        // Required iterator traits
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef int difference_type;

        iterator(T* ptr) : _ptr(ptr) { }
        iterator operator++() { _ptr++; return *this; }
        iterator operator++(int junk) { iterator i = *this; _ptr++; return i; }
        T& operator*() { return *_ptr; }
        T* operator->() { return _ptr; }
        bool operator==(const iterator& rhs) const { return _ptr == rhs._ptr; }
        bool operator!=(const iterator& rhs) const { return _ptr != rhs._ptr; }
    private:
        T* _ptr;
    };

    MyArray(int size) : _size(size) {
        _data = new T[size];
    }
    
    ~MyArray() {
        delete[] _data;
    }

    int size() const { return _size; }

    T& operator[](int index)
    {
        assert(index < _size);
        return _data[index];
    }

    iterator begin()
    {
        return _data;
    }

    iterator end()
    {
        return _data + _size;
    }

private:
    T*  _data;
    int _size;
};


int main()
{
    MyArray<double> point3d(3);
    point3d[0] = 2.3;
    point3d[1] = 3.2;
    point3d[2] = 4.2;

    for(MyArray<double>::iterator i = point3d.begin(); i != point3d.end(); i++)
    {
        std::cout << *i << " ";
    }

    std::cout << std::endl;

    std::vector<double> vec;
    std::copy(point3d.begin(), point3d.end(), std::back_inserter(vec));

    for(std::vector<double>::iterator i = vec.begin(); i != vec.end(); i++)
    {
        std::cout << *i << " ";
    }

    std::cout << std::endl;
    return 0;
}
