#pragma once

class Particle {
    public:
        int id;
        bool respondsToField;
        float radius;
        float mass; // kg
        float charge; // microcoloumb
        sf::Vector2f position; // cm
        sf::Vector2f velocity; // cm/s
        sf::CircleShape sprite;

        Particle(float mass, float charge, sf::Vector2f position, sf::Vector2f velocity, bool respondsToField, int id);
        Particle(float mass, float charge, sf::Vector2f position, sf::Vector2f velocity, bool respondsToField);
        Particle(float mass, float charge, sf::Vector2f position, sf::Vector2f velocity);
        void update_position(float dt);
        void update_velocity(float dt, sf::Vector2f);
};