#pragma once

class FieldLine {
    public:
        sf::Vector2f position;
        sf::Vector2f field;

        FieldLine(sf::Vector2f position);
        void setElectricField(sf::Vector2f electricField);
};