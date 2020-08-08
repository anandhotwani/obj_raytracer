#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../src/math.hpp"

class Shape {
public:
    virtual bool intersect(const Ray& r, SurfaceInteraction& interaction) const = 0;
};

#endif