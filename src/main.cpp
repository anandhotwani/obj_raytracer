#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>

#include "../src/math.hpp"
#include "../src/sphere.hpp"
#include "../src/scene.hpp"
#include "../src/camera.hpp"

struct Options {
    uint32_t width;
    uint32_t height;
    float fov;
    Matrix4x4f c2w;
};

Vector3f cast_ray(const Ray& r, const Shape& scene) {
    SurfaceInteraction interaction;
    if (scene.intersect(r, interaction)) {
        return Vector3f(glm::dot(interaction.Ng, -r.d));
    }

    return Vector3f(0.18f);
}

int main() {
    
    Options options;
    options.width   = 1024;
    options.height  = 429;
    options.fov     = 48.65f;
    options.c2w = Matrix4x4f(    1.0f, 0.0f, 0.0f, 0.0f,
                                 0.0,  1.0f, 0.0f, 0.0f,
                                 0.0f, 0.0f, 1.0f, 0.0f,
                                 0.0f, 0.0f, 3.0f, 1.0f);   // 4x4 Matrix

    Camera camera(options.width, options.height, options.fov, options.c2w);
    Scene scene;

    Vector3f pos = Vector3f(0.0f, 0.0f, -5.0f);
    float rad = 0.75f;
    scene.Add(std::make_shared<Sphere>(pos, rad));

    Vector3f pos2 = Vector3f(2.0f, 0.0f, -5.0f);
    float rad2 = 0.35f;
    scene.Add(std::make_shared<Sphere>(pos2, rad2));

    Vector3f pos3 = Vector3f(-2.2f, 0.0f, -5.0f);
    float rad3 = 1.25f;
    scene.Add(std::make_shared<Sphere>(pos3, rad3));

    std::ofstream ofs("render.1001.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << options.width << " " << options.height << "\n255\n";

    const static float gamma = 1.0f / 2.2f;   

    // Time keeping
    auto start = std::chrono::system_clock::now();
    std::cout<<"Rendering image ... \n";
    for (uint32_t j = 0; j < options.height; ++j) {
        //std::cout<<"Scanlines remaining : "<<options.height - j<<"\n";
        for (uint32_t i = 0; i < options.width; ++i) {

            Ray ray = camera.get_ray(i, j);          
            Vector3f colour = cast_ray(ray, scene);
            
            char r = (char)(255.99f * powf(colour.x, gamma));
            char g = (char)(255.99f * powf(colour.y, gamma));
            char b = (char)(255.99f * powf(colour.z, gamma));
            
            ofs << r << g << b;
            
        }
    }
    // Time keeping
    auto end = std::chrono::system_clock::now();
    
    std::cout<<"Rendering complete! \n";
    
    ofs.close();
    scene.Clear();
    
    // Time keeping
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Program completed on " << std::ctime(&end_time) << "\nTime taken to render : " << elapsed_seconds.count() << "s\n\n";
    
    return EXIT_SUCCESS;
}