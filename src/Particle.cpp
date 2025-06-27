#include <SFML/Graphics.hpp>
#include "Particle.hpp"

const float RADIUS_LOWER_BOUND = 3.0f;
const float RADIUS_UPPER_BOUND = 10.0f;
const float RADIUS_RANGE = RADIUS_UPPER_BOUND - RADIUS_LOWER_BOUND;

Particle::Particle(int id, bool respondsToField,float mass, float charge, sf::Vector2f position, sf::Vector2f velocity) 
    : id(id), respondsToField(respondsToField), mass(mass), charge(charge), position(position), velocity(velocity) {
    
    if (mass == 0) {
        // TODO: Manage this error
    }

    // Determine radius with sigmoid
    radius = RADIUS_LOWER_BOUND + RADIUS_RANGE/(1 + std::exp(-10*mass+5));
    sprite = sf::CircleShape(radius);

    sf::Color spriteColor;
    if (charge == 0.0f) {
        spriteColor = sf::Color(255, 255, 255, 255);
    } else if (charge < 0) {
        spriteColor = sf::Color(0,0,255,255);
    } else {
        spriteColor = sf::Color(255,0,0,255);
    }
    sprite.setFillColor(spriteColor);
    sprite.setPosition(position);
}

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
        velocity = velocity + force*dt/mass;
    }

    // Bounce off walls
    if (position.x <= radius || position.x >= 800 - radius) { velocity.x *= -0.85; velocity.y *= 0.85; }
    if (position.y <= radius || position.y >= 600 - radius) { velocity.y *= -0.85; velocity.x *= 0.85; }
}