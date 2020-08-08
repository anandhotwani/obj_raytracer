#include "../src/scene.hpp"

void Scene::Clear() {
    objects.clear();
}

void Scene::Add(std::shared_ptr<Shape> object) {
    objects.push_back(object);
}

bool Scene::intersect(const Ray &r, SurfaceInteraction &interaction) const {
    
    SurfaceInteraction temp;
    bool any_hit = false;
    float t_near = r.t_max;
    
    for (const auto& object : objects) {
        if (object->intersect(r, temp)) {
            any_hit = true;
            t_near = temp.t;
            interaction = temp;
        }
    }
    return any_hit;
}