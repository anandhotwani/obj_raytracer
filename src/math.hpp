#ifndef MATH_HPP
#define MATH_HPP

#include <../include/glm/glm.hpp>
#include <../include/glm/gtx/norm.hpp>
#include <memory>

typedef glm::vec3 Vector3f;

class Ray {
public:
    Ray() {}
    Ray(const Vector3f& orig, const Vector3f& dir, const float& tmin, const float& tmax) : o(orig), d(dir), t_min(tmin), t_max(tmax) {}    
public:
    Vector3f o;
    Vector3f d;
    float t_min;
    float t_max;

};

struct SurfaceInteraction {
    Vector3f p;             // Intersection point
    Vector3f Ng;            // Geometric normal
    float t;                // Distance along ray for intersection
    bool front_facing;      // Determine if normal is aligned with ray (or against)

    inline void set_face_normal(const Ray& r, const Vector3f& outward_normal) {
        front_facing = glm::dot(r.d, outward_normal) < 0.0f;
        Ng = front_facing ? outward_normal : -outward_normal;       
    }
};

inline float deg2rad(const float &deg) { return deg * M_PI / 180.0f; } 

#endif