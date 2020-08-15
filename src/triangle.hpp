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
    Triangle(Vertex _v0, Vertex _v1, Vertex _v2) {
        
        v0 = _v0.P;
        v1 = _v1.P;
        v2 = _v2.P;
        e1 = v1 - v0;
        e2 = v2 - v0;
        n = glm::normalize(glm::cross(e1, e2)); // Eventually change so it interpolates between vertex normals

        uv[0] = _v0.UV;
        uv[1] = _v1.UV;
        uv[2] = _v2.UV;

        N[0] = _v0.Ng;
        N[1] = _v1.Ng;
        N[2] = _v2.Ng;
        
    }
    
    virtual bool intersect(const Ray& r, SurfaceInteraction &interaction) const;
    Vector3f get_barycentric(Vector3f& p) const;
public:
    Vector3f v0, v1, v2;
    Vector3f e1, e2;
    Vector3f n;
    Vector3f N[3];
    Vector2f uv[3];
};

#endif