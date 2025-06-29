#include "Vec2f.hpp"

Vec2f::Vec2f(float x, float y) : x(x), y(y) {}

Vec2f::Vec2f() : x(0), y(0) {}

Vec2f Vec2f::operator+(Vec2f other) const {
    return Vec2f(x + other.x, y + other.y);
}

Vec2f& Vec2f::operator+=(const Vec2f& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2f Vec2f::operator-(Vec2f other) const {
    return Vec2f(x - other.x, y - other.y);
}

Vec2f& Vec2f::operator-=(const Vec2f& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2f Vec2f::operator*(float scalar) const {
    return Vec2f(scalar * x, scalar * y);
}

Vec2f operator*(float scalar, const Vec2f& vec) {
    return Vec2f(scalar * vec.x, scalar * vec.y);
}

// TODO: Handle division by zero
Vec2f Vec2f::operator/(float scalar) const {
    return Vec2f(x / scalar, y / scalar);
}

bool Vec2f::operator==(Vec2f other) const {
    return x == other.x && y == other.y;
}

bool Vec2f::operator!=(Vec2f other) const {
    return x != other.x || y != other.y;
}

float Vec2f::length() const {
    return std::sqrt(x * x + y * y);
}

Vec2f Vec2f::normalized() const {
    // TODO: Handle zero vector
    float length = this->length();
    return Vec2f(x/length, y/length);
}

sf::Vector2f Vec2f::convert() {
    return sf::Vector2f(x, y);
}