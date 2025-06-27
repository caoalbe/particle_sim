#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include "FieldLine.hpp"
#include "Simulator.hpp"


int main() {
    // Create the main window
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "particle sim");
    window.setFramerateLimit(120);
    sf::Clock clock;

    // Setup conditions of simulator
    std::vector<Particle> p_list = { 
        // mass, charge (microcoloumb), position (cm), velocity (cm/s)
        // Particle(2.0f, -5.0f, sf::Vector2f(400.0f, 300.0f), sf::Vector2f(2.0f, 2.0f)),
        // Particle(3.0f, 3.0f, sf::Vector2f(550.0f, 275.0f), sf::Vector2f(0.0f, -5.0f)),
        // Particle(1.0f, 2.0f, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(-9.0f, 0.0f)),

        // identifier, mass, charge (microcoloumb), position (cm), velocity (cm/s)
        // Particle(1, 100.0f, -500.0f, sf::Vector2f(400.0f, 300.0f), sf::Vector2f(5.0f, 5.0f)),
        // Particle(2, 0.75f, 1.0f, sf::Vector2f(500.0f, 300.0f), sf::Vector2f(0.0f, -15.0f))

        // identifier, mass, charge (microcoloumb), position (cm), velocity (cm/s)
        // Particle(1, 2.0f, 50.0f, sf::Vector2f(200.0f,400.0f), sf::Vector2f(10.0f, -5.0f)),
        // Particle(2, 1.0f, -50.0f, sf::Vector2f(500.0f,300.0f), sf::Vector2f(-20.0f, 1.0f)),
        // Particle(3, 0.4f, 35.0f, sf::Vector2f(100.0f,500.0f), sf::Vector2f(30.0f, 9.0f)),
        // Particle(4, 1.3f, 40.0f, sf::Vector2f(700.0f,500.0f), sf::Vector2f(-5.0f, -4.50f)),
        // Particle(5, 1.5f, -35.0f, sf::Vector2f(700.0f,100.0f), sf::Vector2f(10.0f, 2.50f)),

        // mass, charge (microcoloumb), position (cm), velocity (cm/s)
        Particle(100.0f, 100.0f, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(45.0f, 0.0f), false), // EARTH
        Particle(0.5f, -10.0f, sf::Vector2f(100.0f - 75.0f, 300.0f), sf::Vector2f(45.0f, 489.559033858f)), // MOON
    };

    std::vector<FieldLine> f_list;
    f_list.reserve(80*60);
    for (int x = 5; x < 800; x+=15) {
        for (int y = 5; y < 600; y+=15) {
            f_list.push_back(FieldLine(sf::Vector2f(x, y)));
        }
    }

    Simulator sim = Simulator(p_list, f_list);

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
        float dt = clock.restart().asSeconds();

        // Physics engine
        sim.update(dt);

        // Draw graphics
        window.clear();
        for (const FieldLine& field : sim.field_list) {
            window.draw(field.line_data, 2, sf::PrimitiveType::Lines);
        }

        for (const Particle& particle : sim.particle_list) {
            window.draw(particle.sprite);
        }
        window.display();

    }

    return 0;
}