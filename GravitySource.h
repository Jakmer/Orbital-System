#ifndef GRAVITY_SOURCE
#define GRAVITY_SOURCE

#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>

class GravitySource
{
    sf::CircleShape point;
    double mass;
    Eigen::Vector2d pos;

public:
    GravitySource(double pos_x, double pos_y, double mass);

    double getMass() const;

    Eigen::Vector2d getPos();

    void render(sf::RenderWindow &window) const;
};

#endif