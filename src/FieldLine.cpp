#include <SFML/Graphics.hpp>
#include "FieldLine.hpp"

FieldLine::FieldLine(sf::Vector2f position) : position(position) {
    line_data[0].position = position;
    line_data[0].color = sf::Color::Yellow;
    line_data[1].position = position;
    line_data[1].color = sf::Color::Yellow;
}

void FieldLine::setElectricField(sf::Vector2f electricField) {
    float length_squared = electricField.x * electricField.x + electricField.y * electricField.y;
    if (length_squared > MAX_LENGTH_SQUARED) {
        electricField = electricField / std::sqrt(length_squared) * MAX_LENGTH;
    }
    line_data[1].position = position + 3.0f * electricField;
}