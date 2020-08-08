#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../src/shape.hpp"

class Sphere: public Shape {
public:
    Sphere() {}
    Sphere(Vector3f c, float r) : center(c), radius(r) {};
    
    virtual bool intersect(const Ray& r, SurfaceInteraction& interaction) const;
public:
    Vector3f center;
    float radius;
};

#endif