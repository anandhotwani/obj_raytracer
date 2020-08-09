#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../src/math.hpp"

class Camera {
public:
    Camera(uint32_t _width, uint32_t _height, float _fov, Matrix4x4f _c2w);
    Ray get_ray(float u, float v);
    
public:
    uint32_t width;
    uint32_t height;
    float fov;
    Matrix4x4f c2w;
    float scale;
    float image_aspect_ratio;
};


#endif
