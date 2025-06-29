#pragma once
#include "Vec2f.hpp"

class Particle {
    public:
        int id;
        bool respondsToField;
        float radius;
        float mass; // kg
        float charge; // microcoloumb
        Vec2f position; // cm
        Vec2f velocity; // cm/s

        Particle(float mass, float charge, Vec2f position, Vec2f velocity, bool respondsToField, int id);
        Particle(float mass, float charge, Vec2f position, Vec2f velocity, bool respondsToField);
        Particle(float mass, float charge, Vec2f position, Vec2f velocity);
        void update_position(float dt);
        void update_velocity(float dt, Vec2f);
};