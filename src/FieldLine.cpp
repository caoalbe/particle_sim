#include "FieldLine.hpp"
#include "Vec2f.hpp"

FieldLine::FieldLine(Vec2f position) : position(position) {
    field = Vec2f(0.0f, 0.0f);
}

void FieldLine::update_field(Vec2f electricField) {
    field = electricField;
}