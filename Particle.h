#ifndef PARTICLE
#define PARTICLE
#include "GravitySource.h"
#include "Parameters.h"
#include <iostream>

class Particle
{
    sf::CircleShape point;
    Eigen::Vector2d pos, vel, force;
    double mass;

    Eigen::Vector2d gravForce(GravitySource source);

public:
    Particle(double pos_x, double pos_y, double vel_x, double vel_y, double mass);

    void updatePos(std::vector<GravitySource> &sources, sf::RenderWindow &window);
};

#endif