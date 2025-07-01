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

Vec2f& Vec2f::operator *=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2f Vec2f::operator/(float scalar) const {
    if (scalar == 0.0f) {
        throw std::invalid_argument("Cannot divide by zero scalar. 43");
    }
    return Vec2f(x / scalar, y / scalar);
}

Vec2f& Vec2f::operator /=(float scalar) {
    if (scalar == 0.0f) {
        throw std::invalid_argument("Cannot divide by zero scalar. 50");
    }
    x /= scalar;
    y /= scalar;
    return *this;
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
    float length = this->length();
    if (length == 0.0f) {
        throw std::invalid_argument("Cannot normalize the zero vector. 72");
    }
    return Vec2f(x/length, y/length);
}

Vec2f Vec2f::rotated(float angle) const {
    // Apply rotation matrix
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    return Vec2f(cos * x - sin * y, sin * x + cos * y);
}

Vec2f::operator sf::Vector2f() const {
    return sf::Vector2f(x, y);
}