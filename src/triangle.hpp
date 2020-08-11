#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "../src/shape.hpp"

struct Vertex {
public:
    Vector3f P;
    Vector3f Ng;
    Vector2f UV;
};

class Triangle : public Shape {
public:
    Triangle(Vector3f _v0, Vector3f _v1, Vector3f _v2) {
        
        v0 = _v0;
        v1 = _v1;
        v2 = _v2;
        e1 = v1 - v0;
        e2 = v2 - v0;
        n = glm::normalize(glm::cross(e1, e2));
        
    }
    
    virtual bool intersect(const Ray& r, SurfaceInteraction &interaction) const;
public:
    Vector3f v0, v1, v2;
    Vector3f e1, e2;
    Vector3f n;
    float u, v;;
};

#endif