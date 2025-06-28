#include <SFML/Graphics.hpp>
#include "Particle.hpp"

const float RADIUS_LOWER_BOUND = 3.0f;
const float RADIUS_UPPER_BOUND = 10.0f;
const float RADIUS_RANGE = RADIUS_UPPER_BOUND - RADIUS_LOWER_BOUND;

Particle::Particle(float mass, float charge, sf::Vector2f position, sf::Vector2f velocity, bool respondsToField, int id) 
    : id(id), respondsToField(respondsToField), mass(mass), charge(charge), position(position), velocity(velocity) {

    // TODO: Manage this error
    if (mass == 0) {}

    // Determine radius with sigmoid
    radius = RADIUS_LOWER_BOUND + RADIUS_RANGE/(1 + std::exp(-10*mass+5));
}

Particle::Particle(float mass, float charge, sf::Vector2f position, sf::Vector2f velocity, bool respondsToField) 
    : Particle::Particle(mass, charge, position, velocity, respondsToField, -1) {}

Particle::Particle(float mass, float charge, sf::Vector2f position, sf::Vector2f velocity) 
    : Particle::Particle(mass, charge, position, velocity, true, -1) {}

void Particle::update_position(float dt) {
    // Update position from velocity
    position = position + velocity * dt;

    // Prevent clipping
    if (position.x < radius) { position.x = radius; }
    if (position.x > 800 - radius) { position.x = 800 - radius; } 
    if (position.y < radius) { position.y = radius; }
    if (position.y > 600 - radius) { position.y = 600 - radius; }

    sprite.setPosition(position);
    sprite.move(sf::Vector2f(-radius, -radius));  
}

void Particle::update_velocity(float dt, sf::Vector2f force) {
    // Update velocity from force (Newtons)
    if (respondsToField) {
        velocity = velocity + force*dt/mass*100.0f;
    }

    // Bounce off walls
    if (position.x <= radius || position.x >= 800 - radius) { velocity.x *= -0.85; velocity.y *= 0.85; }
    if (position.y <= radius || position.y >= 600 - radius) { velocity.x *= 0.85; velocity.y *= -0.85; }
}