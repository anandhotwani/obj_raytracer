#ifndef MATH_HPP
#define MATH_HPP

#include <../include/glm/glm.hpp>
#include <../include/glm/gtx/string_cast.hpp>
#include <../include/glm/gtx/norm.hpp>
#include <memory>

// Vector3 and Matrix4x4 setup
typedef glm::vec3 Vector3f;
typedef glm::vec4 Vector4f;
typedef glm::mat4 Matrix4x4f;

// Useful functions for transforming points and directions using matrices
inline Vector3f TransformDirMatrix(const Matrix4x4f &x, const Vector3f &src) {
    
    Vector3f dst;
    Vector4f temp = glm::normalize(x * Vector4f(src, 0.0f));
    
    dst.x = temp.x;
    dst.y = temp.y;
    dst.z = temp.z;
    
    return dst;
}

inline Vector3f TransformPointMatrix(const Matrix4x4f &x, const Vector3f &src) {
    
    Vector3f dst;
    Vector4f temp = x * Vector4f(src, 1.0f);
    
    dst.x = temp.x;
    dst.y = temp.y;
    dst.z = temp.z;
    
    return dst;
}

// Basic ray functionality
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

// To store interaction information
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

// Common math functions
inline float deg2rad(const float &deg) { return deg * M_PI / 180.0f; } 

#endif