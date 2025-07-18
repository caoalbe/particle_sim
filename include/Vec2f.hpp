#pragma once
#include <SFML/Graphics.hpp>

class Vec2f {
    public:
        float x;
        float y;

        Vec2f();
        Vec2f(float x, float y);

        Vec2f operator+(Vec2f other) const;
        Vec2f& operator+=(const Vec2f& other); 

        Vec2f operator-(Vec2f other) const;
        Vec2f& operator-=(const Vec2f& other); 

        Vec2f operator*(float scalar) const;
        friend Vec2f operator*(float scalar, const Vec2f& vec);
        Vec2f& operator *=(float scalar);

        Vec2f operator/(float scalar) const;
        friend Vec2f operator/(float scalar, const Vec2f& vec);
        Vec2f& operator /=(float scalar);

        bool operator==(Vec2f other) const;
        bool operator!=(Vec2f other) const;

        float length() const;
        Vec2f normalized() const;
        Vec2f rotated(float angle) const; // Rotate clockwise

        // Cast to SFML vector
        explicit operator sf::Vector2f() const;
};