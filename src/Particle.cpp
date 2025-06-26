#include <SFML/Graphics.hpp>
#include "Particle.hpp"

Particle::Particle(int id, float mass, float charge, sf::Vector2f position, sf::Vector2f velocity) 
    : id(id), mass(mass), charge(charge), position(position), velocity(velocity) {
    
    if (mass == 0) {
        // TODO: Manage this error
    }

    // Determine radius with sigmoid
    radius = 3/(1 + std::exp(-10*mass+5))+ 3.5f;
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
    sprite.setPosition(position );
    sprite.move(sf::Vector2f(-radius, -radius));  
}

void Particle::update_velocity(float dt, sf::Vector2f force) {
    // Update velocity from force (Newtons)
    velocity = velocity + force*dt/mass;

    // Bounce off walls
    if (position.x < radius || position.x > 800 - radius) {
        velocity.x *= -0.95;
    }
    if (position.y < radius || position.y > 600 - radius) {
        velocity.y *= -0.95;
    }
}