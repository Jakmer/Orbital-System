#include "Particle.h"

Eigen::Vector2d Particle::gravForce(GravitySource source)
{
    Eigen::Vector2d r = source.getPos() - pos;

    double distance_sq = r.squaredNorm();

    Eigen::Vector2d force = r.normalized() * G * mass * source.getMass() / distance_sq;

    return force;
}

Particle::Particle(double pos_x, double pos_y, double vel_x, double vel_y, double mass) : mass(mass), force(0, 0), point(10)
{
    pos(0) = pos_x;
    pos(1) = pos_y;

    vel(0) = vel_x;
    vel(1) = vel_y;

    point.setPosition(pos(0), pos(1));
    point.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}

void Particle::updatePos(std::vector<GravitySource> &sources, sf::RenderWindow &window)
{
    force = {0, 0};
    for (const auto &i : sources)
    {
        force += gravForce(i);
        std::cout << force(0) << " " << force(1) << "";
    }

    Eigen::Vector2d acc{force / mass};

    vel += acc * (TIME_STEP / 1000.0);

    pos += vel * (TIME_STEP / 1000.0);

    point.setPosition(pos(0), pos(1));

    std::cout << "    X:" << pos(0) << " Y:" << pos(1) << "\n";

    window.draw(point);
}