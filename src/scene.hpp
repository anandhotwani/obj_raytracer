#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include "../src/shape.hpp"

class Scene : public Shape {
public:
    Scene() {}
    Scene(std::shared_ptr<Shape> object) { Add(object); }
    
    void Clear();
    void Add(std::shared_ptr<Shape> object);
    
    virtual bool intersect(const Ray& r, SurfaceInteraction &interaction) const;
    
public:
    std::vector<std::shared_ptr<Shape> > objects;
};

#endif