#ifndef TRIANGLEMESH_HPP
#define TRIANGLEMESH_HPP

#include "../src/triangle.hpp"
#include "../external/tiny_obj_loader.h"
#include <iostream>
#include <vector>


class TriangleMesh : public Shape {
public:
    TriangleMesh(const char *filepath);
    bool intersect(const Ray& r, SurfaceInteraction &interaction) const override;
public:
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::vector<std::shared_ptr<Triangle> > tris;
};


#endif