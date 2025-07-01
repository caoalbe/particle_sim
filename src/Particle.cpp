#include "Particle.hpp"
#include "Vec2f.hpp"

const float RADIUS_LOWER_BOUND = 3.0f;
const float RADIUS_UPPER_BOUND = 5.0f;
const float RADIUS_RANGE = RADIUS_UPPER_BOUND - RADIUS_LOWER_BOUND;
const float BOUNCE_DAMPEN_FACTOR = 0.35;

Particle::Particle(float mass, float charge, Vec2f position, Vec2f velocity, bool respondsToField, int id) 
    : id(id), respondsToField(respondsToField), mass(mass), charge(charge), position(position), velocity(velocity) {

    // TODO: Manage this error
    if (mass == 0) {}

    // Determine radius with sigmoid
    radius = RADIUS_LOWER_BOUND + RADIUS_RANGE/(1 + std::exp(-10*mass+5));
}

Particle::Particle(float mass, float charge, Vec2f position, Vec2f velocity, bool respondsToField) 
    : Particle::Particle(mass, charge, position, velocity, respondsToField, -1) {}

Particle::Particle(float mass, float charge, Vec2f position, Vec2f velocity) 
    : Particle::Particle(mass, charge, position, velocity, true, -1) {}

void Particle::update_position(float dt, int sim_width, int sim_height) {
    // Update position from velocity
    position = position + velocity * dt;

    // Prevent clipping
    if (position.x < radius) { position.x = radius; }
    if (position.x > sim_width - radius) { position.x = sim_width - radius; } 
    if (position.y < radius) { position.y = radius; }
    if (position.y > sim_height - radius) { position.y = sim_height - radius; }
}

void Particle::update_velocity(float dt, Vec2f force, int sim_width, int sim_height) {
    // Update velocity from force (centi-Newtons)
    if (respondsToField) {
        velocity = velocity + force*dt/mass;
    }

    // Bounce off walls
    if (position.x <= radius || position.x >= sim_width - radius) { 
        velocity *= BOUNCE_DAMPEN_FACTOR; 
        velocity.x *= -1;
    }
    if (position.y <= radius || position.y >= sim_height - radius) { 
        velocity *= BOUNCE_DAMPEN_FACTOR; 
        velocity.y *= -1; 
    }
}