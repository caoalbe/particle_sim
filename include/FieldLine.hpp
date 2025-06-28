#pragma once

class FieldLine {
    public:
        sf::Vector2f position;
        sf::Vector2f field;

        FieldLine(sf::Vector2f position);
        void update_field(sf::Vector2f electricField);
};