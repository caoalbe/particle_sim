#include "Simulator.hpp"
#include "Vec2f.hpp"

const float k_e = 8987.5517862000; // cN cm^2 per µC^2

// TODO: Support inserting particles and field lines
Simulator::Simulator(std::vector<Particle> particles, std::vector<FieldLine> field_lines, int width, int height)
    : particle_list(particles), field_list(field_lines), particle_count(particles.size()), field_count(field_lines.size()), width(width), height(height) {}


Simulator::Simulator(std::vector<Particle> particles, std::vector<FieldLine> field_lines) 
    : particle_list(particles), field_list(field_lines), particle_count(particles.size()), field_count(field_lines.size()), width(800), height(600) {}

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
    return field; // centi-newtons per microcoloumb
}

void Simulator::update(float dt) {
    for (Particle& particle : particle_list) {
        // particle.charge * compute_field is centi-Newtons
        particle.update_velocity(dt, particle.charge * compute_field(particle.position), width, height);
    }

    for (Particle& particle : particle_list) {
        particle.update_position(dt, width, height);
    }

    for (FieldLine& field : field_list) {
        field.update_field(compute_field(field.position));
    }
}