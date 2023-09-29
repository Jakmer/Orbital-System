#include "GravitySource.h"

GravitySource::GravitySource(double pos_x, double pos_y, double mass) : mass(mass)
{
    pos(0) = pos_x;
    pos(1) = pos_y;

    point.setRadius(20);
    point.setPosition(pos(0), pos(1));
    point.setFillColor(sf::Color::White);
}

double GravitySource::getMass() const
{
    return mass;
}

Eigen::Vector2d GravitySource::getPos()
{
    return pos;
}

void GravitySource::render(sf::RenderWindow &window) const
{
    window.draw(point);
}