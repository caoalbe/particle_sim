#include "Vec2f.hpp"

Vec2f::Vec2f(float x, float y) : x(x), y(y) {}

Vec2f Vec2f::operator+(Vec2f other) const {
    return Vec2f(x + other.x, y + other.y);
}

Vec2f Vec2f::operator-(Vec2f other) const {
    return Vec2f(x - other.x, y - other.y);
}

Vec2f Vec2f::operator*(double scalar) const {
    return Vec2f(scalar * x, scalar * y);
}

Vec2f operator*(double scalar, const Vec2f& vec) {
    return Vec2f(scalar * vec.x, scalar * vec.y);
}

// TODO: Handle division by zero
Vec2f Vec2f::operator/(double scalar) const {
    return Vec2f(x / scalar, y / scalar);
}
