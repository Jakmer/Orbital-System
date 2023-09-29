#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "Parameters.h"
#include "GravitySource.h"
#include "Particle.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Orbital Gravity");
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<GravitySource> sources;
    sources.emplace_back(700, 400, SOURCE_MASS);

    std::vector<Particle> particles;
    particles.emplace_back(700, 600, 80, 30, PARTICLE_MASS);
    particles.emplace_back(500, 350, 20, 60, PARTICLE_MASS);
    particles.emplace_back(500, 350, 0, 80, PARTICLE_MASS);
    particles.emplace_back(700, 200, -70, 30, PARTICLE_MASS);

    for (const auto &i : sources)
    {
        i.render(window);
    }

    for (auto &i : particles)
    {
        i.updatePos(sources, window);
    }

    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (const auto &i : sources)
        {
            i.render(window);
        }

        for (auto &i : particles)
        {
            i.updatePos(sources, window);
        }

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP / 5)); // divide by 5 to speed up the visualization
    }

    return 0;
}