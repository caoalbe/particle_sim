#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "Particle.hpp"
#include "FieldLine.hpp"
#include "Simulator.hpp"
#include "Vec2f.hpp"
#include "args.hpp"

const float pi = 3.1415926535;

int main(int argc, char* argv[]) {
    // Parse command line flags
    ParsedArgs args = ParsedArgs(argc, argv);
    if (args.help) { args.print_usage(); }
    if (args.error_output) { return 1; }
    if (args.help) { return 0; }

    // Create the main window
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "Particle Engine");
    window.setFramerateLimit(120);
    sf::Clock clock;

    // Setup conditions of simulator
    std::vector<Particle> p_list;
    p_list.reserve(10);
    if (args.sim_setup == SimulationSetup::Circular) {
        // mass, charge (microcoloumb), position (cm), velocity (cm/s)
        p_list.push_back(Particle(1000000.0f, 100.0f, Vec2f(400.0f, 300.0f), Vec2f(0.0f, 0.0f)));
        p_list.push_back(Particle(0.5f, -10.0f, Vec2f(400.0f - 75.0f, 300.0f), Vec2f(0.0f, 489.559033858f)));
    } else if (args.sim_setup == SimulationSetup::CircularMoving) {
        p_list.push_back(Particle(1000000.0f, 100.0f, Vec2f(400.0f, 300.0f), Vec2f(15.0f, 0.0f)));
        p_list.push_back(Particle(0.5f, -10.0f, Vec2f(400.0f - 75.0f, 300.0f), Vec2f(15.0f, 489.559033858f)));
    } else if (args.sim_setup == SimulationSetup::Four) {
        p_list.push_back(Particle(10.0f, -35.0f, Vec2f(400.0f - 150.0f, 300.0f), Vec2f(10.0f, -35.0f)));
        p_list.push_back(Particle(10.0f, -45.0f, Vec2f(400.0f + 150.0f, 300.0f), Vec2f(0.0f, -50.0f)));
        p_list.push_back(Particle(5.0f, 25.0f, Vec2f(400.0f, 300.0f), Vec2f(0.0f, 30.0f)));
        p_list.push_back(Particle(15.0f, 45.0f, Vec2f(400.0f, 300.0f+75.0), Vec2f(-15.0f, -5.0f)));
    } else if (args.sim_setup == SimulationSetup::Random) {
        std::random_device rd;               // Seed source
        std::mt19937 gen(rd());              // Mersenne Twister engine
        std::uniform_real_distribution<> dis(0.0, 1.0); // [0.0, 1.0)

        int negative_count = 0;
        int positive_count = 0;
        float charge;
        for (int p = 0; p < 10; p++) {
            if (p == 0) {
                charge = (float) dis(gen) * 75 - 37.5f;
            } else {
                charge = dis(gen) * 75;
                charge -= (float) positive_count / p * 75;
            }
            if (charge > 0) { positive_count++; }
            else if (charge < 0) { negative_count++; }

            p_list.push_back(Particle(
                dis(gen) * 5,
                charge,
                Vec2f(dis(gen) * 300 + 250, dis(gen) * 200 + 200),
                Vec2f(dis(gen) * 60 - 30, dis(gen) * 60 - 30)
            ));
        }
    } else if (args.sim_setup == SimulationSetup::Input) {
        // TODO: Text input for
    }

    std::vector<FieldLine> f_list;
    if (!args.ignore_field) {
        f_list.reserve(80*60);
        for (int x = 0; x < 800; x+=40) {
            for (int y = 0; y < 600; y+=40) {
                f_list.push_back(FieldLine(Vec2f(x, y)));
                f_list.push_back(FieldLine(Vec2f(x+20, y+20)));
            }
        }
    }

    Simulator sim = Simulator(p_list, f_list, 800, 600);

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