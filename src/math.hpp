#include <iostream>
#include <../include/glm/glm.hpp>

typedef glm::vec3 Vector3f;

class Ray {
public:
    Ray() {}
    Ray(const Vector3f& orig, const Vector3f& dir) : o(orig), d(dir) {}    
public:
    Vector3f o;
    Vector3f d;
};

inline float deg2rad(const float &deg) { return deg * M_PI / 180.0f; } 