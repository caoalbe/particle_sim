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

        Vec2f operator/(float scalar) const;
        friend Vec2f operator/(float scalar, const Vec2f& vec);

        bool operator==(Vec2f other) const;
        bool operator!=(Vec2f other) const;

        // Convert to SFML vector
        sf::Vector2f convert();
};