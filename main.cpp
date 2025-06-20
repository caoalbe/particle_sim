#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Particle {
    public:
        sf::Vector2f velocity;
        sf::CircleShape sprite;

        Particle(float radius, sf::Vector2f position, sf::Vector2f velocity) 
            : sprite(radius), velocity(velocity) {
            sprite.setPosition(position);
        }

        void update(float dt, sf::Vector2f accel) {
            // Update position from velocity
            sprite.move(velocity * dt);

            // Update velocity from acceleration
            velocity = velocity + accel*dt;
        }
};

class Simulator {
    public:
        std::vector<Particle> particle_list;
        // std::vector<sf::Vector2f> field_list;

        Simulator(std::vector<Particle> particles) 
            : particle_list(particles) {}

        // sf::Vector2f compute_field(sf::Vector2f position) {}

        void update(float dt) {
            for (Particle& particle : particle_list) {
                particle.update(dt, sf::Vector2f(0.0f, 30.0f));
            }
        }
};

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "particle sim");
    sf::Clock clock;

    // Setup conditions of simulator
    std::vector<Particle> p_list = { 
        Particle(10.0f, sf::Vector2f(50.0f, 500.0f), sf::Vector2f(500.0f, -50.0f)),
        Particle(5.0f, sf::Vector2f(200.0f, 25.0f), sf::Vector2f(-200.0f, 100.0f)) 
    };
    Simulator sim = Simulator(p_list);

    // Start the simulation loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Get elapsed time
        float dt = clock.restart().asSeconds();

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