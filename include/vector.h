#pragma once

#include <cmath>
#include <ostream>

struct Vector2f {
    float x{0.f};
    float y{0.f};

    Vector2f() = default;
    Vector2f(float x, float y) : x(x), y(y) {};

    Vector2f operator+(const Vector2f& other_vec) const {
        return {x + other_vec.x, y + other_vec.y};
    }

    Vector2f operator-(const Vector2f& other_vec) const {
        return {x - other_vec.x, y - other_vec.y};
    }

    Vector2f operator*(const float scale) const {
        return {x * scale, y * scale};
    }

    Vector2f operator*(const Vector2f& other_vec) const {
        return {x * other_vec.x, y * other_vec.y};
    }

    Vector2f operator/(const float scale) const {
        if (scale == 0.f){
            return {0.f, 0.f};
        }
        return {x / scale, y / scale};
    }

    Vector2f operator/(const Vector2f other_vec) const {
        return {
            (other_vec.x == 0.f) ? x / other_vec.x : 0.f,
            (other_vec.y == 0.f) ? y / other_vec.y : 0.f
        };
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2f& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

struct Vector2i {
    int x{0};
    int y{0};

    Vector2i() = default;
    Vector2i(int x, int y) : x(x), y(y) {};

    Vector2i operator+(const Vector2i& other_vec) const {
        return {x + other_vec.x, y + other_vec.y};
    }

    Vector2i operator-(const Vector2i& other_vec) const {
        return {x - other_vec.x, y - other_vec.y};
    }

    Vector2i operator*(const int scale) const {
        return {x * scale, y * scale};
    }

    Vector2i operator*(const Vector2i& other_vec) const {
        return {x * other_vec.x, y * other_vec.y};
    }

    Vector2i operator/(const int scale) const {
        if (scale == 0.f){
            return {0, 0};
        }
        const int scale_int = static_cast<int>(scale);
        return {x / scale_int, y / scale_int};
    }

    Vector2i operator/(const Vector2i& other_vec) const {
        return {
            (other_vec.x == 0) ? x / other_vec.x : 0,
            (other_vec.y == 0) ? y / other_vec.y : 0
        };
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2i& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};