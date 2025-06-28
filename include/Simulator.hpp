#pragma once
#include "Particle.hpp"
#include "FieldLine.hpp"

// Represents the world space
class Simulator {
    public:
        int particle_count;
        int field_count;

        std::vector<Particle> particle_list;
        std::vector<FieldLine> field_list;

        Simulator(std::vector<Particle> particles, std::vector<FieldLine> field_lines);
        sf::Vector2f compute_field(sf::Vector2f target);
        void update(float dt);
};