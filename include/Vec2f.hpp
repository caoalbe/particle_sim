#pragma once

class Vec2f {
    public:
        float x;
        float y;

        Vec2f(float x, float y);

        Vec2f operator*(float scalar);

        Vec2f operator+(Vec2f other) const;
        Vec2f operator-(Vec2f other) const;

        Vec2f operator*(double scalar) const;
        friend Vec2f operator*(double scalar, const Vec2f& vec);

        Vec2f operator/(double scalar) const;
        friend Vec2f operator/(double scalar, const Vec2f& vec);
};