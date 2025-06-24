#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

const float k_e = 89.875517862000; // N cm^2 / µC^2
const float pi = 3.141592653589;

class Particle {
    public:
        int id;
        float radius;
        float mass; // kg
        float charge; // microcoloumb
        sf::Vector2f position; // cm
        sf::Vector2f velocity; // cm/s
        sf::CircleShape sprite;

        Particle(int id, float mass, float charge, sf::Vector2f position, sf::Vector2f velocity) 
            : id(id), charge(charge), position(position), velocity(velocity) {
            
            radius = std::sqrt(100 * mass/pi);
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

        void update_position(float dt) {
            // Update position from velocity
            position = position + velocity * dt;
            sprite.setPosition(position );
            sprite.move(sf::Vector2f(-radius, -radius));  
        }

        void update_velocity(float dt, sf::Vector2f accel) {
            // Update velocity from acceleration
            velocity = velocity + accel*dt;
        }
};

class Simulator {
    public:
        std::vector<Particle> particle_list;

        Simulator(std::vector<Particle> particles) 
            : particle_list(particles) {}

        sf::Vector2f compute_field(sf::Vector2f target) {
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

        void update(float dt) {
            for (Particle& particle : particle_list) {
                // particle.charge * compute_field is Newtons
                particle.update_velocity(dt, particle.charge * compute_field(particle.position));
            }

            for (Particle& particle : particle_list) {
                particle.update_position(dt);
            }
        }
};

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "particle sim");
    sf::Clock clock;

    // Setup conditions of simulator
    std::vector<Particle> p_list = { 
        // identifier, mass, charge (microcoloumb), position (cm), velocity (cm/s)
        Particle(1, 1.0f, 50.0f, sf::Vector2f(400.0f, 300.0f), sf::Vector2f(0.0f, 0.0f)),
        Particle(2, 1.0f, -30.0f, sf::Vector2f(500.0f, 300.0f), sf::Vector2f(0.0f, 0.0f)),
        Particle(3, 1.0f, -20.0f, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(0.0f, 0.0f))
    };
    Simulator sim = Simulator(p_list);

    // Start the simulation loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // Get elapsed time
        float dt = clock.restart().asSeconds(); // NOTE: Varying dt yields varying sims

        // Physics engine
        sim.update(dt);

        // Draw graphics
        window.clear();
        for (const Particle& particle : sim.particle_list) {
            window.draw(particle.sprite);
        }
        window.display();

    }

    return 0;
}