#pragma once
#include "Vec2f.hpp"

class FieldLine {
    public:
        Vec2f position;
        Vec2f field;

        FieldLine(Vec2f position);
        void update_field(Vec2f electricField);
};