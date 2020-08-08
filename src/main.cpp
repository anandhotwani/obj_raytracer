#include <iostream>
#include <fstream>
#include "../src/vec3.h"

struct Options {
    uint32_t width;
    uint32_t height;
};


int main() {

    Options options;
    options.width = 1024;
    options.height = 429;

    std::ofstream ofs("VSCODE_render.ppm", std::ios::out | std::ios::binary);
    ofs<<"P6\n"<<options.width<<" "<<options.height<<"\n255\n";

    std::cout<<"Rendering now... \n";

    for (uint32_t j = 0; j < options.height; ++j) {
        std::cout<<"Scanlines remaining : "<<options.height - j<<"\n";
        for (uint32_t i = 0; i < options.width; ++i) {
            float u = float(j) / float(options.height);
            float v = float(i) / float(options.width); 
            Vec3f colour = Vec3f(u, v, 0.18f);

            char r = (char)(255.99f * colour.x);
            char g = (char)(255.99f * colour.y);
            char b = (char)(255.99f * colour.z);

            ofs << r << g << b;

        }
    }

    ofs.close();
    std::cout<<"Rendering complete!\n";

    Vec3f a = Vec3f(1.0f, 0.0f, 2.0f);
    Vec3f b = Vec3f(1.0f, 0.5f, 1.0f);
    Vector3f glm_a = Vector3f(1.0f, 0.5f, 2.0f);

    std::cout<<"hello vec3\n";
    std::cout<<"A + B is "<<a+b<<"\n";
    std::cout<<"GLM y component is "<<glm_a[1]<<"\n";
    return EXIT_SUCCESS;
}
