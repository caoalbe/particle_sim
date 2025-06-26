#include <SFML/Graphics.hpp>
#include "Simulator.hpp"

const float k_e = 89.875517862000; // N cm^2 / µC^2

Simulator::Simulator(std::vector<Particle> particles, std::vector<FieldLine> field_lines) 
    : particle_list(particles), field_list(field_lines) {}

sf::Vector2f Simulator::compute_field(sf::Vector2f target) {
    sf::Vector2f field = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f distance_vector;

    float distance_squared;
    float distance;
    float force;
    for (Particle& particle : particle_list) {
        if (particle.position != target) {
            distance_vector = target - particle.position;
            distance_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;
            distance = std::sqrt(distance_squared);
            distance_vector = distance_vector / distance; // distance_vector is normalized

            force = k_e * particle.charge / distance_squared;
            field = field + force*distance_vector;
        }
    }
    return field; // newtons per microcoloumb
}

void Simulator::update(float dt) {
    for (Particle& particle : particle_list) {
        // particle.charge * compute_field is Newtons
        particle.update_velocity(dt, particle.charge * compute_field(particle.position));
    }

    for (Particle& particle : particle_list) {
        particle.update_position(dt);
    }

    for (FieldLine& field : field_list) {
        field.setElectricField(compute_field(field.position));
    }
}