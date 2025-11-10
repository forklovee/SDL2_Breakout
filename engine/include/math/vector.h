#pragma once

#include <cmath>
#include <ostream>
#include <type_traits>

template<typename T, 
        typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
struct Vector2 {
    T x;
    T y;

    Vector2() = default;
    Vector2(T xy) : x(xy), y(xy) {};
    Vector2(T x, T y) : x(x), y(y) {};

    template<typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value>::type>
    explicit constexpr Vector2(const Vector2<U>& other_vec)
        : x(static_cast<T>(other_vec.x)), y(static_cast<T>(other_vec.y)) 
        {}

    #pragma region Operators
    Vector2 operator+(const Vector2& other_vec) const {
        return {x + other_vec.x, y + other_vec.y};
    }

    Vector2 operator+=(const Vector2& other_vec) {
        x += other_vec.x;
        y += other_vec.y;
        return *this;
    }

    Vector2 operator-() const {
        return {-x, -y};
    }

    Vector2 operator-(const Vector2& other_vec) const {
        return {x - other_vec.x, y - other_vec.y};
    }

    Vector2 operator-=(const Vector2& other_vec) {
        x -= other_vec.x;
        y -= other_vec.y;
        return *this;
    }

    Vector2 operator*(const float scale) const {
        return {x * scale, y * scale};
    }

    Vector2 operator*=(const float& scale) {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vector2 operator*(const Vector2& other_vec) const {
        return {x * other_vec.x, y * other_vec.y};
    }

    Vector2 operator*=(const Vector2& other_vec) {
        x += other_vec.x;
        y += other_vec.y;
        return *this;
    }

    Vector2 operator/(const float scale) const {
        if (scale == 0.f){
            return {x, y};
        }
        return {x / scale, y / scale};
    }

    Vector2 operator/=(const float scale) {
        x /= scale;
        y /= scale;
        return *this;
    }

    Vector2 operator/(const Vector2 other_vec) const {
        return {
            (other_vec.x == 0.f) ? x / other_vec.x : 0.f,
            (other_vec.y == 0.f) ? y / other_vec.y : 0.f
        };
    }

    Vector2 operator/=(const Vector2& other_vec) {
        x /= other_vec.x;
        y /= other_vec.y;
        return *this;
    }
    #pragma endregion Operators

    #pragma region Utility
    bool is_zero() const {
        return static_cast<int>(x) == 0 && static_cast<int>(y) == 0;
    }

    const float length(){
        return std::sqrt(x*x + y*y);
    }

    const Vector2 direction() const{
        const float lenght = std::sqrt(x*x + y*y);
        return Vector2{x/lenght, y/lenght};
    }

    const Vector2 direction_to(Vector2& other_vec){
        Vector2 offset = other_vec;
        offset.x -= x;
        offset.y -= y;
        offset = offset.direction();
        return offset;
    }
    #pragma endregion Utility

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

// Vector3
template<typename T, 
        typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
struct Vector3 {
    T x;
    T y;
    T z;

    Vector3() = default;
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {};
    Vector3(T xyz) : x(xyz), y(xyz), z(xyz) {};

    template<typename U, typename std::enable_if<std::is_arithmetic<U>::value>::type>
    explicit constexpr Vector3(const Vector3<U>& other_vec)
        : x(static_cast<T>(other_vec.x)), y(static_cast<T>(other_vec.y)), z(static_cast<T>(other_vec.z))
        {}


    Vector3 operator+(const Vector3& other_vec) const {
        return {x + other_vec.x, y + other_vec.y, z + other_vec.z};
    }

    Vector3 operator+=(const Vector3& other_vec) {
        x += other_vec.x;
        y += other_vec.y;
        z += other_vec.z;
        return *this;
    }

    Vector3 operator-(const Vector3& other_vec) const {
        return {x - other_vec.x, y - other_vec.y, z - other_vec.z};
    }

    Vector3 operator-=(const Vector3& other_vec) {
        x -= other_vec.x;
        y -= other_vec.y;
        z -= other_vec.z;
        return *this;
    }

    Vector3 operator*(const float scale) const {
        return {x * scale, y * scale, z * scale};
    }

    Vector3 operator*=(const float& scale) {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    Vector3 operator*(const Vector3& other_vec) const {
        return {x * other_vec.x, y * other_vec.y, z * other_vec.z};
    }

    Vector3 operator*=(const Vector3& other_vec) {
        x *= other_vec.x;
        y *= other_vec.y;
        z *= other_vec.z;
        return *this;
    }

    Vector3 operator/(const float scale) const {
        if (scale == 0.f){
            return {0.f, 0.f, 0.f};
        }
        return {x / scale, y / scale, z / scale};
    }

    Vector3 operator/=(const float scale) {
        x /= scale;
        y /= scale;
        z /= scale;
        return *this;
    }

    Vector3 operator/(const Vector3 other_vec) const {
        return {
            (other_vec.x == 0.f) ? x / other_vec.x : 0.f,
            (other_vec.y == 0.f) ? y / other_vec.y : 0.f,
            (other_vec.z == 0.f) ? z / other_vec.z : 0.f
        };
    }

    Vector3 operator/=(const Vector3& other_vec) {
        x /= other_vec.x;
        y /= other_vec.y;
        z /= other_vec.z;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }
};