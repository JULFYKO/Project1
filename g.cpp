#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
using namespace std;

class NegOrZeroSide : public invalid_argument {
public:
    NegOrZeroSide(const string& msg = "Side cannot be negative or zero")
        : invalid_argument(msg) {}
};

class InvalidTriangle : public logic_error {
public:
    InvalidTriangle(const string& msg = "Invalid triangle")
        : logic_error(msg) {}
};

class IndexOutOfRange : public out_of_range {
public:
    IndexOutOfRange(const string& msg = "Index out of range")
        : out_of_range(msg) {}
};

class InvalidArg : public invalid_argument {
public:
    InvalidArg(const string& msg = "Invalid argument")
        : invalid_argument(msg) {}
};

double triangleArea(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0)
        throw NegOrZeroSide();
    if (a + b <= c || a + c <= b || b + c <= a)
        throw InvalidTriangle();
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

class Array {
    vector<int> data;

public:
    explicit Array(size_t size) : data(size) {}

    int& operator[](size_t index) {
        if (index >= data.size())
            throw IndexOutOfRange();
        return data[index];
    }

    Array operator+(const Array& other) const {
        if (data.size() != other.data.size())
            throw InvalidArg("Arrays must be of the same size");
        Array result(data.size());
        for (size_t i = 0; i < data.size(); ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    void fill(const vector<int>& values) {
        if (values.size() != data.size())
            throw InvalidArg("Mismatched size");
        data = values;
    }

    void print() const {
        for (int v : data) cout << v << " ";
        cout << endl;
    }
};

int main() {
    try {
        double a, b, c;
        a = 3;
        b = 4;
        c = 5;
        cout << "Triangle area: " << triangleArea(a, b, c) << endl;

        Array arr1(3), arr2(3);
        arr1.fill({ 1, 2, 3 });
        arr2.fill({ 4, 5, 6 });
        Array result = arr1 + arr2;

        cout << "Arr 1: ";
        arr1.print();
        cout << "Arr 2: ";
        arr2.print();
        cout << "Result: ";
        result.print();
    }
    catch (const exception& ex) {
        cout << "Exception: " << ex.what() << endl;
    }

    return 0;
}
