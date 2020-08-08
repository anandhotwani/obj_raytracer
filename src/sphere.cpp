#include "../src/sphere.hpp"

bool Sphere::intersect(const Ray &r, SurfaceInteraction &interaction) const {
    
    Vector3f oc = r.o - this->center;
    float a = glm::length2(r.d);
    float half_b = glm::dot(oc, r.d);
    float c = glm::length2(oc) - radius * radius;
    float discriminant = half_b * half_b - a * c;
    
    if (discriminant > 0.0f) {
        float root = sqrt(discriminant);
        float temp = (-half_b - root) / a;
        if (temp < r.t_max && temp > r.t_min) {
            interaction.t = temp;
            interaction.p = r.o + interaction.t * r.d;
            Vector3f outward_normal = (interaction.p - center) / radius;  // Normalized by diving by radius
            interaction.set_face_normal(r, outward_normal);
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < r.t_max && temp > r.t_min) {
            interaction.t = temp;
            interaction.p = r.o + interaction.t * r.d;
            Vector3f outward_normal = (interaction.p - center) / radius;  // Normalized by diving by radius
            interaction.set_face_normal(r, outward_normal);
            return true;
        }
    }
    // No solutions
    return false;
}