#include <iostream>
#include <fstream>
#include <chrono>
#include "../src/math.hpp"

struct Options {
    uint32_t width;
    uint32_t height;
    float fov;
};

float ray_sphere_intersection(const Vector3f& center, float radius, const Ray& r) {
    Vector3f oc = r.o - center;
    float a = glm::dot(r.d, r.d);
    float b = 2.0f * glm::dot(oc, r.d);
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0.0f) {
        return -1.0f;
    } else {
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}

Vector3f cast_ray(const Ray& r) {
    float hit = ray_sphere_intersection(Vector3f(0.0f, 0.0f, -1.0f), 0.5f, r);
    if (hit > 0.0f) {
        Vector3f normal = glm::normalize((r.o + hit * r.d) - Vector3f(0.0f, 0.0f, -1.0f));
        return Vector3f(glm::dot(normal, -r.d));
    }
    float t = 0.5f * (r.d.y + 1.0f);
    return Vector3f(0.44f);//lerp(Vector3f(1.0f, 1.0f, 1.0f), Vector3f(0.5f, 0.7f, 1.0f), t);
}

int main() {
    
    Options options;
    options.width   = 1024;
    options.height  = 429;
    options.fov     = 130.0f;

    std::ofstream ofs("OUT.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << options.width << " " << options.height << "\n255\n";

    float scale = tan(deg2rad(options.fov * 0.5f));
    float image_aspect_ratio = options.width / (float)options.height;
    
    // Time keeping
    auto start = std::chrono::system_clock::now();
    std::cout<<"Rendering image ... \n";
    for (uint32_t j = 0; j < options.height; ++j) {
        std::cout<<"Scanlines remaining : "<<options.height - j<<"\n";
        for (uint32_t i = 0; i < options.width; ++i) {
//            float u = float(j) / float(options.height);
//            float v = float(i) / float(options.width);
            float u = (2.0f * (i + 0.5f) / (float)options.width - 1.0f) * scale;
            float v = (1.0f - 2.0f * (j + 0.5f) / (float)options.height) * scale * 1.0f / image_aspect_ratio;
            //Vector3f colour = Vector3f(u, v, 0.18f);
            Ray ray = Ray(Vector3f(0.0f), Vector3f(u, v, -1.0f));
            Vector3f colour = cast_ray(ray);
            
            char r = (char)(255.99f * colour.x);
            char g = (char)(255.99f * colour.y);
            char b = (char)(255.99f * colour.z);
            
            ofs << r << g << b;
            
        }
    }
    // Time keeping
    auto end = std::chrono::system_clock::now();
    
    std::cout<<"Rendering complete! \n";
    
    ofs.close();
    
    // Time keeping
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Program completed on " << std::ctime(&end_time) << "\nTime taken to render : " << elapsed_seconds.count() << "s\n\n";
    //Time keeping
    
    return EXIT_SUCCESS;
}