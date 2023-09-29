#include <iostream>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <thread>
#include <chrono>

const double G{6.67430}; // gravitational constant
const int TIME_STEP(50);     // milliseconds

class GravitySource
{
    sf::CircleShape point;
    double mass;
    Eigen::Vector2d pos;

public:
    GravitySource(double pos_x, double pos_y, double mass) : mass(mass)
    {
        pos(0) = pos_x;
        pos(1) = pos_y;

        point.setRadius(20);
        point.setPosition(pos(0), pos(1));
        point.setFillColor(sf::Color::White);
    }

    double getMass() const
    {
        return mass;
    }

    Eigen::Vector2d getPos()
    {
        return pos;
    }

    void render(sf::RenderWindow &window) const
    {
        window.draw(point);
    }
};

class Particle
{
    sf::CircleShape point;
    Eigen::Vector2d pos, vel, force;
    double mass;

    Eigen::Vector2d gravForce(GravitySource source)
    {
        Eigen::Vector2d r = source.getPos() - pos;

        double distance_sq = r.squaredNorm();

        Eigen::Vector2d force = r.normalized() * G * mass * source.getMass()/ distance_sq;

        return force;
    }

public:
    Particle(double pos_x, double pos_y, double vel_x, double vel_y, double mass) : mass(mass), force(0, 0), point(10)
    {
        pos(0) = pos_x;
        pos(1) = pos_y;

        vel(0) = vel_x;
        vel(1) = vel_y;

        point.setPosition(pos(0), pos(1));
        point.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    }

    void updatePos(std::vector<GravitySource> &sources, sf::RenderWindow &window)
    {
        force = {0,0};
        for (const auto &i : sources)
        {
            force += gravForce(i);
            std::cout << force(0) << " " << force(1) << "";
        }

        Eigen::Vector2d acc{force / mass};

        vel += acc * (TIME_STEP / 1000.0);

        pos += vel * (TIME_STEP / 1000.0);

        point.setPosition(pos(0), pos(1));

        std::cout<<"    X:"<<pos(0)<<" Y:"<<pos(1)<<"\n";

        window.draw(point);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Orbital Gravity");
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<GravitySource> sources;
    sources.emplace_back(700, 400, 158800);

    std::vector<Particle> particles;
    particles.emplace_back(700, 600, 80, 30, 5.98);
    particles.emplace_back(500, 350, 20, 60, 5.98);
    particles.emplace_back(500, 350, 0, 80, 5.98);
    particles.emplace_back(700, 200, -70, 30, 5.98);

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

        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP/4));
    }

    return 0;
}