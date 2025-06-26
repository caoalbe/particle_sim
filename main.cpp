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
            : id(id), mass(mass), charge(charge), position(position), velocity(velocity) {
            
            if (mass == 0) {
                // TODO: Manage this error
            }

            // Determine radius with sigmoid
            radius = 3/(1 + std::exp(-10*mass+5))+ 5.0f;
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

        void update_velocity(float dt, sf::Vector2f force) {
            // Update velocity from force (Newtons)
            velocity = velocity + force*dt/mass;
        }
};

class FieldLine {
    public:
        sf::Vector2f position;
        sf::Vertex line_data[2];

        FieldLine(sf::Vector2f position) : position(position) {
            line_data[0].position = position;
            line_data[0].color = sf::Color::Yellow;
            line_data[1].position = position;
            line_data[1].color = sf::Color::Yellow;
        }

        void setElectricField(sf::Vector2f electricField) {
            float length_squared = electricField.x * electricField.x + electricField.y * electricField.y;
            if (length_squared > MAX_LENGTH_SQUARED) {
                electricField = electricField / std::sqrt(length_squared) * MAX_LENGTH;
            }
            line_data[1].position = position + 3.0f * electricField;
        }

    private:
        const float MAX_LENGTH = 10.0f; // Max length of field line
        const float MAX_LENGTH_SQUARED = MAX_LENGTH * MAX_LENGTH;
};

class Simulator {
    public:
        std::vector<Particle> particle_list;
        std::vector<FieldLine> field_list;

        Simulator(std::vector<Particle> particles, std::vector<FieldLine> field_lines) 
            : particle_list(particles), field_list(field_lines) {}

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

            for (FieldLine& field : field_list) {
                field.setElectricField(compute_field(field.position));
            }
        }
};

int main() {
    // Create the main window
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "particle sim");
    window.setFramerateLimit(120);
    sf::Clock clock;

    // Setup conditions of simulator
    std::vector<Particle> p_list = { 
        // identifier, mass, charge (microcoloumb), position (cm), velocity (cm/s)
        Particle(1, 2.0f, -50.0f, sf::Vector2f(400.0f, 300.0f), sf::Vector2f(5.0f, 5.0f)),
        Particle(2, 3.0f, 30.0f, sf::Vector2f(550.0f, 300.0f), sf::Vector2f(0.0f, -10.0f)),
        Particle(3, 1.0f, 20.0f, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(-9.0f, 0.0f)),
        Particle(3, 1.0f, -10.0f, sf::Vector2f(250.0f, 150.0f), sf::Vector2f(-9.0f, 0.0f))
    };
    // std::vector<Particle> p_list = { 
    //     // identifier, mass, charge (microcoloumb), position (cm), velocity (cm/s)
    //     Particle(1, 100.0f, -500.0f, sf::Vector2f(400.0f, 300.0f), sf::Vector2f(5.0f, 5.0f)),
    //     Particle(2, 0.75f, 1.0f, sf::Vector2f(500.0f, 300.0f), sf::Vector2f(0.0f, -15.0f))
    // };
    std::vector<FieldLine> f_list = {};
    for (int x = 15; x < 800; x+=10) {
        for (int y = 15; y < 600; y+=10) {
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