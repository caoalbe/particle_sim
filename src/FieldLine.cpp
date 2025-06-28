#include <SFML/Graphics.hpp>
#include "FieldLine.hpp"

FieldLine::FieldLine(sf::Vector2f position) : position(position) {
    field = sf::Vector2f(0.0f, 0.0f);
}

void FieldLine::update_field(sf::Vector2f electricField) {
    field = electricField;
}