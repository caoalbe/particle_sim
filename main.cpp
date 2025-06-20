#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Simulator {
    public:
        std::vector<Particle> particle_list;

        Simulator(std::vector<Particle> particles) 
            : particle_list(particles) {}

            
        sf::Vector2f compute_field(sf::Vector2f position) {}

        void update(float dt) {}
}

class Particle {
    public:
        sf::Vector2f velocity;
        sf::CircleShape sprite;

        Particle(float radius, sf::Vector2f position, sf::Vector2f velocity) 
            : sprite(radius), velocity(velocity) {
            sprite.setPosition(position);
        }

        void update(float dt) {
            // Update position from velocity
            sprite.move(velocity * dt);

            // Update velocity from acceleration
            velocity.y = velocity.y + 0.05f;
        }
};

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "particle sim");
    sf::Clock clock;

    std::vector<Particle> particle_list = { 
        Particle(10.0f, sf::Vector2f(50.0f, 500.0f), sf::Vector2f(500.0f, -50.0f)),
        Particle(5.0f, sf::Vector2f(200.0f, 25.0f), sf::Vector2f(-200.0f, 100.0f)) 
    };

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
        for (Particle& particle : particle_list) {
            particle.update(dt);
        }

        // Draw graphics
        window.clear();
        for (const Particle& particle : particle_list) {
            window.draw(particle.sprite);
        }
        window.display();

    }

    return 0;
}