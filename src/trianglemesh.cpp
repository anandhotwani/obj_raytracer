#include "trianglemesh.hpp"


#include "trianglemesh.hpp"

TriangleMesh::TriangleMesh(const char *filepath) {
    

    std::string inputfile = filepath;
    unsigned long pos = inputfile.find_last_of("/");
    std::string mtlbasepath = inputfile.substr(0, pos + 1);

    std::cout<<"> Attempting to open  "<<inputfile<<" ... \n";
    std::string err = tinyobj::LoadObj(shapes, materials, inputfile.c_str(), mtlbasepath.c_str());

    if (!err.empty()) {
        std::cout<<err<<std::endl;
    }

    long shapes_size, indices_size;
    shapes_size = shapes.size();
    std::cout<<"> Number of polygon objects found in the .obj file : "<<shapes.size()<<"\n";

    // Load triangles
    for (uint32_t i = 0; i < shapes_size; ++i) {
        indices_size = shapes[i].mesh.indices.size() / 3;
        std::cout<<"> Triangles found in mesh : "<<indices_size<<"\n";
        for (size_t f = 0; f < indices_size; ++f) {
            
            // Vertices
            Vector3f v0 = Vector3f(
                                    shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f] * 3],
                                    shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f] * 3 + 1],
                                    shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f] * 3 + 2]
                                    );
            Vector3f v1 = Vector3f(
                                    shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 1] * 3],
                                    shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 1] * 3 + 1],
                                    shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 1] * 3 + 2]
                                    );
            Vector3f v2 = Vector3f(
                                    shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 2] * 3],
                                    shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 2] * 3 + 1],
                                    shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 2] * 3 + 2]
                                    );
            
            Vector2f UV0, UV1, UV2;
            
            // Attempt to load texture coordinates, UV
            if (shapes[i].mesh.indices[3 * f + 2] * 2 + 1 < shapes[i].mesh.texcoords.size()) {
                UV0 = Vector2f(
                    shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f] * 2],
                    shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f] * 2 + 1]
                );

                UV1 = Vector2f(
                    shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f + 1] * 2],
                    shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f + 1] * 2 + 1]
                );

                UV2 = Vector2f(
                    shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f + 2] * 2],
                    shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f + 2] * 2 + 1]
                );
                
                // Ensure UVs are in [0,1] range
                // UV0.x = saturate(UV0.x);
                // UV0.y = saturate(UV0.y);
                // UV1.x = saturate(UV1.x);
                // UV1.y = saturate(UV1.y);
                // UV2.x = saturate(UV2.x);
                // UV2.y = saturate(UV2.y);
                
//                std::cout<<"UV Coordinates are : \n"<<"v0 : "<<glm::to_string(UV0)<<"\nv1 : "<<glm::to_string(UV1)<<"\nv2 : "<<glm::to_string(UV2)<<"\n";
            }
            else {
                UV0 = Vector2f(0.0f);
                UV1 = Vector2f(0.0f);
                UV2 = Vector2f(0.0f);
            }

            tris.push_back(std::make_shared<Triangle>(v0, v1, v2));
        }
    }
    std::cout<<"> Successfully opened "<<inputfile<<"! \n\n";
    
    shapes.clear();
    materials.clear();
}

bool TriangleMesh::intersect(const Ray &r, SurfaceInteraction &interaction) const {
    
    
    bool hit_tri = false;
    long tri_idx;
    float t = r.t_max;
    SurfaceInteraction temp;
    long triangles_size = tris.size();
    for (long i = 0; i < triangles_size; ++i) {
        if (tris[i]->intersect(r, temp)) {
            hit_tri = true;
            tri_idx = i;
            r.t_max = temp.t;
            interaction = temp;
        }
    }
    return hit_tri;
}