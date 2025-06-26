#pragma once

class FieldLine {
    public:
        sf::Vector2f position;
        sf::Vertex line_data[2];

        FieldLine(sf::Vector2f position);
        void setElectricField(sf::Vector2f electricField);

    private:
        const float MAX_LENGTH = 10.0f; // Max length of field line
        const float MAX_LENGTH_SQUARED = MAX_LENGTH * MAX_LENGTH;
};