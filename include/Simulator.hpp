#pragma once
#include "Particle.hpp"
#include "FieldLine.hpp"
#include "Vec2f.hpp"

// Represents the world space
class Simulator {
    public:
        int particle_count;
        int field_count;
        int width;
        int height;

        std::vector<Particle> particle_list;
        std::vector<FieldLine> field_list;

        Simulator(std::vector<Particle> particles, std::vector<FieldLine> field_lines, int width, int height);
        Simulator(std::vector<Particle> particles, std::vector<FieldLine> field_lines);
        Vec2f compute_field(Vec2f target);
        void update(float dt);
};