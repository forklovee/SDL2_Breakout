#pragma once

#include <cmath>
#include <ostream>
#include <type_traits>

template<typename T, 
        typename = typename std::enable_if<std::is_same<T, int>::value ||
                                        std::is_same<T, float>::value>::type>
struct Vector2 {
    T x;
    T y;

    Vector2() = default;
    Vector2(T xy) : x(xy), y(xy) {};
    Vector2(T x, T y) : x(x), y(y) {};

    bool is_zero() const {
        return static_cast<int>(x) == 0 && static_cast<int>(y) == 0;
    }

    Vector2 operator+(const Vector2& other_vec) const {
        return {x + other_vec.x, y + other_vec.y};
    }

    Vector2 operator-(const Vector2& other_vec) const {
        return {x - other_vec.x, y - other_vec.y};
    }

    Vector2 operator*(const float scale) const {
        return {x * scale, y * scale};
    }

    Vector2 operator*(const Vector2& other_vec) const {
        return {x * other_vec.x, y * other_vec.y};
    }

    Vector2 operator/(const float scale) const {
        if (scale == 0.f){
            return {x, y};
        }
        return {x / scale, y / scale};
    }

    Vector2 operator/(const Vector2 other_vec) const {
        return {
            (other_vec.x == 0.f) ? x / other_vec.x : 0.f,
            (other_vec.y == 0.f) ? y / other_vec.y : 0.f
        };
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

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

// Vector3

struct Vector3f {
    float x{0.f};
    float y{0.f};
    float z{0.f};

    Vector3f() = default;
    Vector3f(float x, float y, float z) : x(x), y(y), z(z) {};

    Vector3f operator+(const Vector3f& other_vec) const {
        return {x + other_vec.x, y + other_vec.y, z + other_vec.z};
    }

    Vector3f operator-(const Vector3f& other_vec) const {
        return {x - other_vec.x, y - other_vec.y, z - other_vec.z};
    }

    Vector3f operator*(const float scale) const {
        return {x * scale, y * scale, z * scale};
    }

    Vector3f operator*(const Vector3f& other_vec) const {
        return {x * other_vec.x, y * other_vec.y, z * other_vec.z};
    }

    Vector3f operator/(const float scale) const {
        if (scale == 0.f){
            return {0.f, 0.f, 0.f};
        }
        return {x / scale, y / scale, z / scale};
    }

    Vector3f operator/(const Vector3f other_vec) const {
        return {
            (other_vec.x == 0.f) ? x / other_vec.x : 0.f,
            (other_vec.y == 0.f) ? y / other_vec.y : 0.f,
            (other_vec.z == 0.f) ? z / other_vec.z : 0.f
        };
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3f& v) {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }
};

struct Vector3i {
    int x{0};
    int y{0};
    int z{0};

    Vector3i() = default;
    Vector3i(int x, int y, int z) : x(x), y(y), z(z) {};

    Vector3i operator+(const Vector3i& other_vec) const {
        return {x + other_vec.x, y + other_vec.y, z + other_vec.z};
    }

    Vector3i operator-(const Vector3i& other_vec) const {
        return {x - other_vec.x, y - other_vec.y, z + other_vec.z};
    }

    Vector3i operator*(const int scale) const {
        return {x * scale, y * scale, z * scale};
    }

    Vector3i operator*(const Vector3i& other_vec) const {
        return {x * other_vec.x, y * other_vec.y, z * other_vec.z};
    }

    Vector3i operator/(const int scale) const {
        if (scale == 0.f){
            return {0, 0, 0};
        }
        const int scale_int = static_cast<int>(scale);
        return {x / scale_int, y / scale_int, z / scale_int};
    }

    Vector3i operator/(const Vector3i& other_vec) const {
        return {
            (other_vec.x == 0) ? x / other_vec.x : 0,
            (other_vec.y == 0) ? y / other_vec.y : 0,
            (other_vec.z == 0) ? z / other_vec.z : 0
        };
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3i& v) {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }
};