//
//
//
#ifndef WET_ARRAY_H
#define WET_ARRAY_H

template <class T>
class Array {
    T* data;
    int size_a;
public:
    explicit Array(int size_a);
    Array(const Array& a);
    Array& operator=(const Array& a);
    ~Array();
    int size() const;
    T& operator[](int index);
    const T& operator[](int index) const;
    class BadIndex {
    public:
        int index;
        explicit BadIndex(int index) : index(index) {}
    };
};



#endif //WET_ARRAY_H
