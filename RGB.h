#include <cmath>

class RGB {
public:
    float r, v, b;

    RGB(float a, float b, float c) {
        r = a;
        v = b;
        this->b = c;
    }

    RGB() : r(0), v(0), b(0) {}

    RGB& operator/=(const float& a) {
        if (a != 0) {
            r /= a;
            v /= a;
            b /= a;
        }
        return *this;
    }

    RGB& operator+=(const RGB& a) {
        r += a.r;
        v += a.v;
        b += a.b;
        return *this;
    }

    RGB& operator-=(const RGB& a) {
        r -= a.r;
        v -= a.v;
        b -= a.b;
        return *this;
    }

    bool operator==(const RGB& a) {
        return r == a.r && v == a.v && b == a.b;
    }

public:
    static float dist(const RGB& a, const RGB& b) {
        return sqrt(pow((b.r - a.r), 2) + pow((b.v - a.v), 2) + pow((b.b - a.b), 2));
    }
};