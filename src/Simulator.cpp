#include "Simulator.hpp"
#include "Vec2f.hpp"

const float k_e = 89.875517862000; // N cm^2 per µC^2

Simulator::Simulator(std::vector<Particle> particles, std::vector<FieldLine> field_lines) 
    : particle_list(particles), field_list(field_lines), particle_count(particles.size()), field_count(field_lines.size()) {}

Vec2f Simulator::compute_field(Vec2f target) {
    Vec2f field = Vec2f(0.0f, 0.0f);
    Vec2f distance_vector;

    float length_squared;
    float force;
    for (Particle& particle : particle_list) {
        if (particle.position != target) {
            distance_vector = target - particle.position;
            length_squared = distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y;

            force = k_e * particle.charge / length_squared;
            field = field + force * distance_vector.normalized();
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
        field.update_field(compute_field(field.position));
    }
}