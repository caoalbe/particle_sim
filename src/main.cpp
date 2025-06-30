#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include "FieldLine.hpp"
#include "Simulator.hpp"
#include "Vec2f.hpp"


const float pi = 3.1415926535;

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
        Particle(100.0f, 100.0f, Vec2f(100.0f, 300.0f), Vec2f(45.0f, 0.0f), false), // EARTH
        Particle(0.5f, -10.0f, Vec2f(100.0f - 75.0f, 300.0f), Vec2f(45.0f, 489.559033858f)), // MOON

        // Particle(10.0f, 0.0f, sf::Vector2f(10.0f, 10.0f), sf::Vector2f(0.0f, 0.0f)),
    };

    std::vector<FieldLine> f_list;
    f_list.reserve(80*60);
    for (int x = 0; x < 800; x+=20) {
        for (int y = 0; y < 600; y+=20) {
            f_list.push_back(FieldLine(Vec2f(x, y)));
            f_list.push_back(FieldLine(Vec2f(x+10, y+10)));
        }
    }

    Simulator sim = Simulator(p_list, f_list);

    // Setup sprite data for graphics library
    sf::CircleShape particle_sprite;

    sf::Vertex line_data[6];
    Vec2f tip_vec;
    const float MAX_ARROW_LENGTH = 25.0f;
    const float MIN_ARROW_LENGTH = 2.5f;
    const float ARROW_TIP_PROPORTION = 0.45; 
    const float ARROW_TIP_ANGLE = 15 * (pi / 180);
    line_data[0].color = sf::Color::Yellow;
    line_data[1].color = sf::Color::Yellow;
    line_data[2].color = sf::Color::Yellow;
    line_data[3].color = sf::Color::Yellow;
    line_data[4].color = sf::Color::Yellow;
    line_data[5].color = sf::Color::Yellow;

    // Start the simulation loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close(); // Close window: exit
        }

        float dt = clock.restart().asSeconds(); // Get elapsed time

        sim.update(dt); // Physics engine

        // Draw graphics
        window.clear();

        for (FieldLine& field_line : sim.field_list) {
            if (field_line.field.length() < MIN_ARROW_LENGTH) { continue; }

            // Main field line
            line_data[0].position = static_cast<sf::Vector2f>(field_line.position);
            if (field_line.field.length() > MAX_ARROW_LENGTH) { 
                line_data[1].position = static_cast<sf::Vector2f>(
                                            field_line.position + MAX_ARROW_LENGTH * field_line.field.normalized());
                tip_vec = field_line.field.normalized() * MAX_ARROW_LENGTH * ARROW_TIP_PROPORTION;
            } else {
                line_data[1].position = static_cast<sf::Vector2f>(
                                            field_line.position + field_line.field);
                tip_vec = field_line.field * ARROW_TIP_PROPORTION;
            }

            // Left tip of field line
            line_data[2].position = line_data[1].position;
            line_data[3].position = line_data[2].position + static_cast<sf::Vector2f>(tip_vec.rotated(pi - ARROW_TIP_ANGLE));
            
            // Right tip of field line
            line_data[4].position = line_data[1].position;
            line_data[5].position = line_data[4].position + static_cast<sf::Vector2f>(tip_vec.rotated(pi + ARROW_TIP_ANGLE));

            window.draw(line_data, 6, sf::PrimitiveType::Lines);
        }

        for (Particle& particle : sim.particle_list) {
            if (particle.charge == 0.0f) { particle_sprite.setFillColor(sf::Color(255, 255, 255, 255)); }
            else if (particle.charge < 0.0f) { particle_sprite.setFillColor(sf::Color(0, 0, 255, 255)); }
            else { particle_sprite.setFillColor(sf::Color(255, 0, 0, 255)); }

            particle_sprite.setRadius(particle.radius);
            particle_sprite.setPosition(static_cast<sf::Vector2f>(particle.position - Vec2f(particle.radius, particle.radius)));
            
            window.draw(particle_sprite);
        }

        window.display();

    }

    return 0;
}